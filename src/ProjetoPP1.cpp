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
	Pilha *c1 = new Pilha(); //Pilha *c2; Pilha *c3;
	LSE lista1; LSE lista2;


	for (int i = 0; i < 3; ++i) {
		Item *it = new Item();
		it->setValor(i);
		c1->empilha(it);
	}
	inserePilhas(lista1, c1, 1);
	lista1.mostra();

	Item *res = new Item();
	Item *par = new Item();
	res = c1->desempilha(par);

	c1->mostra();
	cout << res->getValor();

	/*Item *it2;
	for (int j = 3; j < 5; ++j) {
		it2->setValor(j);
		c2->empilha(it2);
	}
	inserePilhas(lista1, c2, 2);
	lista1.mostra();

	Item *it3;
	for (int k = 5; k < 8; ++k) {
		it3->setValor(k);
		c3->empilha(it3);
	}
	Item *it4;
	it4->setValor(200);
	c3->empilha(it4);
	inserePilhas(lista1, c3, 3);
	lista1.mostra();

	int r;
	r = lista1.busca(7);
	cout << r << endl;

	//Item it4;
//	it4.setValor(200);

	//c3.empilha(it4);
	c3->mostra();
	//c3.desempilha(it4);
	//c3.mostra();
	//c3.desempilha(it4);
	//c3.mostra();
	cout << "---------------------" << endl;
	//c3->desempilhaAux(c1);
	c3->mostra();

	lista1.mostra();
*/
	return 0;
}



