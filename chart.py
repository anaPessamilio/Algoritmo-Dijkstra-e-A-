import pandas as pd
import matplotlib.pyplot as plt

# Leitura dos dados do arquivo CSV
df = pd.read_csv('tempos_execucao.csv')

# Criando o gráfico de barras
plt.figure(figsize=(8, 6))
plt.bar(df['Algoritmo'], df['Tempo de Execução (s)'], color=['blue', 'green'])
plt.xlabel('Algoritmo')
plt.ylabel('Tempo de Execução (s)')
plt.title('Comparação de Tempo de Execução entre Dijkstra e A*')
plt.xticks(rotation=45)
plt.tight_layout()

# Salvar o gráfico como imagem PNG
plt.savefig('grafico_tempo_execucao.png')

# Mostrar o gráfico na tela (opcional)
plt.show()
