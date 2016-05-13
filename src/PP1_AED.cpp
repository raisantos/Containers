//============================================================================
// Name        : PP1_AED.cpp
// Author      : Jailson Perera & Rai Soledade & Richardson Souza
// Version     :
// Copyright   : Your copyright notice
// Description : Projeto PP1 de AED in C++, Ansi-style
//============================================================================

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
    prim = new NoLista(); // cabeça
    prim->setProx(NULL);
    ult = prim;
}
void ListaDeEntrada::insere(Lista *l){
	ult->setProx(new NoLista());
	ult = ult->getProx();
	ult->setProx(NULL);
	ult->setLista(l);
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

		while (listaAux->getPilha()->getEstado() != TEMP) {
			if (listaAux == NULL) {										// Essa condicao verificar se já chegamos no fim da lista
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
		if (listaAux == NULL) {
			listaAux = lista->getPrim()->getProx();
		}
		cont--;
	}
}

/**
	Retorna o valor da variavel cont decrementado de
	Serve de referencia para verificar em que posicao o conteiner deve entrar
 */

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

					listaAux = lista->getPrim()->getProx();					// Volta para o começo da Lista

					while (listaAux->getPilha()->getEstado() != DESTINO) {	// Procurar pilha e destino
						if (listaAux == NULL) {
							listaAux = lista->getPrim()->getProx();
						}
						listaAux = listaAux->getProx();
					}

					int cont = contaDestino(listaAux->getPilha());			// Guarda a quantidade de containers
					int temp = (cont-dist)+1;
					if (cont > dist) {
						ajustaPosicao(lista,listaAux->getPilha(),temp);		// Ajusta a posicao
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
					int cont = conferePosicao(listaAux->getPilha(), container);	// Incrementa a variavel cont

					if (cont == dist) {
						continuar = false;
					}
					else if (cont>dist) {
						ajustaOrigem(lista,listaAux->getPilha(), container);// Ajusta a pilha para que o container requerido esteja no topo
						ajustaDestino(lista,listaAux->getPilha());			// Pega o container requerido e move para uma pilha
						ajustaPosicao(lista,listaAux->getPilha(),cont);		// Ajusta a pilha de Destino tendo como referencia a variavel cont
						empilhaDesempilha(lista);
						continuar = false;
					}
				}
			}
			else {
				pilhaTemp = pilhaTemp->getProx();							// Passa para o proximo container
			}
		}
		listaAux = listaAux->getProx();										// passa para a proxima pilha
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

//Funcao principal
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
