#include <stdio.h>
void main(){
int minhaIdade = 19;     
int *A = &minhaIdade;  

// Resultado do endereco de memoria de minhaIdade atraves do ponteiro A (0x7ffe5367e044)
printf("%p\n", A);

// Valor da variavel minhaIdade atraves do ponteiro A (19)
printf("%d\n", *A);

// Valor de minhaIdade alterado
minhaIdade = 30;

// Resultado do endereco de memoria de minhaIdade atraves do ponteiro A (0x7ffe5367e044)
printf("%p\n", A);

// Valor da variavel minhaIdade atraves do ponteiro A (30)
printf("%d\n", *A);
}