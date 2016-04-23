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
	Pilha container;
	LSE lista1;

	Item it;

	for (int i = 0; i < 5; ++i) {
		it.setValor(i);
		container.empilha(it);
		container.mostra();
	}

	lista1.insere(container);

	lista1.mostra();


	return 0;
}
