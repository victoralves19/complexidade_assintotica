/**
 * @file main.cpp
 * @author Victor Alves
 * @brief Análise empírica de complexidade de algoritmos de busca e ordenação.
 * @version 2.0
 * * Este programa mede o tempo de execução dos algoritmos:
 * - Busca Sequencial O(n)
 * - Busca Binária O(log n)
 * - Insertion Sort O(n^2)
 * - Quick Sort O(n log n)
 * * Os dados são exportados para 'tempos_execucao.csv' para posterior plotagem.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;

/**
 * Realiza a busca linear em um vetor.
 * Complexidade: O(n) no pior caso.
 * @param arr Referência constante para o vetor de inteiros.
 * @param alvo Valor a ser procurado.
 * @return Índice do elemento ou -1 se não encontrado.
 */
int buscaSequencial(const vector<int>& arr, int alvo) {
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == alvo) return i;
    }
    return -1;
}

/**
 * Realiza a busca binária (divisão e conquista).
 * Requisito: Vetor deve estar ordenado.
 * Complexidade: O(log n).
 */
int buscaBinaria(const vector<int>& arr, int alvo) {
    int esq = 0, dir = (int)arr.size() - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (arr[meio] == alvo) return meio;
        if (arr[meio] < alvo) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}

/**
 * Ordenação por inserção.
 * Eficiente para conjuntos pequenos, mas custoso para grandes.
 * Complexidade: O(n^2) no pior caso.
 */
void insertionSort(vector<int>& arr) {
    for (int i = 1; i < (int)arr.size(); i++) {
        int chave = arr[i];
        int j = i - 1;
        // Desloca elementos maiores que a chave para a direita
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

/**
 * Função auxiliar do Quick Sort para particionamento.
 * Utiliza o último elemento como pivô.
 */
int particiona(vector<int>& arr, int baixo, int alto) {
    int pivo = arr[alto];
    int i = (baixo - 1);
    for (int j = baixo; j <= alto - 1; j++) {
        if (arr[j] < pivo) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[alto]);
    return (i + 1);
}

/**
 * Quick Sort: Algoritmo de ordenação eficiente.
 * Complexidade: O(n log n) em média.
 */
void quickSort(vector<int>& arr, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particiona(arr, baixo, alto);
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

/**
 * Gera um vetor de tamanho N com números aleatórios.
 * Usa mt19937 para geração de números de alta qualidade.
 */
vector<int> gerarVetor(int n) {
    vector<int> arr(n);
    mt19937 rng(42); // Semente fixa para resultados reprodutíveis
    uniform_int_distribution<int> dist(1, n * 10);
    for (int i = 0; i < n; i++) arr[i] = dist(rng);
    return arr;
}

int main() {
    // Definição das amostras de tamanho de entrada (n)
    vector<int> tamanhos = {1000, 5000, 10000, 20000, 40000};
    int repeticoes = 30; // Aumentado para reduzir variância estatística
    
    ofstream arquivo("tempos_execucao.csv");
    arquivo << "n,B_Sequencial,B_Binaria,InsertionSort,QuickSort\n";

    cout << "--- Iniciando Testes de Desempenho ---" << endl;

    for (int n : tamanhos) {
        long long tSeq = 0, tBin = 0, tIns = 0, tQui = 0;

        for (int r = 0; r < repeticoes; r++) {
            vector<int> arrOriginal = gerarVetor(n);
            int alvo = -1; // Alvo inexistente garante o pior caso O(n) na busca
            
            // Medição da Busca Sequencial
            auto inicio = high_resolution_clock::now();
            // volatile impede o compilador de remover a função por "não usar o retorno"
            volatile int res1 = buscaSequencial(arrOriginal, alvo); 
            auto fim = high_resolution_clock::now();
            tSeq += duration_cast<nanoseconds>(fim - inicio).count();

            // Medição da Busca Binária (com vetor ordenado)
            vector<int> arrOrdenado = arrOriginal;
            sort(arrOrdenado.begin(), arrOrdenado.end());
            inicio = high_resolution_clock::now();
            volatile int res2 = buscaBinaria(arrOrdenado, alvo);
            fim = high_resolution_clock::now();
            tBin += duration_cast<nanoseconds>(fim - inicio).count();

            // Medição do Insertion Sort
            vector<int> arrIns = arrOriginal;
            inicio = high_resolution_clock::now();
            insertionSort(arrIns);
            fim = high_resolution_clock::now();
            tIns += duration_cast<nanoseconds>(fim - inicio).count();

            // Medição do Quick Sort
            vector<int> arrQui = arrOriginal;
            inicio = high_resolution_clock::now();
            quickSort(arrQui, 0, n - 1);
            fim = high_resolution_clock::now();
            tQui += duration_cast<nanoseconds>(fim - inicio).count();
        }

        // Grava a média dos tempos no arquivo CSV
        arquivo << n << "," << (tSeq/repeticoes) << "," << (tBin/repeticoes) 
                << "," << (tIns/repeticoes) << "," << (tQui/repeticoes) << "\n";
        
        cout << "[OK] Testes concluidos para n = " << n << endl;
    }
    
    arquivo.close();
    cout << "Relatorio de tempos gerado: 'tempos_execucao.csv'" << endl;
    return 0;
}