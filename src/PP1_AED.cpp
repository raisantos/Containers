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
    	//cout << "i:" << p->getPilha()->getEstado() << " ";
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

		listaAux = lista->getPrim()->getProx();

		while (listaAux->getPilha()->getEstado() != TEMP) {
			if (listaAux == NULL) {										// Essa condicao verificar se já chegamos no fim da lista
				listaAux = lista->getPrim()->getProx();
			}
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

	listaAux = lista->getPrim()->getProx();

	while (listaAux->getPilha()->getEstado() != TEMP) {
		if (listaAux == NULL) {
			listaAux = lista->getPrim()->getProx();
		}
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

	while (cont != 0 && pTemp->vazia() != true) {
		Contain *ctemp = new Contain ();
		ctemp = pTemp->desempilha(ctemp);

		listaAux = lista->getPrim()->getProx();

		while (listaAux->getPilha()->getEstado() != TEMP) {
			if (listaAux == NULL) {
				listaAux = lista->getPrim()->getProx();
			}
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

	return cont;
}

int contaDestino (Pilha *pTemp){

	int cont = 0;
	No *pilhaTemp = pTemp->getTopo()->getProx();
	while (pilhaTemp != NULL) {
		cont = cont + 1;
		pilhaTemp = pilhaTemp->getProx();
	}

	return cont;
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

					//lista->mostra();

					listaAux = lista->getPrim()->getProx();

					while (listaAux->getPilha()->getEstado() != DESTINO) {	// Procurar pilha e destino
						if (listaAux == NULL) {
							listaAux = lista->getPrim()->getProx();
						}
						listaAux = listaAux->getProx();
					}

					int cont = contaDestino(listaAux->getPilha());			// Guarda a quantidade de containers
					if (cont > dist) {
						ajustaPosicao(lista,listaAux->getPilha(),cont);		// Ajusta a posicao
					}
					else if (cont == dist) {
						ajustaPosicao(lista,listaAux->getPilha(),cont);
					}

					listaAux = lista->getPrim()->getProx();

					while (listaAux->getPilha()->getEstado() != ORIGEM) {	// Retorna a pilha de ORIGEM
						if (listaAux == NULL) {								// Recomeca o ponteiro na lista se necessario
							listaAux = lista->getPrim()->getProx();
						}
						listaAux = listaAux->getProx();
					}

					Contain *ctemp = new Contain();
					ctemp = listaAux->getPilha()->desempilha(ctemp);
					listaAux->getPilha()->setEstado(TEMP);

					listaAux = lista->getPrim()->getProx();

					while (listaAux->getPilha()->getEstado() != DESTINO) {	// Procurar pilha e destino
						if (listaAux == NULL) { 							// Recomeca o ponteiro na lista
							listaAux = lista->getPrim()->getProx();
						}
						listaAux = listaAux->getProx();
					}
					listaAux->getPilha()->empilha(ctemp);
				}
				else {
					int cont = contaPilha(listaAux->getPilha(), container);	// Incrementa a variavel cont

					if (cont > dist) {
						ajustaOrigem(lista,listaAux->getPilha(), container);// Ajusta a pilha para que o container requerido esteja no topo
						ajustaDestino(lista,listaAux->getPilha());			// Pega o container requerido e move para uma pilha
						ajustaPosicao(lista,listaAux->getPilha(),cont);		// Ajusta a pilha de Destino tendo como referencia a variavel cont
					}

					else if (cont == dist) {
						break;
					}

					listaAux = lista->getPrim()->getProx();

					while (listaAux->getPilha()->getEstado() != ORIGEM) {	// Retorna a pilha de ORIGEM
						if (listaAux == NULL) {								// Recomeca o ponteiro na lista se necessario
							listaAux = lista->getPrim()->getProx();
						}
						listaAux = listaAux->getProx();
					}
					Contain *ctemp = new Contain();
					ctemp = listaAux->getPilha()->desempilha(ctemp);		// Desempilha o Container da pilha de ORIGEM
					listaAux->getPilha()->setEstado(TEMP);

					listaAux = lista->getPrim()->getProx();

					while (listaAux->getPilha()->getEstado() != DESTINO) {	// Procurar pilha e destino
						if (listaAux == NULL) { 							// Recomeca o ponteiro na lista
							listaAux = lista->getPrim()->getProx();
						}
						listaAux = listaAux->getProx();
					}
					listaAux->getPilha()->empilha(ctemp);					// Empilha o Container na pilha de DESTINO

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
	//LSE *e2 = new LSE();

	int entrada;

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

	e1->mostra();

	NoPilha *listaAux = e1->getPrim()->getProx();

	int dist = 0;
	cin >> entrada;
	while (entrada != -1){
		listaAux->getPilha()->setEstado(DESTINO);
		while (entrada != -1) {
			dist++;
			buscarContainer(e1,entrada,dist);
			//e1->mostra();
			cin >> entrada;
		}
		listaAux->getPilha()->setEstado(TEMP);
		listaAux = listaAux->getProx();
		dist = 0;
		cin >> entrada;
	}

	cout << "\n";

	e1->mostra();

	return 0;
}
