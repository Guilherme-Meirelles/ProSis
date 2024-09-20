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

int controleMenu(){
    int x;
    scanf("\n %d", &x);
    if ( (x >= 1) && (x <= 5)){
        return 1;
    }
    else {
        return 0;
    }
}

void mensagemErro(int codigoErro, char str){
    char strErro[];
    str= strErro[];
    switch (codigoErro) {
        case 0:
        strErro = "Opção invalida! Verifique!";
        break;
    
    default:
        break;
    }
}


void main(){
    int x;
    char str[240], *mensagem;
    mensagem = str;
    desenhaMenu();
    x = controleMenu();
    mensagemErro(x);

}