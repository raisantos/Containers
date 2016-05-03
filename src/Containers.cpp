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

void Pilha::empilha(Item *item) {
    No *aux = new No();
    topo -> setItem(item);
    aux -> setProx(topo);
    topo = aux;
}

void Pilha::empilhaAux(Item *item) {
    No *aux = new No();
    topo->setItem(item);
    aux->setProx(topo);
    topo = aux;
}

Item* Pilha::desempilha(Item* item) {
    if (vazia()) {
        cout << "pilha vazia: impossível remover item\n";
    }
    else {
        No *aux = topo;
        topo = topo->getProx();
        item = topo->getItem();
        delete aux;
        return item;
    }
}

void Pilha::desempilhaAux(Pilha &tPilha) {
    if (vazia()) {
        cout << "pilha vazia: impossível remover item\n";
    }
    else {
        No *aux = topo;
        No *tmp = new No();
        topo = topo->getProx();
        //item = topo->getItem();
        //delete aux;
        cout << aux->getItem()->getValor() << "\n";
        tPilha.topo->setItem(aux->getItem());
        tmp->setProx(tPilha.topo);
        tPilha.topo = tmp;
        tPilha.mostra();
    }
}

bool Pilha::vazia() {
    return topo == fundo;
}

void Pilha::mostra() {
    cout << "Pilha: topo-> ";
    for (No *nav = topo->getProx(); nav != NULL;
                                   nav = nav->getProx()) {
        nav->getItem()->mostra();
    }
    cout << "<- fundo\n";
}

LSE::LSE() {
    prim = new NoPilha(); // cabeça
    prim -> prox = NULL;
    ult = prim;
}

void LSE::insere(Pilha* p) {
    ult->prox = new NoPilha();
//    if (ult == nullptr) exit(1);
    ult = ult-> prox;
    ult -> prox = NULL;
    ult->pilha = p;
    tam++;
    //apontar para a pilha criada
    //----> aqui <----
}
//-------------------------------------------------------------------------------------------
ListaAux::ListaAux() {
    prim = new No(); // cabeça
    prim -> prox = NULL;
    ult = prim;
}


void ListaAux::insere(Item* x){
	ult->prox = new No();
	ult = ult->prox;
	ult->prox = NULL;
	ult->item = x;
	tam++;
}

void ListaAux::mostra(){
	cout << "Lista: Inicio-> ";
	for (No *nav = prim->getProx(); nav != NULL;
	                                   nav = nav->getProx()) {
	        nav->getItem()->mostra();
	    }
	    cout << "<- Fim\n";
}

ListaEntrada::ListaEntrada() {
    prim = new NoLista(); // cabeça
    prim->setProx(NULL);
    ult = prim;
}

void ListaEntrada::insere(ListaAux *l){
	ult->setProx(new NoLista());
	ult = ult->getProx();
	ult->setProx(NULL);
	ult->setListaAux(l);
	tam++;
}

void ListaEntrada::mostra() {
    cout << "LISTA:\n";
    NoLista *p = getPrim()->getProx();
    while (p != NULL) {
        p->getListaAux()->mostra();
        p = p->getProx();
    }
    cout << "\n";
}

//-------------------------------------------------------------------------------------------
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
        p->pilha->mostra();
        p = p->prox;
    }
    cout << "\n";
}

void LSE::busca(Chave chave){
	NoPilha *p = prim->getProx();
	while(p != NULL){
		No *aux = p->getPilha()->getTopo()->getProx();
		while(aux->getItem()->getValor()!= chave){
			p->getPilha()->setIndice(2); //indeice da pilha alvo
			if(p->getPilha()->getTopo()->getProx()->getItem()->getValor() == chave){
					//funcao para empilhar o item ao destino
			}
			else{
				//desempilhar os itens ate chegar no item com a chave
				while(p->getPilha()->getTopo()->getProx()->getItem()->getValor() != chave){
					Item *aux = new Item(); Item *ret = new Item();
					ret = p->getPilha()->desempilha(aux);
					NoPilha *r = prim->getProx();
					while(r != NULL){
						if(r->getPilha()->getIndice() == 0){
							r->getPilha()->empilha(ret);
							break;
						}
						else{
							r = r->getProx();
						}
					}
				}
			}
				//return aux->getItem();
				/*int x;
				x = p->getPilha()->getIndice();
				int &ref = x;
				return ref;*/
			}

			aux = aux->getProx();
		}
	}
		p = p->getProx();
	}
	//return NULL;
}

void inserePilhas(LSE &lista, Pilha *p, int indice){
	p->setIndice(indice);
	lista.insere(p);
}
