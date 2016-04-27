#include <iostream>
#include "Containers.h"
using namespace std;

int main() {
	Pilha container; Pilha container2;
	LSE lista1;

	Item it;
	for (int i = 0; i < 5; ++i) {
		it.setValor(i);
		container.empilha(it);
		container.mostra();
	}
	lista1.insere(container);

	lista1.mostra();

	Item it2;
	for (int j = 5; j < 10; ++j) {
		it2.setValor(j);
		container2.empilha(it2);
		container2.mostra();
	}
	lista1.insere(container2);

	lista1.mostra();
	
	cout <<"\n";
	lista1.busca(21);
	return 0;
}
