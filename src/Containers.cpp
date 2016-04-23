/*
 * Containers.cpp
 *
 *  Created on: 23 de abr de 2016
 *      Author: rsouza
 */

#include "Containers.h"

Pilha::Pilha() {
    fundo = new No(); // nó cabeça
    topo = fundo;
}

void Pilha::empilha(Item item) {
    No *aux = new No();
    topo -> setItem(item);
    aux -> setProx(topo);
    topo = aux;
}

bool Pilha::vazia() {
    return topo == fundo;
}

void Pilha::mostra() {
    cout << "Pilha: topo-> ";
    for (No *nav = topo->getProx(); nav != NULL;
                                   nav = nav->getProx()) {
        nav->getItem().mostra();
    }
    cout << "<- fundo\n";
}

LSE::LSE() {
    prim = new No(); // cabeça
    prim -> prox = NULL;
    ult = prim;
}


void LSE::insere(Pilha& p) {
    ult->prox = new No();
//    if (ult == nullptr) exit(1);
    ult = ult-> prox;
    ult -> prox = NULL;
    //apontar para a pilha criada
    //----> aqui <----
}

bool LSE::vazia() {
    return prim == ult;
}

No* LSE::pred(No* r) {
    No* p = prim;
    while (p->prox != r) {
        p = p->prox;
    }
    return p;
}


void LSE::mostra() {
    cout << "LISTA:\n";
    No *p = prim->prox;
    while (p != NULL) {
        p->item.mostra();
        p = p->prox;
    }
    cout << "\n";
}
