#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "../include/Grafo.h"
#include "../include/FilaDePrioridade.h"

const double INF = 1e9;

int* dijkstra(Grafo &g, int inicio, int objetivo, double energia, int maxPortais) {
    FilaDePrioridade conjuntoAberto;
    conjuntoAberto.adicionar(0, inicio, 0);

    double* dist = new double[g.tamanho()];
    int* contadorPortais = new int[g.tamanho()];
    for (int i = 0; i < g.tamanho(); ++i) {
        dist[i] = INF;
        contadorPortais[i] = 0;
    }
    dist[inicio] = 0;

    while (!conjuntoAberto.vazio()) {
        auto parAtual = conjuntoAberto.remover();
        double custoAtual = parAtual.first;
        int atual = parAtual.second.first;
        int portaisUsados = parAtual.second.second;

        if (atual == objetivo && custoAtual <= energia && portaisUsados <= maxPortais) {
            int* resultado = new int[1];
            resultado[0] = 1; // Existe caminho
            return resultado;
        }

        if (custoAtual > energia) continue;

        for (int vizinho = 0; vizinho < g.tamanho(); ++vizinho) {
            double peso = g.obterAresta(atual, vizinho);
            if (peso < INF) { // Existe aresta
                double novoCusto = custoAtual + peso;
                int novoContadorPortais = portaisUsados + (peso == 0 ? 1 : 0);
                if (novoCusto <= energia && novoCusto < dist[vizinho] && novoContadorPortais <= maxPortais) {
                    dist[vizinho] = novoCusto;
                    contadorPortais[vizinho] = novoContadorPortais;
                    conjuntoAberto.adicionar(novoCusto, vizinho, novoContadorPortais);
                }
            }
        }
    }

    int* resultado = new int[1];
    resultado[0] = 0; // Não existe caminho
    return resultado;
}

double heuristica(const Grafo &g, int a, int b) {
    return g.obterDistancia(a, b);
}

int* a_estrela(Grafo &g, int inicio, int objetivo, double energia, int maxPortais) {
    FilaDePrioridade conjuntoAberto;
    conjuntoAberto.adicionar(heuristica(g, inicio, objetivo), inicio, 0);

    double* dist = new double[g.tamanho()];
    int* contadorPortais = new int[g.tamanho()];
    for (int i = 0; i < g.tamanho(); ++i) {
        dist[i] = INF;
        contadorPortais[i] = 0;
    }
    dist[inicio] = 0;

    while (!conjuntoAberto.vazio()) {
        auto parAtual = conjuntoAberto.remover();
        double custoAtual = parAtual.first;
        int atual = parAtual.second.first;
        int portaisUsados = parAtual.second.second;

        // Remove a heurística do custo atual para comparar com a distância real
        custoAtual -= heuristica(g, atual, objetivo);

        if (atual == objetivo && custoAtual <= energia && portaisUsados <= maxPortais) {
            int* resultado = new int[1];
            resultado[0] = 1; // Existe caminho
            return resultado;
        }

        if (custoAtual > energia || portaisUsados > maxPortais) continue;

        for (int vizinho = 0; vizinho < g.tamanho(); ++vizinho) {
            double peso = g.obterAresta(atual, vizinho);
            if (peso < INF) { // Existe aresta
                double novoCusto = custoAtual + peso;
                int novoContadorPortais = portaisUsados + (peso == 0 ? 1 : 0);
                if (novoCusto <= energia && novoCusto < dist[vizinho] && novoContadorPortais <= maxPortais) {
                    dist[vizinho] = novoCusto;
                    contadorPortais[vizinho] = novoContadorPortais;
                    conjuntoAberto.adicionar(novoCusto + heuristica(g, vizinho, objetivo), vizinho, novoContadorPortais);
                }
            }
        }
    }

    int* resultado = new int[1];
    resultado[0] = 0; // Não existe caminho
    return resultado;
}

int main() {
    int numExecucoes;
    std::cin >> numExecucoes;

    for (int exec = 0; exec < numExecucoes; ++exec) {
        int n, m, k;
        std::cin >> n >> m >> k;

        Grafo g(n);

        for (int i = 0; i < n; ++i) {
            double x, y;
            std::cin >> x >> y;
            g.definirCoordenada(i, x, y);
        }

        for (int i = 0; i < m; ++i) {
            int u, v;
            std::cin >> u >> v;
            double peso = g.obterDistancia(u, v);
            g.adicionarAresta(u, v, peso);
        }

        for (int i = 0; i < k; ++i) {
            int u, v;
            std::cin >> u >> v;
            g.adicionarAresta(u, v, 0); // Peso 0 para portais
        }

        double energia;
        int maxPortais;
        std::cin >> energia >> maxPortais;

        // Medir tempo de execução para Dijkstra
        auto startDijkstra = std::chrono::high_resolution_clock::now();
        int* resultadoDijkstra = dijkstra(g, 0, n - 1, energia, maxPortais);
        auto endDijkstra = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedDijkstra = endDijkstra - startDijkstra;

        // Medir tempo de execução para A*
        auto startAEstrela = std::chrono::high_resolution_clock::now();
        int* resultadoAEstrela = a_estrela(g, 0, n - 1, energia, maxPortais);
        auto endAEstrela = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedAEstrela = endAEstrela - startAEstrela;

        // Salvar resultados em arquivo CSV
        std::ofstream file("tempos_execucao.csv", std::ios::app);
        if (file.is_open()) {
            file << n << "," << m << "," << energia << "," << maxPortais << ","
                 << elapsedDijkstra.count() << "," << elapsedAEstrela.count() << "\n";
            file.close();
        }

        std::cout << "Execução " << exec + 1 << ": Dijkstra: " << resultadoDijkstra[0] << " A*: " << resultadoAEstrela[0] << "\n";
        
        delete[] resultadoDijkstra;
        delete[] resultadoAEstrela;
    }

    return 0;
}
