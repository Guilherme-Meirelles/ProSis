/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <math.h> 
#include <stdint.h>
#include <stdio.h> 
#define sqrt2 1.4142135623730950488016887
#define invsqrt2  1/sqrt2
#define B 127


 
typedef union floatIEEE{ 
    /* 
    Cria uma estrutura para manipular um número flutuante a partir do padrão float IEEE (float 32bits).
    
    */
    float x; // valor decimal float 
    struct { 
        //a ordem de definição dos seguintes campos é importante 
        unsigned int f : 23; // 23 bits para a fração da mantissa (0.xxx...) 
        unsigned int E : 8; // 8 bits para a o expoente enviezado por 127 
        unsigned char s : 1;  //   1 bit para o sinal da mantissa 
    } bits; 
} floatIEEE; //estrutura para precisão simples 


float Newton_Rapson(float a){
    /* O método de Newton_Rapson é um método matemático que permite calcular(aproximadamente
    a raiz quadrada de um número qualquer, utilizando a equação de recorrencia Xk+1 = 1/2 (Xk + A/Xk)
    Para evitar muitas multiplições utiliza-se uma aproximação matemática da raiz quadrada para utilizar
    como valor inicial na equação de Newton-Rapson √𝐴 = 1/2(1 + 𝑓) × √2𝑒
    */
    floatIEEE x1;               
    floatIEEE x0 = {a};
    
    
    // Aproximação da raiz do número inserido para facilitar o metodo de Newton-Rapson
    int e = x0.bits.E - B; 
    x0.bits.f >>= 1; // (f = f/2) 
   
    if (e & 1) {      // e = x0.bits.E 
        x0.bits.E = ((e+1) >> 1) + B; 
        x0.x *= invsqrt2; 
    } 
    else{ 
        x0.bits.E = ((e) >> 1)  +  B; 
    }
    
    
    // Método de Newton-Rapson
    x1.x = x0.x;
    do { 
    x0.x = x1.x; // estimativa atual


    x1.x = (x0.x + a/x0.x); // próxima estimativa


    x1.bits.E--; // x1.bits.E = x1.bits.E – 1;
    } while (x0.x > x1.x);
        

    return x1.x;

}


int main(){ 
    /* Compara as raízes quadradas de 50 até 70 através do método de Newton_Rapson e a função
    de raíz quadrada importada do C: sqrt(float a) 
    */
    float a;
    float b;
    
    printf("\n ------- Raízes Quadradas de 50 até 70 -------");
    for (float c = 50 ; c <= 70; c++){
        a = Newton_Rapson(c);
        b = sqrt(c);
        printf("\n Raiz Quadrada de %f  por Newton-Rapson:( %f ) e pela funcao sqrt:( %f )", c, a, b);

    }
    return 1;
}