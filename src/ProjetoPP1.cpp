/*
 * ProjetoPP1.cpp
 *
 *  Created on: 1 de mai de 2016
 *      Author: raisantos
 */
#include <iostream>
#include "Containers.h"
using namespace std;

/*void empilhaTemp(Pilha &p, Item &item) {
    No *aux = new No();
    p.topo -> setItem(item);
    aux -> setProx(p.topo);
    p.topo->setItem(item);
}

void desempilha(Pilha &p,Pilha &pTemp, Item &item){
	//No *aux = p.topo;
	Item aux = p.topo->getItem();
	p.topo = p.topo->getProx();
	item = p.topo->getItem();
	empilhaTemp(pTemp, aux);
}*/

int main(int argc, const char * argv[]) {
	Pilha *c1 = new Pilha(); Pilha *c2 = new Pilha(); Pilha *c3 = new Pilha();
	LSE lista1; //LSE lista2;


	for (int i = 0; i < 3; ++i) {
		Item *it = new Item();
		it->setValor(i);
		c1->empilha(it);
	}
	inserePilhas(lista1, c1, 0);
	//lista1.mostra();

	for (int j = 3; j < 5; ++j) {
		Item *it2 = new Item();
		it2->setValor(j);
		c2->empilha(it2);
	}
	inserePilhas(lista1, c2, 0);
	//lista1.mostra();

	for (int k = 5; k < 8; ++k) {
		Item *it3 = new Item();
		it3->setValor(k);
		c3->empilha(it3);
	}
	inserePilhas(lista1, c3, 0);
	lista1.mostra();

	/*Item *res = new Item();
	Item *par = new Item();
	res = lista1.getPrim()->getProx()->getPilha()->desempilha(par);

	//c1->mostra();
	cout << "valor desempilhado : " << res->getValor() << endl << endl;

	lista1.getPrim()->getProx()->getProx()->getPilha()->empilha(res);

	lista1.mostra();

	cout << "LISTA DE LISTAS" << endl << endl;*/

	ListaAux *l1 = new ListaAux(); ListaAux *l2 = new ListaAux(); ListaAux *l3 = new ListaAux();
	ListaEntrada lista2;

	for (int i = 3; i < 5; ++i) {
		Item *it3 = new Item();
		it3->setValor(i);
		l1->insere(it3);
	}
	lista2.insere(l1);
	//lista2.mostra();

	for (int i = 5; i < 8; ++i) {
		Item *it4 = new Item();
		it4->setValor(i);
		l3->insere(it4);
	}
	lista2.insere(l3);
	//lista2.mostra();

	for (int i = 0; i < 3; ++i) {
		Item *it5 = new Item();
		it5->setValor(i);
		l2->insere(it5);
	}
	lista2.insere(l2);
	lista2.mostra();

	cout << lista1.getPrim()->getProx()->getPilha()->getTopo()->getProx()->getItem()->getValor();

	NoLista *l = lista2.getPrim()->getProx();
	//setar a primeira pilha da lista 1 como alvo;
	NoPilha *q = lista1.getPrim()->getProx();
	q->getPilha()->setIndice(2); //indeice 2 = pra onde devo jogar o item que achar
	while(l != NULL){
		No *itlista = l->getListaAux()->getPrim()->getProx(); //no que pega a primeira lista da lista2
		while(itlista != NULL){
			int aux = itlista->getItem()->getValor();
			lista1.busca(aux);
			itlista = itlista->getProx(); //navega na listaaux da lista2
		}
		l = l->getProx(); //quando itlista chegar a null, acabou os elementos da lista, entao vai para a proxima lista
		q->getPilha()->setIndice(0); //a pilha da lista1 correspondente a listaaux da lista2 foi ordenada, fica como temporaria
		q = q->getProx(); //como a proxima lista foi incrementada, incrementa a pilha tbm
		q->getPilha()->setIndice(2);//lista2 andou, lista 1 andar tbm, para mudar o indice alvo e deixar antigo alvo temporario
	}

	//cout << "Pilha 3 : " << endl;

	lista1.mostra();

	return 0;
}

