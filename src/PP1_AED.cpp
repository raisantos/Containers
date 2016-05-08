//============================================================================
// Name        : PP1_AED.cpp
// Author      : Jailson & Rai Soledade & Richardson Souza
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#define ORIGEM 2
#define DESTINO 1
#define TEMP 0

typedef int Chave;

/*template<typename T>
void f(T s)
{
    cout << s << '\n';
}*/

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
    fundo = new No(); // nó cabeça
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
    //cout << " ";
    for (No *nav = topo->getProx(); nav != NULL; nav = nav->getProx()) {
        nav->getContain()->mostra();
        cout << " ";
    }

    cout << "\n";
}

class NoPilha{ //no que guarda pilhas
public:
	Pilha *pilha;
	NoPilha *prox;
//public:
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
    //void inserePilhas(Pilha*);
};

LSE::LSE() {
	prim = new NoPilha();
	prim -> setProx(NULL);
	ult = prim;
}

void LSE::insere(Pilha* p) {
    ult->setProx(new NoPilha());
//    if (ult == nullptr) exit(1);
    ult=ult->getProx();
    ult->setProx(NULL);
    ult->setPilha(p);
    //apontar para a pilha criada
    //----> aqui <----
}

void LSE::mostra() {
    NoPilha *p = getPrim()->getProx();
    while (p != NULL) {
    	cout << "i:" << p->getPilha()->getEstado() << " ";
        p->pilha->mostra();
        p = p->getProx();
    }
    //cout << "\n";
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
	// Enquanto o TOPO for diferente do valor do container é feito o desempilhamento
	while (pTemp->getTopo()->getProx()->getContain()->getValor() != container) {
		Contain *ctemp = new Contain ();
		ctemp = pTemp->desempilha(ctemp);
		// Essa condicao verificar se já chegamos no fim da lista
		// se sim o ponteiro e reiniciado
		if (listaAux == NULL) {
			listaAux = lista->getPrim()->getProx();
		}
		while (listaAux->getPilha()->getEstado() != TEMP) {
			listaAux = listaAux->getProx();
		}
		listaAux->getPilha()->empilha(ctemp);
		listaAux = listaAux->getProx();
	}
}

int contaPilha (No *tempPilha){
	int cont = 0;
	while (tempPilha != NULL){
		cont=cont+1;
		tempPilha = tempPilha->getProx();
	}
	return cont-1;
}

/*
 * Essa Funcao é responsavel por realizar a busca pelo container
 * Apos encontrar o container requesita outras funcoes para ajustara operacao
 */
void buscarContainer (LSE *lista, int container, int dist){

	bool continuar = true;

	NoPilha *listaAux = new NoPilha();
	listaAux = lista->getPrim()->getProx();

	while (continuar && listaAux != NULL) {
		No *pilhaTemp = new No();
		pilhaTemp = listaAux->getPilha()->getTopo()->getProx();

		while (continuar && pilhaTemp != NULL) {
			// Faz a busca pelo container
			if (pilhaTemp->getContain()->getValor() == container){
				// Verifica se o container encontrado esta numa pilha TEMP (0) (Temporaria)
				if (listaAux->getPilha()->getEstado() == TEMP) {
					// Se estiver alteramos o estado da pilha par ORIGEM (2)
					listaAux->getPilha()->setEstado(ORIGEM);
					// funcao ajusta a pilha ate que o topo seja igual ao container
					ajustaOrigem(lista,listaAux->getPilha(), container);
				}
				else {
					ajustaOrigem(lista,listaAux->getPilha(), container);
					Contain *ctemp = new Contain ();
					listaAux->getPilha()->mostra();
					ctemp = listaAux->getPilha()->desempilha(ctemp);
					if (listaAux == NULL) {
						listaAux = lista->getPrim()->getProx();
					}
					while (listaAux->getPilha()->getEstado() != TEMP) {
						listaAux = listaAux->getProx();
					}
					listaAux->getPilha()->empilha(ctemp);
					listaAux->getPilha()->setEstado(ORIGEM);
					listaAux = listaAux->getProx();

					int cont = contaPilha(pilhaTemp);
					cout << cont << "\n";

					if (cont>dist){
						while (cont != 0) {
							Contain *ctemp = new Contain ();
							ctemp = listaAux->getPilha()->desempilha(ctemp);
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

				}
				continuar = false;
			}
			else {
				pilhaTemp = pilhaTemp->getProx();
			}
		}
		listaAux = listaAux->getProx();
	}
}

int main(int argc, const char * argv[]) {

	LSE *e1 = new LSE();

	Pilha *p1 = new Pilha();
	Pilha *p2 = new Pilha();
	Pilha *p3 = new Pilha();
	Pilha *p4 = new Pilha();

	/*bool continuar = true;

	int entrada;

	while (continuar){
		while (continuar) {

		}
	}*/


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

