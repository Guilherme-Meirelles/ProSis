#include <stdio.h>


void desenhaMenu(){
    printf("\n ****** Menu Principal ******");
    printf("\n*    1. Cadastro       *");
    printf("\n*    2. Atualização    *");
    printf("\n*    3. Exclusão       *");
    printf("\n*    4. Consulta       *");
    printf("\n     5. Sair           *");
    printf("\n**************************");
    printf("\nSelecione uma opção [1--5]:");
}
int contoleMenu(){
    int opção;
    scanf("\n %d", &opção);
    if ((opção >= 1) && (opção <= 5)){
        return 1;
    }
    else {
        return 0;
    }
}

void main(){
    int x;
    desenhaMenu();
    x = controleMenu();

}


