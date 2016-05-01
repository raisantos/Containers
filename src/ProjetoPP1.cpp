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
	Pilha c1; Pilha c2; Pilha c3;
	LSE lista1; LSE lista2;

	Item it;
	for (int i = 0; i < 3; ++i) {
		it.setValor(i);
		c1.empilha(it);
	}
	inserePilhas(lista1, c1, 1);
	lista1.mostra();

	Item it2;
	for (int j = 3; j < 5; ++j) {
		it2.setValor(j);
		c2.empilha(it2);
	}
	inserePilhas(lista1, c2, 2);
	lista1.mostra();

	Item it3;
	for (int k = 5; k < 8; ++k) {
		it3.setValor(k);
		c3.empilha(it3);
	}
	inserePilhas(lista1, c3, 3);
	lista1.mostra();

	int r;
	r = lista1.busca(7);
	cout << r << endl;

	return 0;
}
