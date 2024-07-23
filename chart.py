import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import r2_score

# Função para plotar o gráfico e salvar a imagem
def plot_comparison_graph(x, y1, y2, xlabel, ylabel, title, filename):
    plt.figure()
    plt.scatter(x, y1, color='blue', label='Dijkstra')
    plt.scatter(x, y2, color='green', label='A*')
    
    # Ajuste de linha para Dijkstra
    coeffs_dijkstra = np.polyfit(x, y1, 1)
    poly_dijkstra = np.poly1d(coeffs_dijkstra)
    x_fit = np.linspace(min(x), max(x), 100)
    y_fit_dijkstra = poly_dijkstra(x_fit)
    
    plt.plot(x_fit, y_fit_dijkstra, color='blue', linestyle='--', label=f'Dijkstra Ajuste: R²={r2_dijkstra:.2f}')
    
    # Ajuste de linha para A*
    coeffs_a_star = np.polyfit(x, y2, 1)
    poly_a_star = np.poly1d(coeffs_a_star)
    y_fit_a_star = poly_a_star(x_fit)
    
    plt.plot(x_fit, y_fit_a_star, color='green', linestyle='--', label=f'A* Ajuste: R²={r2_a_star:.2f}')
    
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.savefig(filename)
    plt.close()

# Carregar os dados do CSV com cabeçalhos fictícios
column_names = ['Número de Nós', 'Número de Arestas', 'Energia', 'Número Máximo de Portais', 'Tempo Dijkstra', 'Tempo A*']
data = pd.read_csv('tempos_execucao.csv', header=None, names=column_names)

# Verificar as colunas
print("Colunas do CSV:", data.columns)

# Ajuste de acordo com os nomes corretos das colunas
try:
    n = data['Número de Nós']
    m = data['Número de Arestas']
    energia = data['Energia']
    portais = data['Número Máximo de Portais']
    tempo_dijkstra = data['Tempo Dijkstra']
    tempo_a_estrela = data['Tempo A*']
except KeyError as e:
    print(f"Erro ao acessar a coluna: {e}")
    exit()

# Calcular R² para ajuste de linha
def calculate_r2(x, y):
    coeffs = np.polyfit(x, y, 1)
    poly = np.poly1d(coeffs)
    y_pred = poly(x)
    return r2_score(y, y_pred)

# Gráficos comparativos
r2_dijkstra = calculate_r2(n, tempo_dijkstra)
r2_a_star = calculate_r2(n, tempo_a_estrela)
plot_comparison_graph(n, tempo_dijkstra, tempo_a_estrela, 'Número de Nós', 'Tempo de Execução (s)', 'Tempo de Execução vs Número de Nós', 'comparison_vs_n.png')

r2_dijkstra = calculate_r2(m, tempo_dijkstra)
r2_a_star = calculate_r2(m, tempo_a_estrela)
plot_comparison_graph(m, tempo_dijkstra, tempo_a_estrela, 'Número de Arestas', 'Tempo de Execução (s)', 'Tempo de Execução vs Número de Arestas', 'comparison_vs_m.png')

r2_dijkstra = calculate_r2(energia, tempo_dijkstra)
r2_a_star = calculate_r2(energia, tempo_a_estrela)
plot_comparison_graph(energia, tempo_dijkstra, tempo_a_estrela, 'Energia', 'Tempo de Execução (s)', 'Tempo de Execução vs Energia', 'comparison_vs_energia.png')

r2_dijkstra = calculate_r2(portais, tempo_dijkstra)
r2_a_star = calculate_r2(portais, tempo_a_estrela)
plot_comparison_graph(portais, tempo_dijkstra, tempo_a_estrela, 'Número Máximo de Portais', 'Tempo de Execução (s)', 'Tempo de Execução vs Número Máximo de Portais', 'comparison_vs_portais.png')
