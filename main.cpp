#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;

/**
 * --- 1. Busca Sequencial ---
 * Complexidade de Pior Caso: O(n)
 * Percorre o vetor elemento por elemento.
 */
int buscaSequencial(const vector<int>& arr, int alvo) {
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == alvo) return i;
    }
    return -1;
}

/**
 * --- 2. Busca Binária ---
 * Complexidade de Pior Caso: O(log n)
 * Divide o espaço de busca pela metade a cada iteração.
 * Requisito: O vetor deve estar ordenado.
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
 * --- 3. Insertion Sort ---
 * Complexidade de Pior Caso: O(n^2)
 * Algoritmo estável que ordena inserindo elementos em sua posição correta
 * em um subconjunto já ordenado do vetor.
 */
void insertionSort(vector<int>& arr) {
    for (int i = 1; i < (int)arr.size(); i++) {
        int chave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

/**
 * --- 4. Quick Sort ---
 * Complexidade Média: O(n log n) | Pior Caso: O(n^2)
 * Algoritmo de divisão e conquista que utiliza um pivô para particionar o vetor.
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

void quickSort(vector<int>& arr, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particiona(arr, baixo, alto);
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

// Utilitário para gerar vetor com semente fixa para reprodutibilidade
vector<int> gerarVetor(int n) {
    vector<int> arr(n);
    mt19937 rng(42); 
    uniform_int_distribution<int> dist(1, n * 10);
    for (int i = 0; i < n; i++) arr[i] = dist(rng);
    return arr;
}

int main() {
    // Tamanhos de entrada conforme exigido no relatório [cite: 59]
    vector<int> tamanhos = {1000, 5000, 10000, 20000, 40000};
    int repeticoes = 10; // Número de repetições para mitigar ruídos 
    
    ofstream arquivo("tempos_execucao.csv");
    arquivo << "n,B_Sequencial(ns),B_Binaria(ns),InsertionSort(ns),QuickSort(ns)\n";

    cout << "Iniciando a analise empirica dos algoritmos..." << endl;

    for (int n : tamanhos) {
        long long tSeq = 0, tBin = 0, tIns = 0, tQui = 0;

        for (int r = 0; r < repeticoes; r++) {
            vector<int> arrOriginal = gerarVetor(n);
            int alvo = arrOriginal[n - 1]; // Teste focado no pior caso da busca linear
            
            // Medição: Busca Sequencial
            auto inicio = high_resolution_clock::now();
            buscaSequencial(arrOriginal, alvo);
            auto fim = high_resolution_clock::now();
            tSeq += duration_cast<nanoseconds>(fim - inicio).count();

            // Medição: Busca Binária (ordenada previamente com std::sort)
            vector<int> arrOrdenado = arrOriginal;
            sort(arrOrdenado.begin(), arrOrdenado.end());
            inicio = high_resolution_clock::now();
            buscaBinaria(arrOrdenado, alvo);
            fim = high_resolution_clock::now();
            tBin += duration_cast<nanoseconds>(fim - inicio).count();

            // Medição: Insertion Sort
            vector<int> arr1 = arrOriginal;
            inicio = high_resolution_clock::now();
            insertionSort(arr1);
            fim = high_resolution_clock::now();
            tIns += duration_cast<nanoseconds>(fim - inicio).count();

            // Medição: Quick Sort
            vector<int> arr2 = arrOriginal;
            inicio = high_resolution_clock::now();
            quickSort(arr2, 0, n - 1);
            fim = high_resolution_clock::now();
            tQui += duration_cast<nanoseconds>(fim - inicio).count();
        }

        // Salva a média das execuções no CSV [cite: 17, 60]
        arquivo << n << "," << (tSeq/repeticoes) << "," << (tBin/repeticoes) << "," << (tIns/repeticoes) << "," << (tQui/repeticoes) << "\n";
        cout << "Testado para n = " << n << " concluido." << endl;
    }
    
    arquivo.close();
    cout << "\nSucesso! Arquivo 'tempos_execucao.csv' gerado na mesma pasta." << endl;
    return 0;
}