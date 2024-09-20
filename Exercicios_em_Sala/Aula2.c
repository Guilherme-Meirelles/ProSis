#include <stdio.h>


void multiplicadordois(int valor){
    valor = valor * 2;
    printf("\nValor dentro da funcao: %d", valor);
    printf("\nEndereco de memoria depois: %X", &valor);
}
void main()
{
    int valor;
    int valor2;
    int resultado;
    scanf("\n%d", &valor);
    multiplicadordois(valor);
    printf("\nValor antes da funcao: %d",valor);
    printf("\nEndereco de memoria antes: %X", &valor);
    scanf("\n%d", &valor2);
    resultado = multiplicar_dois(valor2);
    printf("\nResultado é %d", resultado);
    
}
int multiplicar_dois(int valor){
    valor = valor*2;
    printf("\nValor dentro da função: %d", valor);
    printf("\nEndereço dentro da função: %X", &valor);
    return valor;
}
