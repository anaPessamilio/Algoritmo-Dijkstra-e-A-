Algoritmos de Busca em Grafos
Este repositório contém a implementação dos algoritmos de busca Dijkstra e A* para encontrar o caminho mais curto em grafos. O projeto utiliza duas estruturas de dados principais: matriz de adjacência e lista de adjacência. O código foi escrito em C++ e inclui uma análise de desempenho detalhada e comparação entre diferentes abordagens.

Estruturas de Dados
Grafo: Representa o grafo usando duas estruturas de dados:

Matriz de Adjacência: Armazena as distâncias entre os vértices.
Lista de Adjacência: Armazena as conexões entre os vértices e portais.
Fila de Prioridade: Implementa um heap para suportar operações de inserção e remoção com base no menor custo. Armazena o custo, o nó associado e o número de portais usados.

Funcionalidades
Algoritmo Dijkstra: Encontra o caminho mais curto em grafos com pesos não negativos.
Algoritmo A*: Encontra o caminho mais curto utilizando uma heurística para guiar a busca, otimizando o tempo de execução.
Compilação
Para compilar o projeto, use o seguinte comando:

g++ -std=c++11 -O2 -g -Wall -c src/Grafo.cpp -o obj/Grafo.o -I./include/
g++ -std=c++11 -O2 -g -Wall -c src/tp2.cpp -o obj/tp2.o -I./include/
g++ -std=c++11 -O2 -g -Wall -o ./bin/tp2.out ./obj/Grafo.o ./obj/tp2.o ./obj/FilaDePrioridade.o

Execução
Para executar o programa, utilize o comando:

./bin/tp2.out < entrada.txt

Certifique-se de que o arquivo entrada.txt está no mesmo diretório que o executável. Este arquivo deve conter as entradas para o algoritmo.

Análise de Desempenho
O projeto inclui análises detalhadas de desempenho usando ferramentas como chrono para medir o tempo de execução e Valgrind para avaliar a localidade de referência. Para gerar gráficos comparativos e visualizar os resultados, foram utilizados scripts Python.

Referências
Valgrind: Documentação do Valgrind
chrono: Funções Chrono no Microsoft Docs
Python para Gráficos: Dicas de Gráficos em Python
Algoritmo A*: Wikipedia
Dijkstra: Repositório GitHub
Código de Marcos Castro: Gist
