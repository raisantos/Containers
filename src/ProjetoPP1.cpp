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
	for (int i = 0; i < 3; ++i) {
		it.setValor(i);
		container.empilha(it);
	}
	inserePilhas(lista1, container, 1);
	lista1.mostra();

	Item it2;
	for (int j = 3; j < 5; ++j) {
		it2.setValor(j);
		container2.empilha(it2);
	}
	inserePilhas(lista1, container2, 2);
	lista1.mostra();

	Item it3;
	for (int k = 5; k < 8; ++k) {
		it3.setValor(k);
		container3.empilha(it3);
	}
	inserePilhas(lista1, container3, 3);

	lista1.mostra();

	int r;
	r = lista1.busca(0);
	cout << r << endl;

	return 0;
}

