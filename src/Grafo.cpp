#include "../include/Grafo.h"

Grafo::Grafo(int n) : numVertices(n) {
    matrizAdj = new double*[n];
    for (int i = 0; i < n; ++i) {
        matrizAdj[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            matrizAdj[i][j] = INFINITY; // Inicializa com infinito (sem aresta)
        }
    }
    coordenadas = new Coordenada[n];
}

void Grafo::adicionarAresta(int u, int v, double peso) {
    matrizAdj[u][v] = peso;
}

double Grafo::obterAresta(int u, int v) const {
    return matrizAdj[u][v];
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
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;
}
