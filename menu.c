#include<stdio.h>
#include<conio.h>
#define infinito 99999999;

/*
  prox: Se refere aos elementos organizados na ordem que foram inseridos,
  isso Ã© util para o inicio do algoritmo.
  vizinhos: Ã‰ a lista individual dos vizinhos do elemento do grafo iniciado pelos membros da lista grafo
  referencia: Elemento vizinho pertencente ao grafo que Ã© apontado por guia.
*/

typedef struct no{
  int peso;
  struct no *vizinhos;
  struct lista *referencia;
} *guia;

typedef struct lista{
  int valor;
  short int marcado;
  struct lista *prox;
  guia vizinhos;
} *def_grafo;

typedef struct listaDistancia{
	int deOndeVeio;
	int id;
	int peso;
	listaDistancia* prox;
}*dist;


//==============================================Parte Paulo=======================

int dijkstra(def_grafo grafo, int origem, int destino){
	int qtd;
	def_grafo q;
	dist inicioDist = (dist)malloc(sizeof(listaDistancia));
	dist l;
	dist anterior;

	//Criando lista de distancias minimas

	anterior = NULL;
	inicioDist->id = q->valor;
	inicioDist->peso = infinito;
	inicioDist->deOndeVeio = -1;
	inicioDist->prox = anterior;
	anterior=inicioDist;

	for(q=grafo->prox; q!=NULL; q=q->prox){
		l =(dist) malloc(sizeof(listaDistancia));
		l->id = q->valor;
		l->peso = infinito;
		l->deOndeVeio = -1;
		anterior->prox = l;
		anterior=l;
	}

	//chamando funï¿½ï¿½o recursiva
	setDist();
}

void setDist(def_grafo grafo, int origem, int destino, listaDistancia inicioLista){
	guia p;
	listaDistancia d, o;
	int valor; //valor do peso do grafo vizinho
	p= grafo->vizinhos;
	
	//para cada vizinho fazer
	while(p){
		valor = p->referencia->valor;
		
		for(d=inicioLista; d!=NULL && d->id!=valor; d = d->prox){
			//encontrando no do vizinho na listaDistancia
		}
		for(o=inicioLista; o!=NULL && o->id!=grafo->valor; d = d->prox){
			//encontrando no da origem na listaDistancia
		}
		
		//Caso ele não encontre, não existe
		if(d==NULL || o==NULL){
			printf("\n setDist() Falhou!");
			return;
		}
		
		
		//se for menor o caminho, substitui na listaDistancia
		if(p->peso + o->peso < d->peso){
			d->peso = p->peso + o->peso;
			d->deOndeVeio = o->id;
		}
		//caminha para o proximo vizinho
		p= p->vizinhos;
		
	}
	//marca nó como visitado
	grafo->marcado = 1;
	
	//para cada vizinho faça
	while(p){
		//se não estiver marcado, faz o processo todo para esse vertice
		if(!p->referencia->marcado){
			setDist(p->referencia, origem, destino, inicioLista);
		}
	}
	
	//Retornando o menor caminho
	for(d=inicioLista; d!=NULL && d->id!=destino; d = d->prox){
			//encontrando no do vizinho na listaDistancia
	}
	
	return d->peso;
	
	
}

//================================================Fim parte Paulo=================

short int mostrarGrafo(def_grafo grafo){
  short int i = 1;
  def_grafo q;
  if (grafo){
    guia p;
    for(; grafo; grafo = grafo->prox, i++){
      printf("\n\tIndice[%hd]: Elemento: %d: Vizinhos:", i, grafo->valor);
      for(p = grafo->vizinhos; p; p = p->vizinhos){
      	q = p->referencia;
      	printf(" -> %d (peso: %d)", q->valor, p->peso);
	  }
    }
  }
  else
    printf("\n\tNao ha nenhum elemento no grafo.");
  return i-1;
}

