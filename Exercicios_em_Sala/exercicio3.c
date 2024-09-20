#include <stdio.h>
void main() {

    float* p;
    float a;
    float b;
    a = 2;
    b = 2;
    p = &a;

    printf("Endereço de a: %p \n", p);
    p = &b;
    printf("Endereço de b: %p \n\n", p);

    printf("Valor a: %f \n", a);
    printf("Valor b: %f \n", b);

    printf("Valor de *p: %p \n\n", p);
    printf("Tamanho float: %d \n", sizeof(a));

    a = 5*b;
    printf("Valor a: %f \n", a);
    printf("Valor b: %f \n", b);

    printf("Valor de *p: %p \n\n", p);



}