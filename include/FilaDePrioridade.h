#ifndef FILADEPRIORIDADE_H
#define FILADEPRIORIDADE_H

#include <utility>

struct Elemento {
    double custo;
    int no;
    int portais;
    Elemento* proximo;
    
    Elemento(double c, int n, int p);
};

class FilaDePrioridade {
    Elemento* primeiro;

public:
    FilaDePrioridade();
    void adicionar(double custo, int no, int portais);
    typedef std::pair<int, int> IntPair; // Definindo o typedef aqui
    std::pair<double, IntPair> remover();
    bool vazio();
    ~FilaDePrioridade();
};

#endif // FILADEPRIORIDADE_H
