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

void LSE::busca(Chave chave){ //entrei na busca com a chave do item ataul da listaaux atual da lista2
	NoPilha *p = prim->getProx(); //comeca a busca desde a primeira pilha da lista1
	p->getPilha()->mostra();
	while(p != NULL){
		No *aux = p->getPilha()->getTopo()->getProx();//pega o primeiro no da pilha
		cout << aux->getItem()->getValor() << endl;
		while(aux->getItem()->getValor()!= chave && aux != NULL){ //enquanto o valor do item desse no for diferente da chave e de null
			//p->getPilha()->setIndice(2); //indeice da pilha alvo						//anda para o proximo no da pilha
			aux = aux->getProx();
			cout << aux->getItem()->getValor();
		}

		if(aux != NULL){ //se aux é igual a null, o item nao esta nesta pilha, entao tem que ir p proxima
			// OBS: verificar se a pilha do item de chave encontrada tbm é a pilha de destino 'indice 2'
			/*if(p->getPilha()->getTopo()->getProx()->getItem()->getValor() == chave){
					//OBS: como empilhar o item na pilha de destino (indice 2)
					//empilhar o item que esta no topo da pilha atual, na pilha de destino(indice 2)
			}
			else{*/
				//desempilhar os itens ate chegar no item com a chave
			p->getPilha()->setIndice(2); // indice 2 (origem)
			while(p->getPilha()->getTopo()->getProx()->getItem()->getValor() != chave){
				Item *aux = new Item(); Item *ret = new Item();
				ret = p->getPilha()->desempilha(aux);
				NoPilha *r = prim->getProx();
				//while(r != NULL){ //OBS: melhorar a forma de desempilhar nas pilhas temporarias
				while(r->getPilha()->getIndice() != 0){
					r = r->getProx();
				}
				r->getPilha()->empilha(ret);
				//break;
					//else{
						//r = r->getProx();
			}



				//}
		}
			//}

		//}
		else{
			p = p->getProx();
		}
	}
}


//return aux->getItem();
/*int x;
				x = p->getPilha()->getIndice();
				int &ref = x;
				return ref;*/

void inserePilhas(LSE &lista, Pilha *p, int indice){
	p->setIndice(indice);
	lista.insere(p);
}
