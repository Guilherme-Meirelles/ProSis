#include <stdio.h>
#include <stdlib.h>
//#include <locale.h>

typedef struct TpDADO{
    int C;
    int D;
} TpDADO;  /// defina a estrutura de TpDado
//typedef struct TpNODE TpNODE;
//typedef struct TpPILHA TpPILHA;

typedef struct TpNODE {  /// estrutura da "caixa" do nodo
            TpDADO dado;
            struct TpNODE *prox; /// permite encadear caixas (*p para Link)
    } TpNODE;

typedef struct TpPILHA {   /// cabecalho (ou descritor) da estrutura de dados
            TpNODE *topo;
          //  int len;    /// campos complementares do descritor
          //  TpNODE *fim; ///
    } TpPILHA;


void displayLL(TpPILHA *p) {
printf("\n Display:\n");
    if(p->topo) // se o ponteiro nao eh NULL
    {
        TpNODE *paux;
        paux = p->topo;
        printf("Os elementos armazenados na Pilha sao:\n");
        do
        {
            printf(" %d, %d  ", paux->dado.C, paux->dado.D);
            paux = paux->prox;

        } while(paux);
        printf("\n ......... Fim da PILHA .........\n");
    }
    else {
        printf("\n ......... PILHA Vazia. \n\n");
    }
    return;
}


void InicializaPilha(TpPILHA *p){
printf("\n Inicializa:\n");
//    p = (TpPILHA*) malloc(sizeof(TpPILHA));
//    if (!p) {
//        printf("\n ERRO de alocacao da PILHA:\n");
//        exit(0);
//    }
    p->topo = NULL;
   ///  p->len = 0;   /// outros campos do descritor
   ///  p->fim = NULL;

}


int push(TpDADO x, TpPILHA *p) { /// empilhar x
printf("\n PUSH:\n");

    TpNODE *paux;
    /// alocar memoria
    paux = (TpNODE*) malloc(sizeof(TpNODE*));
    /// se houve erro na alocacao, entao paux eh NULL (??)
    /// em C, NULL eh o mesmo que ZERO
    if(!paux) {
        printf("\n ERRO na alocacao de um novo NODO na pilha.");
        return -1;
    }

    /// inserir x = 20 na memoria alocada
    paux->dado.C = x.C;
    paux->dado.D = x.D;
    paux->prox = p->topo;
    p->topo = paux;
printf("\n empilhou ---> %d %d\n", paux->dado.C, paux->dado.D);

    return 1;/// sucesso
}

int pop(TpDADO *x, TpPILHA *p) { /// desempilhar x

printf("\n POP:\n");
    if(!p->topo) {
            printf("\n ERRO no desempilhamento. Pilha vazia.");
            return -2;// nao se pode desempilhar em pilha vazia
    }
    /// tem dados empilhados
    TpNODE *paux;
    paux = p->topo;


    /// copiar o valor do dado armazenado no topo da pilha
    *x = paux->dado;
    
    p->topo = paux->prox;
    paux->prox = NULL; /// desligar do encadeamento a caixa do topo.

printf("\n Desempilhou ---> %d  %d\n", paux->dado.C, paux->dado.D);

    free(paux);

    return 2;

}


int main(void)
{
    TpPILHA *pilha;
    TpDADO  x;
    

    /// criar a base da pilha
    pilha = (TpPILHA*) malloc(sizeof(TpPILHA));
    if (!pilha) {
        printf("\n ERRO de alocacao da PILHA:\n");
        exit(0);
    }

    InicializaPilha(pilha);
    printf("\n Dixplay:\n");

    displayLL(pilha);  /// mostra pilha vazia



  //  displayLL(pilha); /// mostra pilha vazia.

    /// inserir 20 na pilha.
    x.C = 20;
    x.D = -20;
    
    push(x, pilha); /// empilhar x = 20
    push(x, pilha); /// empilhar x = 30
    push(x, pilha); /// empilhar x = 40
    displayLL(pilha); /// mostra pilha


    pop(&x, pilha);
printf("\n Desempilhou ---> %d %d\n", x.C,x.D);
    pop(&x, pilha);
printf("\n Desempilhou ---> %d %d\n", x.C,x.D);
    pop(&x, pilha);
printf("\n Desempilhou ---> %d %d\n", x.C,x.D);

    pop(&x, pilha); /// erro!!!!
printf("\n Desempilhou ---> %d %d\n", x.C, x.D);

    if (pop(&x, pilha)==-2) /// erro!!!!
          printf("\n ERRO!!! Impossivel desempilhar de PILHA vazia \n");


  return 0;
}
