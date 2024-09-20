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


#define maio_valor 6400 // Maior valor do crivo
#define tamanho_vetor (6400 / 32) 
unsigned int primos[tamanho_vetor]; // Vetor/Tabela onde se construirá o crivo

void formar_tabela(){
    // Insere os elementos no vetor que se utilizará para o crivo
    // Como sabe-se que os números pares não são primos, então constroi-se a tabelea/crivo
    // já recebendo os bits relacionados aos números pares iguais a 0 e os bits relacionados aos números ímpares iguais a 1.
    
    primos[0] = 0xAAAAAAAC;
    for (int i = 1; i < 200; i++)
        primos[i] =  0xAAAAAAAA;
}

void Tabela_Primos(){
    // Demarcam-se com o valor binário 0 os bits relacionados aos números que não são primos.
    
    double fim = sqrt(maio_valor); // Raiz quadrada do maior valor
    int p=3; // Primeriro primo conhecido após 2
    int k; // multiplos de p
    int i; // variavel auxiliar
    int kk; // variavel auxiliar
    int a = 1; // variavel auxiliar

    /*
    do  {
        k = p * 2;
        while (k < maio_valor){
            i = k / 32;
            kk = k % 32;
            primos[i] = ResetBitn(primos[i],kk);
            k += p;
        }
        ++ p;
    }while ( p  < fim);
    */

    while (a) {
        int k = 2 * p;
        while (k <= maio_valor) {
            i = k /32;
            kk = k % 32;
            primos[i] = ResetBitn(primos[i], kk); 
            k += p;
        }

        
        do {
            ++p;
            i = p /32;
            kk = p%32;
        } while (p <= fim && !GetBitn(primos[i], kk));

        if (p > fim) {
            a = 0;
        }
    }
}


void mostrarTabela(){
    // Imprime os valores da tabela/crivo de Erastótenes
    int contador = 0;
    int j = 0;
    int i = 0;
    while (i < 200) {
        while (j < 32){
        if (GetBitn(primos[i], j)){
            printf(" %d  ", contador);
            }
        contador ++;
        j ++;

        }
    j = 0;
    printf("\n");
    i ++;
    }
}


int main(){
    /* 
    O objetivo desta função é descobrir se um número inteiro é primo ou não, utilizando-se o crivo de Erastótenes.

    No algoritmo/crivo de Erastótenes se constroi uma tabela de números inteiro e demarca todos os números que não são primos,
    os quais são os múltiplos dos números primos que estão até a raiz quadrada inteira do último número da tabela.

    Para implementar o crivo, a função utilizará os bits de números inteiro (32 bits cada número) armazenados em um vetor,
    para realizar as demarcações dos números não primos, o bit correspondente a um número não primo será alterado para 0.

    n. 
    */
    int n; // Inteiro escolhido pelo usuário
    
    
    int verificador; // O crivo irá até o número 6400
    
     
    int i; // Variavel auxiliar
    int kk; // Variavel auxiliar
    

    // Inseção do elementos no vetor
    formar_tabela();

    Tabela_Primos();

    
    printf("\n Digite um numero de 0 ate 6400 para verificar se o numero e primo ou nao: ");
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
    
    printf("\n\n Digite (1) se voce quer ver a tabela/crivo de numeros primos de 0 ate 6400: ");
    scanf(" %d", &verificador);



    if (verificador == 1){
        mostrarTabela();
}
return 1;
}
