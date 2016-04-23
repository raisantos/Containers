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
    prim = new NoPilha(); // cabeça
    prim -> prox = NULL;
    ult = prim;
}


void LSE::insere(Pilha p) {
    ult->prox = new NoPilha();
//    if (ult == nullptr) exit(1);
    ult = ult-> prox;
    ult -> prox = NULL;
    ult->pilha = p;
    //apontar para a pilha criada
    //----> aqui <----
}

bool LSE::vazia() {
    return prim == ult;
}

NoPilha* LSE::pred(NoPilha* r) {
    NoPilha *p = prim;
    while (p->prox != r) {
        p = p->prox;
    }
    return p;
}


void LSE::mostra() {
    cout << "LISTA:\n";
    NoPilha *p = prim->prox;
    while (p != NULL) {
        p->pilha.mostra();
        p = p->prox;
    }
    cout << "\n";
}