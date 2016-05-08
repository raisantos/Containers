//============================================================================
// Name        : PP1_AED.cpp
// Author      : Jailson & Rai Soledade & Richardson Souza
// Version     :
// Copyright   : Your copyright notice
// Description : Projeto PP1 de AED in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#define ORIGEM 2
#define DESTINO 1
#define TEMP 0

typedef int Chave;

class Contain {
private:
    Chave valor;

public:
    Contain() {};
    Contain(int valor): valor(valor) { }

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
	Contain *item;
    No *prox;

    No() {}

    Contain* getContain() {
        return item;
    }

    void setContain(Contain *item) {
        this -> item = item;
    }

    No* getProx() {
        return prox;
    }

    void setProx(No *prox) {
        this->prox = prox;
    }

};

class Pilha {
private:
    No *fundo, *topo;
    int estado;

public:
    Pilha();

    No* getFundo(){
    	return fundo;
    }

    void setFundo(No *fundo) {
    	this->fundo = fundo;
    }

    No* getTopo(){
        return topo;
    }

    void setTopo(No *topo){
    	this->topo = topo;
    }

    int getEstado(){
    	return estado;
    }

    void setEstado(int estado){
    	this->estado = estado;
    }

    Contain* desempilha(Contain*);
    void empilha(Contain*);
    bool vazia();
    void mostra();
};

Pilha::Pilha() {
    fundo = new No();
    topo = fundo;
    estado = TEMP;
}

bool Pilha::vazia() {
	return topo == fundo;
}

void Pilha::empilha(Contain *item) {
    No *aux = new No();
    topo -> setContain(item);
    aux -> setProx(topo);
    topo = aux;
}

Contain* Pilha::desempilha(Contain *item) {
    if (vazia()) {
        cout << "pilha vazia: impossível remover item\n";
    }
    else {
        No *aux = topo;
        topo = topo->getProx();
        item = topo->getContain();
        delete aux;
        return item;
    }
}

void Pilha::mostra() {
    for (No *nav = topo->getProx(); nav != NULL; nav = nav->getProx()) {
        nav->getContain()->mostra();
        cout << " ";
    }

    cout << "\n";
}

class NoPilha{
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

public:

    NoPilha* getPrim(){
    	return prim;
    }
    void setPrim (NoPilha *prim) {
    	this->prim = prim;
    }

    NoPilha* getUlt(){
    	return ult;
    }
    void setUlt (NoPilha *ult) {
    	this->ult =ult;
    }

    LSE();
    void insere(Pilha*);
    void busca(Chave);
    void mostra();
};

LSE::LSE() {
	prim = new NoPilha();
	prim -> setProx(NULL);
	ult = prim;
}

void LSE::insere(Pilha* p) {
    ult->setProx(new NoPilha());
    ult=ult->getProx();
    ult->setProx(NULL);
    ult->setPilha(p);
}

void LSE::mostra() {
    NoPilha *p = getPrim()->getProx();
    while (p != NULL) {
    	cout << "i:" << p->getPilha()->getEstado() << " ";
        p->pilha->mostra();
        p = p->getProx();
    }
}

void LSE::busca(Chave chave){
	NoPilha *p = prim->getProx();

	while (p != NULL) {
		p->getPilha()->mostra();
	}
}

/*
 * Funcao ajusta a pilha de origem.
 * O container em questao deve esta no topo para poder ser empilhado na pilha de destino
 * Essa funcao desempilha o container da pilha ate que o topo seja o container requerido
 */
void ajustaOrigem (LSE *lista, Pilha *pTemp, int container) {

	NoPilha *listaAux = new NoPilha();
	listaAux = lista->getPrim()->getProx();
	while (pTemp->getTopo()->getProx()->getContain()->getValor() != container) {	// Enquanto o TOPO for diferente do valor do container é feito o desempilhamento
		Contain *ctemp = new Contain ();
		ctemp = pTemp->desempilha(ctemp);

		if (listaAux == NULL) {										// Essa condicao verificar se já chegamos no fim da lista
			listaAux = lista->getPrim()->getProx();
		}
		while (listaAux->getPilha()->getEstado() != TEMP) {
			listaAux = listaAux->getProx();
		}
		listaAux->getPilha()->empilha(ctemp);
		listaAux = listaAux->getProx();
	}
}

/**
	Caso o container que estamos buscando,
	ja esteja na pilha de destino
	Temos que verificar sua posicao
	Essa funcao realiza ajuste na pilha de Destino
	Deixando o Container em questao no topo
 */

void ajustaDestino (LSE *lista, Pilha *pTemp) {
	Contain *ctemp = new Contain ();
	NoPilha *listaAux = new NoPilha();
	listaAux = lista->getPrim()->getProx();
	ctemp = pTemp->desempilha(ctemp);
	if (listaAux == NULL) {
		listaAux = lista->getPrim()->getProx();
	}
	while (listaAux->getPilha()->getEstado() != TEMP) {
		listaAux = listaAux->getProx();
	}
	listaAux->getPilha()->empilha(ctemp);
	listaAux->getPilha()->setEstado(ORIGEM);
}

/**
	Ajusta a pilha de Destino tomando como referencia
	o valor da variavel cont
 */

