#ifndef GRAFO_H
#define GRAFO_H

#include <cmath>
#include <utility>

typedef std::pair<int, int> Aresta;
typedef std::pair<double, double> Coordenada;

class Grafo {
    double** matrizAdj;
    Coordenada* coordenadas;
    int numVertices;

public:
    Grafo(int n);
    void adicionarAresta(int u, int v, double peso);
    double obterAresta(int u, int v) const;
    void definirCoordenada(int u, double x, double y);
    double obterDistancia(int u, int v) const;
    int tamanho() const;
    ~Grafo();
};

#endif // GRAFO_H
