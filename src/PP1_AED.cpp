#include <iostream>
using namespace std;

#define ORIGEM 2
#define DESTINO 1
#define TEMP 0
#define UNIDADE 1
#define DEZENA 10

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
	No *aux = topo;
	topo = topo->getProx();
	item = topo->getContain();
	delete aux;
	return item;
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

class Lista{
private:
	No *prim, *ult;
public:
	No* getPrim(){
		return prim;
	}

	No* getUlt(){
		return ult;
	}
	Lista();
	void insere(Contain*);
};

Lista::Lista() {
    prim = new No(); // cabeça
    prim -> prox = NULL;
    ult = prim;
}
void Lista::insere(Contain* x){
	ult->prox = new No();
	ult = ult->prox;
	ult->prox = NULL;
	ult->item = x;
}

class NoLista{
private:
	Lista *lista;
	NoLista *prox;
public:
	NoLista(){};

	Lista *getLista(){
		return lista;
	}

	void setLista(Lista *lista){
		this->lista = lista;
	}

	NoLista* getProx(){
		return prox;
	}

	void setProx(NoLista* prox){
		this->prox = prox;
	}
};

class ListaDeEntrada{
private:
	NoLista *prim, *ult;
public:
	NoLista* getPrim(){
		return prim;
	}
	NoLista* getUlt(){
		return ult;
	}

	ListaDeEntrada();
	void insere(Lista*);
};

ListaDeEntrada::ListaDeEntrada() {
    prim = new NoLista();
    prim->setProx(NULL);
    ult = prim;
}
void ListaDeEntrada::insere(Lista *l){
	ult->setProx(new NoLista());
	ult = ult->getProx();
	ult->setProx(NULL);
	ult->setLista(l);
}

void ajustaOrigem (LSE *lista, Pilha *pTemp, int container) {

	NoPilha *listaAux = new NoPilha();
	listaAux = lista->getPrim()->getProx();

	while (pTemp->getTopo()->getProx()->getContain()->getValor() != container) {
		Contain *ctemp = new Contain ();
		ctemp = pTemp->desempilha(ctemp);

		while (listaAux->getPilha()->getEstado() != TEMP) {
			if (listaAux == NULL) {
				listaAux = lista->getPrim()->getProx();
			}
			listaAux = listaAux->getProx();
		}
		listaAux->getPilha()->empilha(ctemp);
		if (listaAux == NULL) {
			listaAux = lista->getPrim()->getProx();
		}
	}
}

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
		if (listaAux == NULL) {
			listaAux = lista->getPrim()->getProx();
		}
		cont--;
	}
}

int conferePosicao (Pilha *pTemp, int container){
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
		cont++;
		pilhaTemp = pilhaTemp->getProx();
	}
	return cont;
}

void empilhaDesempilha (LSE *lista) {
	NoPilha *listaAux = new NoPilha();
	listaAux = lista->getPrim()->getProx();

	while (listaAux->getPilha()->getEstado() != ORIGEM) {
		if (listaAux == NULL) {
			listaAux = lista->getPrim()->getProx();
		}
		listaAux = listaAux->getProx();
	}
	Contain *ctemp = new Contain();
	ctemp = listaAux->getPilha()->desempilha(ctemp);

	listaAux->getPilha()->setEstado(TEMP);
	listaAux = lista->getPrim()->getProx();

	while (listaAux->getPilha()->getEstado() != DESTINO) {
		if (listaAux == NULL) {
			listaAux = lista->getPrim()->getProx();
		}
		listaAux = listaAux->getProx();
	}
	listaAux->getPilha()->empilha(ctemp);
}

