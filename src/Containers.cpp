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

void Pilha::empilhaTemp(Pilha &p, Item &item) {
    No *aux = new No();
    p.topo -> setItem(item);
    aux -> setProx(p.topo);
    p.topo->setItem(item);
}

void Pilha::desempilha(Pilha &p,Pilha &pTemp, Item &item){
	//No *aux = p.topo;
	Item aux = p.topo->getProx()->getItem();
	p.topo = p.topo->getProx();
	item = p.topo->getItem();
	empilhaTemp(pTemp, aux);
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
    tam++;
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

int LSE::busca(Chave chave){
	NoPilha *p = prim->getProx();
	while(p != NULL){
		No *aux = p->getPilha().getTopo()->getProx();
		while(aux != NULL){
			if(aux->getItem().getValor() == chave){
				int x;
				x = p->getPilha().getIndice();
				int &ref = x;
				return ref;
			}
			else{
				aux = aux->getProx();
			}
		}
		p = p->getProx();
	}
	return NULL;
}

void inserePilhas(LSE &lista, Pilha &p, int indice){
	p.setIndice(indice);
	lista.insere(p);
}
