#include "Containers.h"

Pilha::Pilha() {
    fundo = new No(); // nó cabeça
    topo = fundo;
    this->tam=0;
}

void Pilha::empilha(Item item) {
    No *aux = new No();
    topo -> setItem(item);
    aux -> setProx(topo);
    topo = aux;
}

bool Pilha::vazia() {
    return topo == fundo;
}

void Pilha::mostra() {
    cout << "Pilha: topo-> ";
    for (No *nav = topo->getProx(); nav != NULL;
                                   nav = nav->getProx()) {
        nav->getItem().mostra();
    }
    cout << "<- fundo\n";
}

bool Pilha::pesquisa(int x){
	int flag = 0;
	No *aux = topo;
	while(aux->getProx() != NULL){
		if(aux->getItem().getValor() == x){
			//cout<<"numero achado\n";
			flag = 1;
			aux->setProx(NULL); //= NULL;
			return true;
		}
		else{
			tam--;
			aux = aux->getProx();
		}
	}
	if(flag == 0){
		//cout<<"não tem\n";
		return false;
	}
}	

LSE::LSE() {
    prim = new NoPilha(); // cabeça
    prim -> prox = NULL;
    ult = prim;
    this->tam_lse=0;
}


void LSE::insere(Pilha p) {
    ult->prox = new NoPilha();
//    if (ult == nullptr) exit(1);
    ult = ult-> prox;
    ult -> prox = NULL;
    ult->pilha = p;
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
        p->pilha.mostra();
        p = p->prox;
    }
    cout << "\n";
}

/*NoPilha /void LSE::busca(Chave k){
    NoPilha *p = prim->prox;
   // while(p != NULL && p->pilha.getProx() != NULL){
        if(p->pilha.pesquisa(k) == true) {
 		    cout <<"encontrado\n";
            //tam_lse--;
           // p = p->prox;
        }

        else{
            cout<< "não encontrado\n";
            //tam_lse--;
            //p = p->prox; 	                
	
        }
	tam_lse--;
	p = p->prox;
    }
    
	
}*/
