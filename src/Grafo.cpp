#include "Grafo.h"

No::No(int v, double p) : aresta(v, p), proximo(nullptr) {}

Grafo::Grafo(int n) : numVertices(n) {
    listaAdj = new No*[n];
    coordenadas = new Coordenada[n];
    for (int i = 0; i < n; ++i)
        listaAdj[i] = nullptr;
}

void Grafo::adicionarAresta(int u, int v, double peso) {
    No* novo = new No(v, peso);
    novo->proximo = listaAdj[u];
    listaAdj[u] = novo;
}

const No* Grafo::obterArestas(int u) const {
    return listaAdj[u];
}

void Grafo::definirCoordenada(int u, double x, double y) {
    coordenadas[u] = {x, y};
}

double Grafo::obterDistancia(int u, int v) const {
    return sqrt(pow(coordenadas[u].first - coordenadas[v].first, 2) +
                pow(coordenadas[u].second - coordenadas[v].second, 2));
}

int Grafo::tamanho() const {
    return numVertices;
}

Grafo::~Grafo() {
    delete[] coordenadas;
    for (int i = 0; i < numVertices; ++i) {
        No* atual = listaAdj[i];
        while (atual) {
            No* proximo = atual->proximo;
            delete atual;
            atual = proximo;
        }
    }
    delete[] listaAdj;
}