short int definirVizinho(def_grafo *atual, def_grafo grafo){
  short int resposta, ind, erro = 0, repetido = 0;
  int peso;
  do{ //Perguntar qual o elemteo
    if(erro)
      printf("\n\tComando Invalido");
    if(repetido)
    	printf("\n\tO elemento nao pode ser vizinho dele mesmo");
    repetido = 0;
    printf("\n\tQue elementos %d eh vizinho?\n\tIndice[0]: Nenhum", (*atual)->valor);
    ind = mostrarGrafo(grafo);
    printf("\n\t");
    scanf(" %hd", &resposta);
    ++erro;
    if(resposta == ind)
    	repetido = 1;
  }while((resposta < 0 || resposta > ind) || repetido);

  if(resposta){
    short int i;
    def_grafo indice = grafo;
    for(i = 1, erro = 0; i < resposta; i++, indice = indice->prox);

    do{ //Perguntar qual o peso
      if(erro)
        printf("\n\tPeso Invalido");
      printf("\n\tQual o peso da aresta entre %d e %d? (Este deve ser positivo e nao nulo)", (*atual)->valor, indice->valor);
      printf("\n\t");
      scanf(" %d", &peso);
      ++erro;
    }while(peso <= 0);


    guia p = (*atual)->vizinhos;
    if(p){ //Se o vertice atual ja possui vizinhos
      for(i = 0; (p->vizinhos) && !i; p = p->vizinhos)
        if(p->referencia == indice)
          i = 1;
      if(p->referencia == indice)
         i = 1;

      if(!i){
        p = p->vizinhos = (guia)malloc(sizeof(struct no));
        p->vizinhos = NULL;
        p->referencia = indice;
        p->peso = peso;

        //Inserir vizinho no outro elemento
        if(indice->vizinhos){
        	for(p = indice->vizinhos; (p->vizinhos); p = p->vizinhos);
			    p = p->vizinhos = (guia)malloc(sizeof(struct no));
        	p->vizinhos = NULL;
        	p->referencia = *atual;
          p->peso = peso;
		    }
    		else{
    			p = indice->vizinhos = (guia)malloc(sizeof(struct no));
         	p->vizinhos = NULL;
          p->referencia = *atual;
          p->peso = peso;
    		}
		printf("\n\tVizinho inserido com sucesso");
    }
    else
      printf("\n\tO elemento %d ja esta definido como vizinho de %d", indice->valor, (*atual)->valor);
    }
    else{ //Se o vertice atual ainda nao possui vizinhos
      p = (*atual)->vizinhos = (guia)malloc(sizeof(struct no));
      p->vizinhos = NULL;
      p->referencia = indice;
      p->peso = peso;
      printf("\n\tVizinho inserido com sucesso");

      //Inserir vizinho no outro elemento
      if(indice->vizinhos){
      	for(p = indice->vizinhos; (p->vizinhos); p = p->vizinhos);
		    p = p->vizinhos = (guia)malloc(sizeof(struct no));
       	p->vizinhos = NULL;
       	p->referencia = *atual;
        p->peso = peso;
		  }
		  else{
  			p = indice->vizinhos = (guia)malloc(sizeof(struct no));
       	p->vizinhos = NULL;
        p->referencia = *atual;
        p->peso = peso;
		  }
    }
  }
  return resposta;

}

short int inserir(def_grafo *grafo){
  int valor;
  short int repetir, erro = 0, invalido = 0;

  printf("\n\tElemento que deseja inserir:\n\tResposta: ");
  scanf(" %d", &valor);

  if(!*grafo){
    *grafo = (def_grafo)malloc(sizeof(struct lista));
    (*grafo)->valor = valor;
    (*grafo)->prox = NULL;
    (*grafo)->vizinhos = NULL;
  }
  else{
    def_grafo p;
    for(p = *grafo; p->prox; p = p->prox)
      if (p->valor == valor)
        invalido = 1;
    if(!invalido){
      p = p->prox = (def_grafo)malloc(sizeof(struct lista));
      p->valor = valor;
      p->prox = NULL;
      p->vizinhos = NULL;
      while(definirVizinho(&p, *grafo));
    }
  }
  if(!invalido){
    do{
      if(erro)
      printf("\n\tComando Invalido");
      printf("\n\tDeseja inserir mais um elemento? [0]Nao [1]Sim\n\t");
      scanf(" %hd", &repetir);
      ++erro;
    }while(repetir != 0 && repetir != 1);
    if(repetir)
      system("cls");
  }
  else{
    printf("Um elemento com este mesmo valor ja¡ foi inserido!");
    repetir = 1;
  }
  return repetir;
}

