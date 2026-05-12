"""
Script para geração de gráficos de complexidade.
Lê os dados de 'tempos_execucao.csv' e gera visualizações em PNG.
"""
import pandas as pd
import matplotlib.pyplot as plt

try:
    # Leitura dos dados gerados pelo programa C++
    df = pd.read_csv('tempos_execucao.csv')

    # --- Gráfico de Busca ---
    plt.figure(figsize=(10, 6))
    plt.plot(df['n'], df['B_Sequencial'], label='Sequencial O(n)', marker='o', color='crimson')
    plt.plot(df['n'], df['B_Binaria'], label='Binária O(log n)', marker='o', color='royalblue')
    plt.title('Eficiência de Algoritmos de Busca')
    plt.xlabel('Número de Elementos (n)')
    plt.ylabel('Tempo (nanossegundos)')
    plt.legend()
    plt.grid(True, linestyle='--')
    plt.savefig('grafico_busca.png')

    # --- Gráfico de Ordenação ---
    plt.figure(figsize=(10, 6))
    plt.plot(df['n'], df['InsertionSort'], label='Insertion Sort O(n²)', marker='s', color='darkorange')
    plt.plot(df['n'], df['QuickSort'], label='Quick Sort O(n log n)', marker='s', color='forestgreen')
    plt.title('Eficiência de Algoritmos de Ordenação')
    plt.xlabel('Número de Elementos (n)')
    plt.ylabel('Tempo (nanossegundos)')
    plt.legend()
    plt.grid(True, linestyle='--')
    plt.savefig('grafico_ordenacao.png')

    print("Processamento concluído: Imagens 'grafico_busca.png' e 'grafico_ordenacao.png' salvas.")

except FileNotFoundError:
    print("Erro: Arquivo 'tempos_execucao.csv' não encontrado. Execute o programa C++ primeiro.")