//============================================================================
// Name        : Saida.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
typedef int Chave;

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
    Item *item;
    No *prox;

    No() {}

    Item *getItem() {
        return item;
    }

    void setItem(Item *item) {
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
    int indice; //usar como tamanho da pilha

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

    Item* desempilha(Item*);
    void empilhaAux(Item*);
    void desempilhaAux(Pilha&);
    void empilha(Item*);
    bool vazia();
    void mostra();
};

class NoPilha{ //no que guarda pilhas
public:
	Pilha *pilha;
	NoPilha *prox;

	NoPilha(){};

	Pilha *getPilha() {
	        return pilha;
	    }

	    void setPilha(Pilha *pilha) {
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
    void insere(Pilha*);
    void busca(Chave);
    void mostra();
    void insereLista(LSE);
};

Pilha::Pilha() {
    fundo = new No(); // nó cabeça
    topo = fundo;
    setIndice(0);
}

void Pilha::empilha(Item *item) {
    No *aux = new No();
    topo -> setItem(item);
    aux -> setProx(topo);
    topo = aux;
    //
    int a = getIndice();
    setIndice(a+1);
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
        //
        int a = getIndice();
        setIndice(a-1);
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

void imprimeTopo(NoPilha *nave, int loop){
	while(nave != NULL){
		Pilha *aux = new Pilha();
		Item *it = new Item();
		aux = nave->getPilha();
		//if(aux->getIndice() == TAM da maior pilha entao imprime topo, senao imprime espaco)
		if(aux->getIndice() != loop){
			if(aux->getTopo()->getProx()->getItem()->getValor() > 99){
				cout << "    ";
				nave = nave->getProx();
			}
			else if(aux->getTopo()->getProx()->getItem()->getValor() > 9){
				cout << "   ";
				nave = nave->getProx();
			}
			else{
				cout << "  ";
				nave = nave->getProx();
			}
		}
					//
		else{
			cout << aux->getTopo()->getProx()->getItem()->getValor() << " ";
			aux->desempilha(it);
			nave = nave->getProx();
		}
	}
}

int main() {
	Pilha *c1 = new Pilha(); Pilha *c2 = new Pilha(); Pilha *c3 = new Pilha();
	LSE lista1; //LSE lista2;

	for (int i = 15; i < 19; ++i) {
		Item *it = new Item();
		it->setValor(i);
		c1->empilha(it);
	}
	lista1.insere(c1);
	//lista1.mostra();

	for (int j = 97; j < 99; ++j) {
		Item *it2 = new Item();
		it2->setValor(j);
		c2->empilha(it2);
	}
	lista1.insere(c2);
	//lista1.mostra();

	for (int k = 20; k < 25; ++k) {
		Item *it3 = new Item();
		it3->setValor(k);
		c3->empilha(it3);
	}
	lista1.insere(c3);
	lista1.mostra();

	//cout << c1->getIndice() << endl;
	//cout << c2->getIndice() << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;

	NoPilha *nave = lista1.getPrim()->getProx();

	bool continuar = 1;
	while(continuar){
		int cont = 0;
		while(nave != NULL){
			if(nave->getPilha()->vazia()){
				cont++;
			}
			nave = nave->getProx();
		}
		if(cont == lista1.getTam()){
			continuar = 0;
		}
		else{
			nave = lista1.getPrim()->getProx();
			//verificar o tamanho da maior pilha para comparacao com todas as pilhas
			int tam = nave->getPilha()->getIndice(); //pega o tamanho da primeira pilha
			while(nave != NULL){
				Pilha *p = new Pilha();
				p = nave->getPilha();
				if(p->getIndice() > tam){
					tam = p->getIndice();
				}
				nave = nave->getProx();
			}
			//armazenar num int
			nave = lista1.getPrim()->getProx();
			int loop = tam;
			imprimeTopo(nave, loop);
			cout << endl;
		}
		nave = lista1.getPrim()->getProx();
	}

	return 0;
}
