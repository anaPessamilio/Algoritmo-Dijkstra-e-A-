#include <iostream>
#include "Grafo.h"
#include "FilaDePrioridade.h"

const double INF = 1e9;

// Algoritmo de Dijkstra
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

        for (const No* no = g.obterArestas(atual); no != nullptr; no = no->proximo) {
            int vizinho = no->aresta.first;
            double peso = no->aresta.second;
            double novoCusto = custoAtual + peso;
            int novoContadorPortais = portaisUsados + (peso == 0 ? 1 : 0);
            if (novoCusto <= energia && novoCusto < dist[vizinho] && novoContadorPortais <= maxPortais) {
                dist[vizinho] = novoCusto;
                contadorPortais[vizinho] = novoContadorPortais;
                conjuntoAberto.adicionar(novoCusto, vizinho, novoContadorPortais);
            }
        }
    }
    
    int* resultado = new int[1];
    resultado[0] = 0; // Não existe caminho
    return resultado;
}

// Função heurística para o A*
double heuristica(const Grafo &g, int a, int b) {
    return g.obterDistancia(a, b);
}

// Algoritmo A*
int* a_estrela(Grafo &g, int inicio, int objetivo, double energia, int maxPortais) {
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

        for (const No* no = g.obterArestas(atual); no != nullptr; no = no->proximo) {
            int vizinho = no->aresta.first;
            double peso = no->aresta.second;
            double novoCusto = custoAtual + peso;
            int novoContadorPortais = portaisUsados + (peso == 0 ? 1 : 0);
            if (novoCusto <= energia && novoCusto < dist[vizinho] && novoContadorPortais <= maxPortais) {
                dist[vizinho] = novoCusto;
                contadorPortais[vizinho] = novoContadorPortais;
                conjuntoAberto.adicionar(novoCusto + heuristica(g, vizinho, objetivo), vizinho, novoContadorPortais);
            }
        }
    }
    
    int* resultado = new int[1];
    resultado[0] = 0; // Não existe caminho
    return resultado;
}

// Função principal para resolver o problema
void resolver() {
    int n, m, k;
    std::cin >> n >> m >> k;

    Grafo g(n);

    // Leitura das coordenadas das clareiras (e armazená-las no grafo)
    for (int i = 0; i < n; ++i) {
        double x, y;
        std::cin >> x >> y;
        g.definirCoordenada(i, x, y);
    }

    // Leitura das trilhas e cálculo da distância euclidiana
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        double peso = g.obterDistancia(u, v);
        g.adicionarAresta(u, v, peso);
    }

    // Leitura dos portais
    for (int i = 0; i < k; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.adicionarAresta(u, v, 0); // Peso 0 para portais
    }

    double energia;
    int maxPortais;
    std::cin >> energia >> maxPortais;

    int* resultadoDijkstra = dijkstra(g, 0, n - 1, energia, maxPortais);
    int* resultadoAEstrela = a_estrela(g, 0, n - 1, energia, maxPortais);

    std::cout << resultadoDijkstra[0] << " " << resultadoAEstrela[0] << "\n";

    delete[] resultadoDijkstra;
    delete[] resultadoAEstrela;
}

int main() {
    resolver();
    return 0;
}