void buscarContainer (LSE *lista, int container, int dist){
	bool continuar = true;

	NoPilha *listaAux = new NoPilha();
	listaAux = lista->getPrim()->getProx();

	while (continuar && listaAux != NULL) {
		No *pilhaTemp = new No();
		pilhaTemp = listaAux->getPilha()->getTopo()->getProx();

		while (continuar && pilhaTemp != NULL) {
			if (pilhaTemp->getContain()->getValor() == container){
				if (listaAux->getPilha()->getEstado() == TEMP) {
					listaAux->getPilha()->setEstado(ORIGEM);
					ajustaOrigem(lista,listaAux->getPilha(), container);

					listaAux = lista->getPrim()->getProx();

					while (listaAux->getPilha()->getEstado() != DESTINO) {
						if (listaAux == NULL) {
							listaAux = lista->getPrim()->getProx();
						}
						listaAux = listaAux->getProx();
					}

					int cont = contaDestino(listaAux->getPilha());
					int temp = (cont-dist)+1;

					if (cont > dist) {
						ajustaPosicao(lista,listaAux->getPilha(),temp);
						empilhaDesempilha(lista);
					}
					else if (cont == dist) {
						ajustaPosicao(lista,listaAux->getPilha(),cont);
						empilhaDesempilha(lista);
					}
					else {
						empilhaDesempilha(lista);
					}
					continuar = false;
				}
				else {
					int cont = conferePosicao(listaAux->getPilha(), container);

					if (cont == dist) {
						continuar = false;
					}
					else if (cont>dist) {
						ajustaOrigem(lista,listaAux->getPilha(), container);
						ajustaDestino(lista,listaAux->getPilha());
						ajustaPosicao(lista,listaAux->getPilha(),cont);
						empilhaDesempilha(lista);
						continuar = false;
					}
				}
			}
			else {
				pilhaTemp = pilhaTemp->getProx();
			}
		}
		listaAux = listaAux->getProx();
	}
}

int maiorPilha(LSE *lista){
	int maior = 0, temp;

	NoPilha *listaAux = new NoPilha();
	listaAux = lista->getPrim()->getProx();

	while (listaAux != NULL) {
		Pilha *pilhaTemp = new Pilha();
		pilhaTemp = listaAux->getPilha();
		temp = contaDestino(pilhaTemp);
		if (temp>maior) {
			maior = temp;
		}
		listaAux = listaAux->getProx();
	}
	return maior;
}

void imprime (LSE *lista) {
	bool continuar = true;

	int tam = maiorPilha(lista);
	int temp;
	int tipo;

	if (lista->getPrim()->getProx()->getPilha()->getTopo()->getProx()->getContain()->getValor() < DEZENA) {
			tipo = UNIDADE;
	}
	else {
		tipo = DEZENA;
	}

	NoPilha *listaAux = new NoPilha();
	while (continuar) {
		listaAux = lista->getPrim()->getProx();
		while (listaAux != NULL) {
			Pilha *pilhaTemp = new Pilha();
			pilhaTemp = listaAux->getPilha();

			temp = contaDestino(pilhaTemp);
			if (temp == tam) {
				Contain *c = new Contain ();
				cout << pilhaTemp->getTopo()->getProx()->getContain()->getValor() << " ";
				pilhaTemp->desempilha(c);
			}
			else {
				if (tipo == UNIDADE){
					cout << "  ";
				}
				else {
					cout << "   ";
				}
			}
			listaAux = listaAux->getProx();
		}
		cout << "\n";
		tam = maiorPilha(lista);
		if (tam == 0) {
			continuar = false;
		}
	}
}

int main(int argc, const char * argv[]) {

LSE *e1 = new LSE();
ListaDeEntrada *e2 = new ListaDeEntrada();

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

	cin >> entrada;
	while (entrada != -1){
		Lista *l = new Lista();
		while (entrada != -1) {
			Contain *d = new Contain();
			d->setValor(entrada);
			l->insere(d);
			cin >> entrada;
		}
		e2->insere(l);
		cin >> entrada;
	}

	NoPilha *listaAux = e1->getPrim()->getProx();
	NoLista *listaBusca = e2->getPrim()->getProx();
	int dist = 0;
	while (listaBusca != NULL){
		No *itemLista = listaBusca->getLista()->getPrim()->getProx();
		listaAux->getPilha()->setEstado(DESTINO);
		while (itemLista != NULL) {
			Chave container = itemLista->getContain()->getValor();
			dist++;
			buscarContainer(e1,container,dist);
			itemLista = itemLista->getProx();
		}
		listaAux->getPilha()->setEstado(TEMP);
		listaAux = listaAux->getProx();
		dist = 0;
		listaBusca = listaBusca->getProx();
	}

	imprime(e1);

	return 0;
}
