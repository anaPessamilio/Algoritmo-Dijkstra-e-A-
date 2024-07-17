#include "FilaDePrioridade.h"

Elemento::Elemento(double c, int n, int p)
    : custo(c), no(n), portais(p), proximo(nullptr) {}

FilaDePrioridade::FilaDePrioridade()
    : primeiro(nullptr) {}

void FilaDePrioridade::adicionar(double custo, int no, int portais) {
    Elemento* novo = new Elemento(custo, no, portais);

    if (!primeiro || custo < primeiro->custo) {
        novo->proximo = primeiro;
        primeiro = novo;
    } else {
        Elemento* atual = primeiro;
        while (atual->proximo && atual->proximo->custo <= custo) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}

std::pair<double, FilaDePrioridade::IntPair> FilaDePrioridade::remover() {
    Elemento* topo = primeiro;
    primeiro = primeiro->proximo;
    std::pair<double, IntPair> resultado = {topo->custo, {topo->no, topo->portais}};
    delete topo;
    return resultado;
}

bool FilaDePrioridade::vazio() {
    return primeiro == nullptr;
}

FilaDePrioridade::~FilaDePrioridade() {
    while (primeiro) {
        Elemento* proximo = primeiro->proximo;
        delete primeiro;
        primeiro = proximo;
    }
}
