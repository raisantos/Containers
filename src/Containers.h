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
    Item() {}; // Construtor
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

class No { //no que guarda o item na pilha
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
    int indice;

public:
    Pilha(); // construtor
    No* getFundo(){
    	return fundo;
    }

    No* getTopo(){
        return topo;
    }

    int getIndice(){ //retorna qual é a pilha (1, 2, 3...)
    	return indice;
    }

    void setIndice(int indice){
    	this->indice = indice;
    }

    void desempilha(Pilha&);
    void empilha(Item);
    bool vazia();
    void mostra();
};

class NoPilha{ //no que guarda pilhas
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
    int tam = 0;
    bool vazia();
public:
    int getTam(){
    	return tam;
    }

    NoPilha* getPrim(){
    	return prim;
    }

    NoPilha* getUlt(){
    	return ult;
    }

    LSE();
    void insere(Pilha);
    int busca(Chave);
    void mostra();
    void insereLista(LSE);
};

void inserePilhas(LSE&, Pilha&, int);

#endif /* CONTAINERS_H_ */
