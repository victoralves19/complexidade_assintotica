import pandas as pd
import matplotlib.pyplot as plt

# Lê os dados gerados pelo C++
df = pd.read_csv("tempos_execucao.csv")

# --- Gráfico 1: Buscas ---
plt.figure(figsize=(10, 5))
plt.plot(df['n'], df['B_Sequencial(ns)'], marker='o', label='Busca Sequencial O(n)', color='red')
plt.plot(df['n'], df['B_Binaria(ns)'], marker='s', label='Busca Binária O(log n)', color='blue')
plt.title("Análise Empírica: Algoritmos de Busca")
plt.xlabel("Tamanho da Entrada (n)")
plt.ylabel("Tempo (nanossegundos)")
plt.legend()
plt.grid(True)
plt.savefig("grafico_buscas.png")
plt.close()

# --- Gráfico 2: Ordenação ---
plt.figure(figsize=(10, 5))
plt.plot(df['n'], df['InsertionSort(ns)'], marker='o', label='Insertion Sort O(n²)', color='orange')
plt.plot(df['n'], df['QuickSort(ns)'], marker='s', label='Quick Sort O(n log n)', color='green')
plt.title("Análise Empírica: Algoritmos de Ordenação")
plt.xlabel("Tamanho da Entrada (n)")
plt.ylabel("Tempo (nanossegundos)")
plt.legend()
plt.grid(True)
plt.savefig("grafico_ordenacao.png")
plt.close()

print("Gráficos gerados com sucesso! Verifique as imagens na pasta.")