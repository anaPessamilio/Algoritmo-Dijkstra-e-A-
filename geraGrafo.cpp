#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estrutura para representar uma aresta
struct Aresta {
    int u, v;
    double peso;
};

// Função para gerar um grafo aleatório com 'V' vértices e 'E' arestas
Aresta* gerarGrafoAleatorio(int V, int E) {
    Aresta* arestas = new Aresta[E];
    srand(time(0)); // Seed para garantir aleatoriedade

    // Gerar 'E' arestas aleatórias
    for (int i = 0; i < E; ++i) {
        arestas[i].u = rand() % V;   // Vértice de origem aleatório
        arestas[i].v = rand() % V;   // Vértice de destino aleatório
        arestas[i].peso = (double)(rand() % 1000) / 10.0;  // Peso aleatório entre 0 e 99.9
    }

    return arestas;
}

int main() {
    int V = 10; // Número de vértices
    int E = 15; // Número de arestas

    Aresta* grafos = gerarGrafoAleatorio(V, E);

    // Salvar o grafo gerado em um arquivo
    ofstream arquivo("grafo_aleatorio.txt");
    if (arquivo.is_open()) {
        arquivo << V << " " << E << "\n";
        for (int i = 0; i < E; ++i) {
            arquivo << grafos[i].u << " " << grafos[i].v << " " << grafos[i].peso << "\n";
        }
        arquivo.close();
        cout << "Grafo aleatório gerado e salvo em grafo_aleatorio.txt\n";
    } else {
        cerr << "Não foi possível abrir o arquivo para escrita\n";
    }

    delete[] grafos;

    return 0;
}
