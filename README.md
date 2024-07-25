# Algoritmos de Busca em Grafos

Este repositório contém a implementação dos algoritmos de busca Dijkstra e A* para encontrar o caminho mais curto em grafos. O projeto utiliza duas estruturas de dados principais: matriz de adjacência e lista de adjacência. O código foi escrito em C++ e inclui uma análise de desempenho detalhada e comparação entre diferentes abordagens.

## Estruturas de Dados

- Grafo: Representa o grafo usando duas estruturas de dados:

- Matriz de Adjacência: Armazena as distâncias entre os vértices.

- Lista de Adjacência: Armazena as conexões entre os vértices e portais.

- Fila de Prioridade: Implementa um heap para suportar operações de inserção e remoção com base no menor custo. Armazena o custo, o nó associado e o número de portais usados.

## Funcionalidades

- Algoritmo Dijkstra: Encontra o caminho mais curto em grafos com pesos não negativos.

- Algoritmo A*: Encontra o caminho mais curto utilizando uma heurística para guiar a busca, otimizando o tempo de execução.

# Compilação

Para compilar o projeto, use o seguinte comando:

- g++ -std=c++11 -O2 -g -Wall -c src/Grafo.cpp -o obj/Grafo.o -I./include/
- g++ -std=c++11 -O2 -g -Wall -c src/tp2.cpp -o obj/tp2.o -I./include/
- g++ -std=c++11 -O2 -g -Wall -o ./bin/tp2.out ./obj/Grafo.o ./obj/tp2.o ./obj/FilaDePrioridade.o

# Geração de Entradas:

Para gerar o arquivo entradas.txt, execute o script geraEntradas.py:

- python geraEntradas.py
  
# Execução

Para executar o programa, utilize o comando:

./bin/tp2.out < entrada.txt

Certifique-se de que o arquivo entrada.txt está no mesmo diretório que o executável. Este arquivo deve conter as entradas para o algoritmo.

# Gráficos de Desempenho: 

Para gerar gráficos comparativos, execute o script chart.py:

- python chart.py
  
# Análise de Desempenho

Para analisar o desempenho do programa, você pode usar o Valgrind. Execute o programa com Valgrind para avaliar a localidade de referência e o uso de cache:

- valgrind --tool=cachegrind ./bin/tp2.out