void ajustaPosicao (LSE *lista, Pilha *pTemp, int cont) {

	NoPilha *listaAux = new NoPilha();
	listaAux = lista->getPrim()->getProx();

	while (cont != 0) {
		Contain *ctemp = new Contain ();
		ctemp = pTemp->desempilha(ctemp);

		if (listaAux == NULL) {
			listaAux = lista->getPrim()->getProx();
		}

		while (listaAux->getPilha()->getEstado() != TEMP) {
			listaAux = listaAux->getProx();
		}
		listaAux->getPilha()->empilha(ctemp);
		listaAux = listaAux->getProx();
		cont--;
	}

}

/**
	Retorna o valor da variavel cont decrementado de -1
	Server de referencia para verificar em que posicao o conteiner deve entrar
 */

int contaPilha (Pilha *pTemp, int container){
	int cont = 0;
	No *pilhaTemp = pTemp->getTopo()->getProx();
	while (pilhaTemp->getContain()->getValor() != container) {
		pilhaTemp = pilhaTemp->getProx();
	}
	while (pilhaTemp != NULL) {
		cont = cont + 1;
		pilhaTemp = pilhaTemp->getProx();
	}

	return cont-1;
}

/**
	Funcao é responsavel por realizar a busca pelo container
	Apos encontrar o container requesita outras funcoes para ajustara operacao
 */
void buscarContainer (LSE *lista, int container, int dist){

	bool continuar = true;

	NoPilha *listaAux = new NoPilha();
	listaAux = lista->getPrim()->getProx();

	while (continuar && listaAux != NULL) {
		No *pilhaTemp = new No();
		pilhaTemp = listaAux->getPilha()->getTopo()->getProx();

		while (continuar && pilhaTemp != NULL) {
			if (pilhaTemp->getContain()->getValor() == container){
				if (listaAux->getPilha()->getEstado() == TEMP) {			// Verifica se o container encontrado esta numa pilha TEMP (0) (Temporaria)
					listaAux->getPilha()->setEstado(ORIGEM);				// Se estiver alteramos o estado da pilha par ORIGEM (2)
					ajustaOrigem(lista,listaAux->getPilha(), container);	// Funcao ajusta a pilha ate que o topo seja igual ao container
				}
				else {
					int cont = contaPilha(listaAux->getPilha(), container);	// Incrementa a variavel cont

					if (cont > dist) {
						ajustaOrigem(lista,listaAux->getPilha(), container);// Ajusta a pilha para que o container requerido esteja no topo

						ajustaDestino(lista,listaAux->getPilha());			// Pega o container requerido e move para uma pilha

						ajustaPosicao(lista,listaAux->getPilha(),cont);		// Ajusta a pilha de Destino tendo como referencia a variavel cont

					}
					else if (cont < dist) {
						// --- implementando ---
					}
				}
				continuar = false;
			}
			else {
				pilhaTemp = pilhaTemp->getProx();							// Passa para o proximo container
			}
		}
		listaAux = listaAux->getProx();										// passa para a proxima pilha
	}
}

/**
	Funcao principal
 */

int main(int argc, const char * argv[]) {

	LSE *e1 = new LSE();
	LSE *e2 = new LSE();

	Pilha *p1 = new Pilha();
	Pilha *p2 = new Pilha();
	Pilha *p3 = new Pilha();
	Pilha *p4 = new Pilha();

	/* Bloco para entrada
	int entrada;

	// le a primeira lista e alimenta
	cin >> entrada;
	while (entrada != -1){
		Pilha *p = new Pilha();
		while (entrada != -1) {
			Contain *c = new Contain();
			c->setValor(entrada);
			p->empilha(c);
			cin >> entrada;
		}
		e1->insere(p);
		cin >> entrada;
	}

	// le a segunda lista e alimenta
	cin >> entrada;
	while (entrada != -1){
		Pilha *p = new Pilha();
		while (entrada != -1) {
			Contain *c = new Contain();
			c->setValor(entrada);
			p->empilha(c);
			cin >> entrada;
		}
		e2->insere(p);
		cin >> entrada;
	}
	*/

	for (int i = 1; i <= 4; ++i) {
		Contain *c1 = new Contain();
		c1->setValor(i);
		p1->empilha(c1);
	}
	p1->setEstado(DESTINO);
	e1->insere(p1);

	for (int i = 5; i <= 15; ++i) {
		Contain *c2 = new Contain();
		c2->setValor(i);
		p2->empilha(c2);
	}
	e1->insere(p2);

	for (int i = 16; i <= 18; ++i) {
		Contain *c3 = new Contain();
		c3->setValor(i);
		p3->empilha(c3);
	}
	e1->insere(p3);

	for (int i = 19; i <= 27; ++i) {
		Contain *c4 = new Contain();
		c4->setValor(i);
		p4->empilha(c4);
	}
	e1->insere(p4);

	cout << "Antes: \n";
	e1->mostra();

	int conteiner = 3;
	int dist = 1;

	cout << "container procurado: " << conteiner << "\n";

	buscarContainer(e1,conteiner,dist);

	cout << "Depois: \n";
	e1->mostra();


	return 0;
}

