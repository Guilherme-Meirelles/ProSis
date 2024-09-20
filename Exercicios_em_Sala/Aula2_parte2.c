#include <stdio.h>
#include <locale.h>

void multiplicadoDoisV2(int *valor); //Assinatura


void multiplicadoDoisV2(int *valor){
    *valor = *valor * 2;
    printf("\n Valor dentro da função: %d", *valor);
    printf("\nEndereço de memoria na funcao: %X", valor);
}


void main(){
    int valor;
    printf("\nInforme um valor: ");
    scanf("\n%d",&valor);
    printf("\n Valor antes da função: %d", valor);
    multiplicadoDoisV2(&valor);
    printf("\n Valor da função no main: %d", valor);
    printf("\nEndereço do main: %X ", &valor);
}
