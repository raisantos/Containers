/*
 * Containers.h
 *
 *  Created on: 23 de abr de 2016
 *      Author: rsouza
 */

#ifndef CONTAINERS_H_
#define CONTAINERS_H_

#include <iostream>
using namespace std;
typedef int Chave;

// Número
class Item {
private:
    Chave valor;

public:
    Item() { } // Construtor
    Item(int valor): valor(valor) { }

    int getValor() {
        return valor;
    }

    void setValor(int valor) {
        this -> valor = valor;
    }

    void mostra() {
        cout << valor << " ";
    }
};

class No {
public:
    Item item;
    No *prox;

    No() {}

    Item getItem() {
        return item;
    }

    void setItem(Item item) {
        this -> item = item;
    }

    No* getProx() {
        return prox;
    }

    void setProx(No* prox) {
        this -> prox = prox;
    }
};

class Pilha {
private:
    No *fundo, *topo;

public:
    Pilha(); // construtor
    void empilha(Item);
    bool vazia();
    void mostra();
};

class NoPilha{ //no de pilhas
public:
	Pilha pilha;
	NoPilha *prox;

	NoPilha(){};

	Pilha getPilha() {
	        return pilha;
	    }

	    void setPilha(Pilha pilha) {
	        this -> pilha = pilha;
	    }

	    NoPilha* getProx() {
	        return prox;
	    }

	    void setProx(NoPilha* prox) {
	        this -> prox = prox;
	    }
};


class LSE {
private:
    NoPilha *prim, *ult;
    NoPilha* pred(NoPilha*);
    bool vazia();
public:
    LSE();
    void insere(Pilha);
    NoPilha* busca(Chave);
    void mostra();
};

#endif /* CONTAINERS_H_ */
