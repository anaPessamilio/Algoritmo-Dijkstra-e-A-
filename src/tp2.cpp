#include <chrono>
#include <iostream>
#include <fstream>
#include "../include/Grafo.h"
#include "../include/FilaDePrioridade.h"

const double INF = 1e9;

// Algoritmo de Dijkstra com medição de tempo
std::pair<int *, double> dijkstra(Grafo &g, int inicio, int objetivo, double energia, int maxPortais)
{
    auto start = std::chrono::high_resolution_clock::now();

    FilaDePrioridade conjuntoAberto;
    conjuntoAberto.adicionar(0, inicio, 0);

    double *dist = new double[g.tamanho()];
    int *contadorPortais = new int[g.tamanho()];
    for (int i = 0; i < g.tamanho(); ++i)
    {
        dist[i] = INF;
        contadorPortais[i] = 0;
    }
    dist[inicio] = 0;

    while (!conjuntoAberto.vazio())
    {
        auto parAtual = conjuntoAberto.remover();
        double custoAtual = parAtual.first;
        int atual = parAtual.second.first;
        int portaisUsados = parAtual.second.second;

        if (atual == objetivo && custoAtual <= energia && portaisUsados <= maxPortais)
        {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            int *resultado = new int[1];
            resultado[0] = 1; // Existe caminho
            return {resultado, duration.count()};
        }

        if (custoAtual > energia)
            continue;

        for (const No *no = g.obterArestas(atual); no != nullptr; no = no->proximo)
        {
            int vizinho = no->aresta.first;
            double peso = no->aresta.second;
            double novoCusto = custoAtual + peso;
            int novoContadorPortais = portaisUsados + (peso == 0 ? 1 : 0);
            if (novoCusto <= energia && novoCusto < dist[vizinho] && novoContadorPortais <= maxPortais)
            {
                dist[vizinho] = novoCusto;
                contadorPortais[vizinho] = novoContadorPortais;
                conjuntoAberto.adicionar(novoCusto, vizinho, novoContadorPortais);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    int *resultado = new int[1];
    resultado[0] = 0; // Não existe caminho
    return {resultado, duration.count()};
}

// Função heurística para o A*
double heuristica(const Grafo &g, int a, int b)
{
    return g.obterDistancia(a, b);
}

// Algoritmo A* com medição de tempo
std::pair<int *, double> a_estrela(Grafo &g, int inicio, int objetivo, double energia, int maxPortais)
{
    auto start = std::chrono::high_resolution_clock::now();

    FilaDePrioridade conjuntoAberto;
    conjuntoAberto.adicionar(0, inicio, 0);

    double *dist = new double[g.tamanho()];
    int *contadorPortais = new int[g.tamanho()];
    for (int i = 0; i < g.tamanho(); ++i)
    {
        dist[i] = INF;
        contadorPortais[i] = 0;
    }
    dist[inicio] = 0;

    while (!conjuntoAberto.vazio())
    {
        auto parAtual = conjuntoAberto.remover();
        double custoAtual = parAtual.first;
        int atual = parAtual.second.first;
        int portaisUsados = parAtual.second.second;

        if (atual == objetivo && custoAtual <= energia && portaisUsados <= maxPortais)
        {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            int *resultado = new int[1];
            resultado[0] = 1; // Existe caminho
            return {resultado, duration.count()};
        }

        if (custoAtual > energia)
            continue;

        for (const No *no = g.obterArestas(atual); no != nullptr; no = no->proximo)
        {
            int vizinho = no->aresta.first;
            double peso = no->aresta.second;
            double novoCusto = custoAtual + peso;
            int novoContadorPortais = portaisUsados + (peso == 0 ? 1 : 0);
            if (novoCusto <= energia && novoCusto < dist[vizinho] && novoContadorPortais <= maxPortais)
            {
                dist[vizinho] = novoCusto;
                contadorPortais[vizinho] = novoContadorPortais;
                conjuntoAberto.adicionar(novoCusto + heuristica(g, vizinho, objetivo), vizinho, novoContadorPortais);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    int *resultado = new int[1];
    resultado[0] = 0; // Não existe caminho
    return {resultado, duration.count()};
}

// Função principal para resolver o problema
void resolver()
{
    int n, m, k;
    std::ifstream arquivo("../grafo_aleatorio.txt");
    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo ../grafo_aleatorio.txt\n";
        return;
    }
    else
    {
        std::cout << "Arquivo aberto com sucesso: ../grafo_aleatorio.txt\n";
    }

    arquivo >> n >> m;

    if (arquivo.fail())
    {
        std::cerr << "Erro ao ler valores de n e m do arquivo.\n";
        arquivo.close();
        return;
    }

    Grafo g(n);

    // Leitura das trilhas e cálculo da distância euclidiana
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        double peso;
        arquivo >> u >> v >> peso;
        g.adicionarAresta(u, v, peso);
    }

    // Leitura dos portais
    arquivo >> k;
    for (int i = 0; i < k; ++i)
    {
        int u, v;
        arquivo >> u >> v;
        g.adicionarAresta(u, v, 0); // Peso 0 para portais
    }

    arquivo.close();

    double energia;
    int maxPortais;
    std::cin >> energia >> maxPortais;

    auto resultadoDijkstra = dijkstra(g, 0, n - 1, energia, maxPortais);
    auto resultadoAEstrela = a_estrela(g, 0, n - 1, energia, maxPortais);

    std::cout << resultadoDijkstra.first[0] << " " << resultadoAEstrela.first[0] << "\n";

    // Salvando os tempos de execução em um arquivo CSV
    std::ofstream arquivo_csv("tempos_execucao.csv", std::ios::app);
    if (arquivo_csv.is_open())
    {
        arquivo_csv << "Algoritmo,Tempo de Execução (s)\n";
        arquivo_csv << "Dijkstra," << resultadoDijkstra.second << "\n";
        arquivo_csv << "A*," << resultadoAEstrela.second << "\n";
        arquivo_csv.close();
        std::cout << "Tempos de execução salvos em tempos_execucao.csv\n";
    }
    else
    {
        std::cerr << "Erro ao abrir o arquivo tempos_execucao.csv para escrita.\n";
    }

    delete[] resultadoDijkstra.first;
    delete[] resultadoAEstrela.first;
}

int main()
{
    resolver();
    return 0;
}
