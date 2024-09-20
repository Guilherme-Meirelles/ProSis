#include <stdio.h>
void main() 
{

    int*iptr; //ponteiro

    int a = -8; 

    iptr = &a; // ponteiro aponta o endereço de memória de a

    printf("\n Valor de iptr %p ", iptr); // Endereço de memória
    printf("\n Endereço de a = %p (hexadecimal)", &a);
    printf("\n Endereço de a = %d (decimal)", &a);
    printf("\n Valor armazenado em a = %d", a);
    printf("\n Valor apontado por iptr(*iptr) = %d", *iptr);
    printf("\n tamanho do inteiro [sizeo(int)] = %d (bytes)",sizeof(int)); // tamanho em bytes do inteiro
    printf("\n tamanho do ponteiro para inteiro [sizeof(int*)] = %d(bytes)", sizeof(int*)); // tamanho em bytes do ponteiro
    printf("\n tamnho do float [sizeof(float)] = %d (bytes)", sizeof(float)); // tamanho em bytes em float
    printf("\n Tamanho do ponteiro para float[sizeof(float*)] = %d(bytes)", sizeof(float*));  // tamanho em bytes de um ponteiro float
    printf("\n \n");
    a = a/2;
    printf("\n Valor armazenado em a = %d", a);
    printf("\n Valor apontado por iptr (*iptr) = %d", *iptr);
    printf("\n");
    *iptr = -4 * (*iptr);
    printf("\n Valor armazendo em a = %d", a);
    printf("\n Valor apontado por iptr (*iptr) = %d", *iptr);
    printf("\n\n");

    

    
    
    // multiplicar o valor apontado por iptr

}