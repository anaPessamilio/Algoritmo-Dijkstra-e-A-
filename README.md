Introdução:

Implementação de um sistema de busca em um ambiente de clareiras interligadas por trilhas e portais. O problema consiste em encontrar caminhos eficientes entre pontos específicos, respeitando restrições de quantidades de energia e portais. Utilizando os algoritmos  Dijkstra e A*, adaptados com filas de prioridade, a solução emprega estruturas de dados como listas de adjacência e heurísticas de distância euclidiana para maximizar a eficácia da busca.

Método:

A implementação do programa foi feita na linguagem C++, tendo como base inicial os algoritmos  Dijkstra e A*.
As duas estruturas de dados implementadas foram:

- Grafo: Utiliza uma matriz de adjacência para armazenar as distâncias euclidianas entre as clareiras e uma lista de adjacência para armazenar as conexões de portais. Contém o TAD No, que representa um nó na lista de adjacência do grafo, contendo informações sobre a aresta e o próximo nó na lista.
- FilaDePrioridade: Utiliza uma fila de prioridade para suportar operações de inserção e remoção de elementos com base em custos associados. Contém o TAD Elemento, que  armazena o custo, nó associado e número de portais usados.
  
As principais funções implementadas foram:

- definirCoordenada(int u, double x, double y): Define as coordenadas de uma clareira.
- obterDistancia(int u, int v): Calcula a distância euclidiana entre duas clareiras.
- adicionarAresta(int u, int v, double peso): Adiciona uma aresta (trilha ou portal) entre duas clareiras.
- adicionar(double custo, int no, int portais): Adiciona um elemento na fila com base no custo.
- remover(): Remove e retorna o elemento com menor custo da fila.
A função main() é responsável por ler os dados de entrada, fazer as chamadas para construir os grafos e executar os algoritmos de busca, e por fim,  imprimir os resultados

Como executar:

- ./bin/tp2.out

Como gerar e analisar os resultados:

- ./test.sh
- python3 analyze.py

Dependências:

- g++
- Python 3
- Bibliotecas: matplotlib, pandas
