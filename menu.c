#include<stdio.h>
#include<conio.h>

/*
  prox: Se refere aos elementos organizados na ordem que foram inseridos,
  isso é util para o inicio do algoritmo.
  vizinhos: É a lista individual dos vizinhos do elemento do grafo iniciado pelos membros da lista grafo
  referencia: Elemento vizinho pertencente ao grafo que é apontado por guia.
*/

typedef struct no{
  guia vizinhos
  def_grafo referencia;
} *guia;

typedef struct lista{
  int valor;
  short int marcado;
  def_grafo prox,
  guia vizinhos;
} *def_grafo;


short int mostrarGrafo(def_grafo grafo){
  short int i = 1;
  if (grafo){
    guia p;
    for(; grafo; grafo = grafo->prox, i++){
      printf("\n\tIndice[%hd]: Elemento: %d: Vizinhos:", i, grafo->valor);
      for(p = grafo->vizinhos; p; p = grafo->vizinhos)
        printf(" -> %d", i, (p->referencia)->valor);
    }
  }
  else
    printf("\n\tNao ha nenhum elemento no grafo.");
  return i;
}

short int definirVizinho(def_grafo *atual, def_grafo grafo){
  short int resposta, ind, erro = 0;
  do{
    if(erro)
      printf("\n\tComando Invalido");
    printf("\n\tQue elementos %d eh vizinho?\n\tIndice[0]: Nenhum");
    ind = mostrarGrafo(grafo);
    scanf(" %hd", &resposta);
    ++erro;
  }while(resposta < 0 && resposta > ind);
  if(resposta){
    short int i;
    def_grafo indice = grafo;
    for(i = 1; i < ind; i++, indice = indice->prox);

    guia p = (*atual)->vizinhos;
    if (!p){
      for(erro = 0; !(p->vizinhos) && !erro; p = p->vizinhos)
        if(p->referencia == indice)
          erro = 1;
      if(!erro){
        p = p->vizinhos = (guia)malloc(sizeof(struct no));
        p->vizinhos = NULL;
        P->referencia = indice;
      }
      else
        printf("\n\tO elemento %d ja esta definido como vizinho de %d", indice->valor, (*atual)->valor);
    }
    else{
      p = (guia)malloc(sizeof(struct no));
      p->vizinho = NULL;
      P->referencia = indice;
    }
  }
  return resposta;

}

short int inserir(def_grafo *grafo){
  int valor;
  short int repetir, erro = 0;

  printf("\n\tElemento que deseja inserir: ");
  scanf(" %d", &valor);

  if(!*grafo){
    *grafo = (def_grafo)malloc(sizeof(struct lista));
    (*grafo)->valor = valor;
    (*grafo)->prox = NULL;
    (*grafo)->vizinhos = NULL;
  }
  else{
    def_grafo p;
    while(definirVizinho());
    for(p = *grafo; !(p->prox); p = p->prox);
    p = p->prox = (def_grafo)malloc(sizeof(struct lista));
    p->valor = valor;
    p->prox = NULL;
    while(definirVizinho(&p, *grafo));
  }
  do{
    if(erro)
      printf("\n\tComando Invalido");
    printf("\n\tDeseja inserir mais um elemento? [0]Sim [1]Nao");
    scanf(" %hd", &repetir);
    ++erro;
  }while(repetir != 0 && repetir != 1);
  return repetir;
}

void removerVizinhos(guia p, def_grafo indice){
  def_grafo original = p->referencia;
  guia t, q;
  for(t = NULL, q = original->vizinhos; q->referencia != indice; q = q->vizinhos) //Procura o elemento que faz referencia ao vizinho que faz referencia ao indice
    t = q;
  if(!t){ //q é o primeiro elemento vizinho;
    if(q->vizinhos)
      original->vizinhos = q->vizinhos;
    else
      original->vizinhos = NULL;
  }
  else{ //q não é o primeiro elemento vizinho
    if(q->vizinhos)
      t->vizinhos = q->vizinhos;
    else
      t->vizinhos = NULL;
  }
  free(q);
}

short int remover(def_grafo *grafo){
  short int resposta, ind, erro = 0;
  do{
    if(erro)
      printf("\n\tComando Invalido");
    printf("\n\tQue elemento deseja remover?\n\tIndice[0]: Nenhum");
    ind = mostrarGrafo(grafo);
    scanf(" %hd", &resposta);
    ++erro;
  }while(resposta < 0 && resposta > ind);
  if(resposta){
    def_grafo indice, q;
    for(q = NULL, i = 1, i < ind; i++, q = indice)
       indice = indice->prox;
    guia t, p; = indice->vizinhos;

    for(p){ //Elemento escolhido tem vizinhos
      removerVizinhos(p, indice);
      t = p;
      p = p->vizinhos;
      free(t);
    }

    if(q){ //Não é o primeiro elemento de grafo
      if(indice->prox)
        q->prox = indice->prox;
      else
        q->prox = NULL;
    }
    else{ //É o primeiro elemento de grafo
      if(indice->prox)
        (*grafo)->prox = indice->prox;
      else
        (*grafo)->prox = NULL;
    }
    free(indice);
  }

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
    free(p)
  }
}

void menu(){
  short int resp, erro = 0, vazio = 0, indice;
  int pesquisa;
	def_grafo grafo;
  arvore = NULL;
    do{
    system("cls");
    printf("\n\tMenu:\n\t[1]inserir no Grafo\n\t[2]Remover do Grafo\n\t[3]Busca em Profundidade\n\t[4]Dijkstra\n\t[5]Ordenação Topológica\n\t[6]Limpar Grafo\n\t[7]Sair.\n\t");
    indice = mostrarGrafo(grafo);
    if (erro)
      printf("\n\tComando Invalido!\n\t");
    erro = 0;
    scanf(" %hd", &resp);
    if(!grafo && resp > 1 && resp < 7){
      resp = 8;
      printf("\n\tAntes de usar estes comandos, insira algum elemento na arvore.");
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
          profundidade(grafo, indice);
          break;
        case 4:
          Dijkstra(grafo, indice);
          break;
        case 5:
          ordenacaoTopologica(grafo, indice);
          break;
        case 6:
          printf("\n\tO grafo foi zerado");
          limparGrafo(&grafo);
          break;
        default:
          ++erro;
        }
    getch();
  }while(resp != 7);
}

int main(){
    menu();
}
