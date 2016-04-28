//============================================================================
// Name        : ProjetoPP1.cpp
// Author      : Rai Soledade & Richardson Souza
// Version     :
// Copyright   : Your copyright notice
// Description : PP1 in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Containers.h"
using namespace std;

int main() {
	Pilha container; Pilha container2; Pilha container3;
	LSE lista1; LSE lista2;

	Item it;
	for (int i = 0; i < 5; ++i) {
		it.setValor(i);
		container.empilha(it);
		container.mostra();
	}
	lista1.insere(container);
	lista2.insere(container);

	lista1.mostra();

	Item it2;
	for (int j = 5; j < 10; ++j) {
		it2.setValor(j);
		container2.empilha(it2);
		container2.mostra();
	}
	lista1.insere(container2);
	lista2.insere(container2);

	lista1.mostra();
	lista2.mostra();
	cout << lista1.getTam() << endl;
	cout << lista2.getTam() << endl;

	Item it3;
	for (int k = 10; k < 15; ++k) {
		it3.setValor(k);
		container3.empilha(it3);
		container3.mostra();
	}
	lista1.insere(container3);

	lista1.mostra();
	No *r = new No();
	r = lista1.busca(13);
	r->getItem().mostra();
	//cout << container.getTopo()->getProx()->getItem().getValor() << endl;
	//cout << lista1.getPrim()->getProx()->getPilha().getTopo()->getProx()->getItem().getValor() << endl;
	//for (int var = 0; var < lista2.getTam(); var++) {
	/*	NoPilha *p = lista1.getPrim();
		NoPilha *p2 = lista2.getPrim();

		while(p != NULL){
			if(p->getPilha().getTopo()->getItem().getValor() == p2->getPilha().getTopo()->getItem().getValor()){
				cout << "ok" << endl;
				cout << p->getPilha().getTopo()->getItem().getValor() << endl;
				cout << p2->getPilha().getTopo()->getItem().getValor() << endl;
				cout << endl;
			}
			p = p->prox;
			p2 = p2->prox;
		}
	//}*/
	return 0;
}

