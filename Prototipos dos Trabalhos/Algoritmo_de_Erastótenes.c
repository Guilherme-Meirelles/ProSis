#include <stdio.h>
#include <math.h>
int GetBitn(int num, int n){  
    // recupera o valor (1 ou 0) do n-ésimo bit de num. 
    //         0 =< n <= 31        
    return ((num & (1 << n)) >> n); 
} 
int ResetBitn(int num, int n){  
    // seta o n-ésimo bit de num com o valor “0” 
    //         0 =< n <= 31 
    // shiftar 1 para esquerda n vezes e negar todos os bits desse resultado  
    // e realizar um bitwise & com o próprio num  
    // num &= ~(1 << n); return num; 
    return (num & (~(1 << n)));
}
//unsigned int[]

void main(){
    /* 
    O objetivo desta função é descobrir se um número inteiro é primo ou não, utilizando-se o crivo de Erastótenes.

    No algoritmo/crivo de Erastótenes se constroi uma tabela de números inteiro e demarca todos os números que não são primos,
    os quais são os múltiplos dos números primos que estão até a raiz quadrada inteira do último número da tabela.

    Para implementar o crivo, a função utilizará os bits de números inteiro (32 bits cada número) armazenados em um vetor,
    para realizar as demarcações dos números não primos, o bit correspondente a um número não primo será alterado para 0.

    Como sabe-se que os números pares não são primos, então o algoritmo já recebe os bits relacionados aos números pares iguais 0 e os bits 
    relacionados aos números ímpares iguais a 1.

    Nesta função utiliza-se as funçôes auxialiares GetBitn e ResetBitn. 
    */
    int n; // Inteiro escolhido pelo usuário
    int primeiro = 0xAAAAAAAC; // Como 0 e 1 não primos e 2 é o único par primo, então primeiro elemento do vetor é assim
    int ultimo = 6400; // O crivo irá até o número 6400
    double fim = sqrt(ultimo); // Raiz quadrada do último
    int p=3; // Primeriro primo conhecido
    int k; 
    int i;
    int kk;
    int verificador;
    int elementos = 0xAAAAAAAA; // elementos do vetor, com exeção do primeiro
    unsigned  int primos[200]; // Vetor
    int j =0;

    // Inseção do elementos no vetor
    primos[0] = primeiro;
    for (int i = 1; i < 200; i++)
        primos[i] =  elementos;


    // Demarcação dos números não primos nos bits
    do  {
        k = p * 2;
        while (k < ultimo){
            i = k / 32;
            kk = k % 32;
            primos[i] = ResetBitn(primos[i],kk);
            k += p;
        }
        ++ p;
    }while ( p  < fim);

    printf("\n Digite um numero para verificar se o numero e primo ou nao: ");
    scanf(" %d", &n);
  
    i = n/32;
    kk = n % 32;

    // Encontra o bit relacionado ao número no vetor é analisa se é primo ou não.
    if (GetBitn(primos[i], kk)) { 
        printf("\n O numero %d e primo", n); 
        } 
    else { 
        printf("\n O numero %d nao e primo", n); 
        }
    
    printf("\n\n Digite 1 se voce quer ver a tabela/crivo de numeros primos: ");
    scanf(" %d", &verificador);

    if (verificador == 1){
        int contador = 0;
        int j = 0;
        int i = 0;
        while (i < 200) {
            j = 0;
            while (j < 32){
            if (GetBitn(primos[i], j)){
                printf(" %d  ", contador);
                }
                contador ++;
                j ++;

            }
        printf("\n");
        i ++;
        }
        }
}