void removerVizinhos(guia p, def_grafo indice){
  def_grafo original = p->referencia;
  guia t, q;
  for(t = NULL, q = original->vizinhos; q->referencia != indice; q = q->vizinhos) //Procura o elemento que faz referencia ao vizinho que faz referencia ao indice
    t = q;  if(!t){ //q Ã© o primeiro elemento vizinho;
    if(q->vizinhos)
      original->vizinhos = q->vizinhos;
    else
      original->vizinhos = NULL;
  }
  else{ //q nÃ£o Ã© o primeiro elemento vizinho
    if(q->vizinhos)
      t->vizinhos = q->vizinhos;
    else
      t->vizinhos = NULL;
  }
  free(q);
}

short int remover(def_grafo *grafo){
  short int resposta, ind, erro = 0, i;
  do{
    if(erro)
      printf("\n\tComando Invalido");
    printf("\n\tQue elemento deseja remover?\n\tIndice[0]: Nenhum");
    ind = mostrarGrafo(*grafo);
    printf("\n\t");
    scanf(" %hd", &resposta);
    ++erro;
  }while(resposta < 0 || resposta > ind);
  if(resposta){
    def_grafo indice, q;
    for(q = NULL, indice = *grafo, i = 1; i < resposta; i++, indice = indice->prox)
      q = indice;
    guia t, p = indice->vizinhos;

    while(p){ //Elemento escolhido tem vizinhos
      removerVizinhos(p, indice);
      t = p;
      p = p->vizinhos;
      free(t);
    }

    if(q){ //NÃ£o Ã© o primeiro elemento de grafo
      if(indice->prox)
        q->prox = indice->prox;
      else
        q->prox = NULL;
    }
    else{ //Ã‰ o primeiro elemento de grafo
      if((*grafo)->prox)
        *grafo = (*grafo)->prox;
      else
        *grafo = NULL;
    }
    free(indice);
  }
  erro = 0;
  do{
    if(erro)
      printf("\n\tComando Invalido");
    printf("\n\tDeseja remover mais um elemento? [0]Nao [1]Sim\n\t");
    scanf(" %hd", &resposta);
    ++erro;
  }while(resposta != 0 && resposta != 1);
  if(resposta)
    system("cls");
  return resposta;
}

void limparGrafo(def_grafo *grafo){
  def_grafo p = NULL;
  guia q, t;

  while((*grafo)){
    for(q = (*grafo)->vizinhos; q; free(t)){
      t = q;
      q = q->vizinhos;
    }
    p = (*grafo);
    if((*grafo)->prox)
      (*grafo) = (*grafo)->prox;
    else
      (*grafo) = NULL;
    free(p);
  }
}

void menu(){
  short int resp, erro = 0, vazio = 0, indice;
  int pesquisa;
  def_grafo grafo;
  grafo = NULL;
    do{
    system("cls");
    printf("\n\tMenu:\n\t[1]Inserir no Grafo\n\t[2]Remover do Grafo\n\t[3]Busca em Profundidade\n\t[4]Dijkstra\n\t[5]Ordenacao Topologica\n\t[6]Limpar Grafo\n\t[7]Sair.\n\t");
    indice = mostrarGrafo(grafo);
    if (erro)
      printf("\n\tComando Invalido!\n\t");
    erro = 0;
    printf("\n\tComando: ");
    scanf(" %hd", &resp);
    if(!grafo && resp > 1 && resp < 7){
      resp = 8;
      printf("\n\tAntes de usar este comandos, insira algum elemento na arvore.");
    }
        switch(resp){
        case 1:
          printf("\n\tInserir no Grafo:");
          while (inserir(&grafo));
          break;
        case 2:
          printf("\n\tRemover do Grafo:");
          while (remover(&grafo));
          break;
        case 3:
          //profundidade(grafo, indice);
          break;
        case 4:
          //Dijkstra(grafo, indice);
          break;
        case 5:
          //ordenacaoTopologica(grafo, indice);
          break;
        case 6:
          printf("\n\tO grafo foi zerado");
          limparGrafo(&grafo);
          break;
        default:
          ++erro;
        }
    printf("\n\n\tPressione qualquer tecla");
    getch();
  }while(resp != 7);
}

int main(){
    menu();
}
