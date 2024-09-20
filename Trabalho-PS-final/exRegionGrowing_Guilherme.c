#include <stdio.h>
#include <string.h>  // para usar a fun��o strcmp() que compara duas strings
#include <stdlib.h>  // para usar a fun��o exit() que interrompe (aborta) a execu��o do programa.

typedef struct TpDADO {
            int L, C;
        } TpDADO;

typedef struct TpNODE {  /// estrutura da "caixa" do nodo
            TpDADO dado;
            struct TpNODE *prox; /// permite encadear caixas (*p para Link)
        } TpNODE;

typedef struct TpPILHA {   /// cabecalho (ou descritor) da estrutura de dados
            TpNODE *topo;
          //  int len;    /// campos complementares do descritor
          ///  TpNODE *fim; ///
        } TpPILHA;

typedef unsigned char Tpixel; // tipo Tpixel para valores em [0, 255]

    typedef struct pgm {
      int w;     // largura da imagem em pixels (TC - Total de pixels em cada coluna da imagem)
      int h;     // altura da imagem em pixel   (TL - Total de pixels em cada linha da imagem )
      int max;   // valor de brilho m�ximo registrado na imagem (use 255 sempre)
      Tpixel* pData; // ponteiro para o reticulado (matriz) da immagem alocada como um vetor.
    } pgm;

void InicializaPilha(TpPILHA *p){
printf("\n ..... Pilha Inicializada.");
    p->topo = NULL;  /// topo da pilha est� vazio
   ///  p->len = 0;   /// outros campos do descritor
   ///  p->fim = NULL;
}

int push(TpDADO x, TpPILHA *p) { /// empilhar x

    TpNODE *paux;
    /// alocar memoria
    paux = (TpNODE*) malloc(sizeof(TpNODE));
    /// se houve erro na alocacao, entao paux eh NULL (??)
    /// em C, NULL eh o mesmo que ZERO
    if(!paux) {
        printf("\n ERRO na alocacao de um novo NODO na pilha.");
        return -1;
    }

    /// inserir x = 20 na memoria alocada
    paux->dado = x;
    paux->prox = p->topo;
    p->topo = paux;

    return 1;/// sucesso
}

int pop(TpDADO *x, TpPILHA *p) { /// desempilhar x

    if(!p->topo) {
            printf("\n ERRO no desempilhamento. Pilha vazia.");
            return -2;// nao se pode desempilhar em pilha vazia
    }
    /// tem dados empilhados
    TpNODE *paux;
    paux = p->topo;
    /// copiar o valor do dado armazenado no topo da pilha
    *x = paux->dado;
    p->topo = paux->prox;
    paux->prox = NULL; /// desligar do encadeamento a caixa do topo.

    free(paux); /// desalocar da mem�ria o NODO desempihado
    return 2;
}


int WritePGM(const char* arq, const char* tpPGM, pgm* pPgm) {

printf("\n ..... (ARQUIVO GRAVADO)-->%s.", arq);
        FILE *f;

        f = fopen(arq, "w");  /// modo "w" --> abrir para escrita
        if (!f) {
            printf("\n ERRO: Incapaz de abrir arquivo: %s.", arq);
            return -1;  // algum c�digo de erro - Arquivo nao existe.
        }

        ///gravar no arquivo o cabe�alho de imagens PGM cinza

        fprintf(f, "%s\n", tpPGM); ///  assinatura PGM:
                /// color "P3", cinza "P2" ou binario "P1"
        if (!strcmp(tpPGM, "P3")) {/// a imagem � colorida???
                                      /// Se sim, largura est� multiplicada por 3
            fprintf(f,"%d %d\n", pPgm->w/3, pPgm->h); // divide a largura por 3

        }else {
            fprintf(f,"%d %d\n", pPgm->w, pPgm->h); // imagem bin�ria ou cinza.
        }
        fprintf(f,"255\n"); // valor de brilho m�ximo na imagem (use sempre 255

        /// gravar no arquivo os valores dos pixels da imagem computada
        for ( int k = 0; k < (pPgm->w * pPgm->h); k++) {
            fprintf(f,"%d ", pPgm->pData[k]);
        }

        fclose(f);

        printf("\n ..... (ARQUIVO GRAVADO)-->%s.", arq);
        return(1);
}


int ReadPGMP2(const char* arq, pgm* pPgm) {
    // ReadPGMP2 l� uma imagem gravada em arquivo com formato PGM "P2"
    //      INPUT: arq � uma string que aponta o caminho e o nome do arquivo PGM P2 que vai ser lido.
    //             exemplo: const char* arq = "D:\\AulasAlgoritimosEstruturas\\ignNIR.pgm";
    //      OUTPUT: fd retorna o descritor de arquivo (ponteiro) que atuar� como tratador do arquivo arq.
    //              Se o arquivo arq n�o existir, ou n�o for encontrado no caminho fornecido,  ou n�o for um
    //              arquivo PGM "P2", a execu��o desta fun��o � abortada e fd e pPgm ficam indefinidos.
    //              pPgm � um ponteiro para uma struct com campos definidos em pgm, a qual vai armazenar
    //              dados relevantes que est�o gravados no arquivo PGM arq.

       int word;            // inteiro de prop�sito geral
       unsigned int nRead = 0;       // �ndice para o vetor/matriz de dados (pixels) da imagem
       char readChars[256]; // buffer para ler caracteres do arquivo (prop�sito geral)

       FILE* fd;  /// descritor para um arquivo

       //abrir arquivo de entrada arq e checar se teve sucesso
       fd = fopen(arq, "r");  // modo "r" --> abrir somente para leitura
       if (!fd) {
         printf("\n ERRO: Incapaz de abrir arquivo: %s.\n\n", arq);
         exit(1);  // ERRO 1: arquivo inexistente ou n�o encontrado no caminho especificado.
         // encerra a execu��o do programa e fecha todos os arquivos abertos
       }
       // se o arquivo existe, ele pode ser um PGM. Ent�o,
      fscanf (fd, "%s", readChars); // leia a primeira linha (string) do arquivo fd cujo valor esperado � "P2"

      if ((strcmp(readChars, "P2"))) { //tipo PGM n�o � v�lido? strcmp(s1,s2) compara os caracteres das
                                       //   strings s1 e s2 e retorna o valor zero se s1 � exatamente igual a s2
        printf ("\n\nErro em PGM: %s. Formato nao suportado em:  ", readChars);
        fclose(fd);
        exit(2);  // c�digo de erro para "Arquivo n�o � um PGM P2"
      }
       // o arquivo arq vinculado ao descritor fd tem assinatura PGM "P2", ent�o
       fscanf (fd, "%s", readChars); // leia a segunda linha

       while (readChars[0] == '#') {   // se no cabe�alho do arquivo existe uma linha de coment�rio,
          fgets (readChars, 255, fd);  // ela come�a com o char "#".

          fscanf (fd, "%s", readChars); // Pular essa linha (ela � irrelevante)
        }
        sscanf (readChars, "%d", &pPgm->w);  // para preencher os campos da struct � importante manter a
        fscanf (fd, "%d", &pPgm->h);        // mesma ordem da defini��o desses campos.
        fscanf (fd, "%d", &pPgm->max);

         unsigned int Totalpixels = (pPgm->w) * (pPgm->h);

         pPgm->pData = (Tpixel*)malloc(sizeof(Tpixel) * (Totalpixels)); // pData � um vetor alocado dinamicamente
        // ler cada o valor de brilho de cada pixel do arquivo da imagem e armazen�-lo corretamente no
        // suporte do reticulado (matriz) da imagem, o qual � um vetor criado dinamicamente.


        for (nRead = 0; nRead < Totalpixels; nRead++) {
          fscanf(fd, "%d" ,&word); // l� o valor de brilho de um pixel do arquivo
          pPgm->pData[nRead] = word; // armazena o valor deste pixel no vetor alocado
        } // for

       fclose(fd); // sempre fechar o arquivo se n�o � o mesmo n�o � mais necess�rio
printf("\n ..... (LIDOS DADOS do ARQUIVO )-->%s.", arq);

       return 0; // retorne os dados de imagem no nome da fun��o
     } // ReadPGMP2 - fim da fun��o


int MemImgZero(pgm* atual, pgm* zeropgm) {
    /// MemImgZero ---> cria na memoria RAM um reticulado para suporte de dados de imagem (pPgm)
    ///                 com dimensoes (pPgm->h x pPgm->w) = tp bytes. Todos esses  tp pixels do reticulado
    ///                 serao associados com o valor ZERO. O reticulado eh um vetor de Tpixel
    ///                 apontado pelo ponteiro *pData (Tpixel *pData).
    ///
    ///                 os dados sao copyados de pgm* atual
    zeropgm->w = atual->w;
    zeropgm->h = atual->h;
    zeropgm->max = atual->max;

    unsigned int tp, Totalpixels = (zeropgm->w) * (zeropgm->h);

    zeropgm->pData = (Tpixel*)malloc(sizeof(Tpixel) * (Totalpixels));
    /// pData � um vetor alocado dinamicamente.
    /// pData � o suporte do reticulado (matriz) da imagem.
    if (!(zeropgm->pData)) {
        printf("ERRO na alocacao de matriz de zeros.");
        return -1;
    }

    const Tpixel ZERO = 0;
    for (tp = 0; tp < Totalpixels; tp++) {
            zeropgm->pData[tp] = ZERO;
    } // for

printf("\n ..... Criada Matriz ZEROS[%d, %d](.", zeropgm->h, zeropgm->w);

    return 1; /// Sucesso
}


Tpixel GetPixel(pgm* img, int L, int C){

    /// abstrair o vetor img->pData como uma matriz
    /// de dimensoes  (img->h x img->w)

    if ((L >= img->h) ||  (C >= img->w) || ( L < 0) || (C < 0)) {
        printf("\n ..... Coordenada de imagem esta fora dos limites da grade da imagem.");
        exit(0);
    }
    Tpixel K;
    K = *((img->pData) + L*img->w + C);

    return (K);
}

int PutPixel(pgm* img, int L, int C, Tpixel v){

    /// abstrair o vetor img->pData como uma matriz
    /// de dimensoes  (img->h x img->w)

    if ((L >= img->h) ||  (C >= img->w) || ( L < 0) || (C < 0)) {
        printf("\n ..... Coordenada de imagem esta fora dos limites da grade da imagem.");
        exit(0);
    }
    Tpixel *K; ///unsigned long int *K;
   //*((img->pData) + L*img->w + C)
    K = (img->pData) + L*img->w + C;
   *K = v;

    return (1);
}


int MorphGrad33(pgm* img, pgm* grad) {
    /// computar o gradiente morfologico da imagem img
    /// armazenar o resultado na imagem grad.
    MemImgZero(img, grad);

    /// fazer a convolucao da superficie da imagem com o
    /// elemento estruturante 3x3 (janela 3x3)

    int L, C, k, j;
    Tpixel max, p;
    for (L = 1; L < img->h - 1; L++) {
        for (C = 1; C < img->w - 1; C++) {
            max = 0;
            /// convolucao para dilatacao cinza 3x3
            for (k = -1; k<=1; k++) {    /// elemento estruturante EE 3x3
                for (j = -1; j<=1; j++){
                    p = GetPixel(img, L + k, C + j);
                    if (p > max) max = p;  /// valor de cinza maximo coberto pelo EE
                } // for j
            } // for k
            /// encontrou o valor de cinza maximo max coberto pelo elemento estruturante
            /// armazenar o valor max nas coordenadas (L, C) da matrix grad
            p = max - GetPixel(img, L , C);
            PutPixel(grad, L, C, p);
        } // for C

    } // for L
printf("\n ..... Processado o Gradiente Morfologico da Imagem.");
  return 0;
}


TpDADO pilha_semente(TpPILHA *pilha, TpDADO x, int LS, int CS, int VS, pgm *imgGROW){
    /* Guarda a cordenada do ponto semente na pilha e marcar o ponto semente na imagem*/

    InicializaPilha(pilha); /// indicando que a pilha est� vazia

    x.L = LS; /// copiando o valor das coordenadas do ponto semente para os
    x.C = CS; /// campos da struct TpDADO usada no empilhamento das coordenadas
    printf("\n Valor do Ponto Semente  =  %d \n", VS);

    /// empilhar a coordenada do ponto semente na pilha
    push(x, pilha);
    /// marcar na imagem resultado que o ponto semente pertence a regi�o desejada
    /// .... tem o mesmo significado que fazer  imgGROW[x.L][x.C] = 1
    PutPixel(imgGROW, x.L, x.C, 1);
    return x;
}

void mapear_os_vizinhos(TpPILHA *pilha, TpDADO x, TpDADO y, pgm *imgOR, pgm *imgGROW, int VS, int critsim){
    /* */
    int k, j; /// auxiliares para visitar os 8-vizinhos de um pixel
    int sim;  /// medida de similaridade de um pixel em rela��o ao
              ///  valor VS do ponto semente -->
              ///     sim = (abs(imgOR[?][?] - VS)) <= critsim);
    Tpixel Vpix; // auxiliar para valor de um pixel
    Tpixel Growpix; // auxiliar para definir se um pixel j� foi pocessado ou n�o

    while (pilha->topo) {  /// enquanto existir coordenada na pilha
        pop(&x, pilha);    /// desempilhar uma coordenada do topo
        for (k = -1; k<=1; k++) {    /// elemento estruturante EE 3x3
            y.L = x.L + k;  // s� depende do k
            for (j = -1; j<=1; j++){
                y.C = x.C + j ;
                Vpix = GetPixel(imgOR, y.L, y.C); /// recuperar o valor do pixel (L,C)
                                             /// na imagem original imgOR
                Growpix = GetPixel(imgGROW, y.L, y.C); /// recuperar o valor do pixel (L,C)
                ///       correspondente na imagem resultado imgGROW para saber se esse
                ///       pixel j� foi processado (1) ou n�o (0)
                sim = (abs(VS - Vpix) <= critsim);  /// pergunta (???): o valor do pixel Vpix
                 ///       de coordenada (y.L, y.C) armazenado na imagem original imgOR �
                 ///       similar (sim == 1) ou n�o � similar (sim==0) ao ponto semente??

        ///  se esse pixel de coordenada (y.L, y.C) � similar (sim == 1)
        ///  ao ponto semente e, ainda, se ele N�O foi processado (Growpix == 0
        ///  que � o mesmo que !Growpix) temos que realizar duas a��es:
        ///     (1)  marcar esse pixel na imagem resultado com o valor 1 e;
        ///     (2)  empilhar essa coordenada y .
        ///  A opera��o (1) diz que esse pixel pertence a regi�o de interesse, e
        ///  a opera��o (2) diz que todos os vizinhos desse pixel devem ser investigados

                if (!Growpix && sim) {
                    push(y, pilha);  /// empilhar essa coordenada
                    PutPixel(imgGROW, y.L, y.C, 1); /// registrar o valor "1 o valor
                                        /// como resultado desejado.
///printf(" (%d, %d, %d) ", y.L, y.C, GetPixel(imgGROW, y.L, y.C));
                } // if
            } // for j
        } // for k
    } // while
}

void gerar_imagenspgm_borda(pgm *imgCOLOR, pgm *imgOR, pgm *imgBORD){
    /* Gera a imagem pgm com borda colorida do lago*/
    

    /// gerar borda colorida - a estrutura de uma imagem colorida tem 3 vezes mais pixels.
                 //nome do arquivo da imagem colorida
     const char* NColorBORDUmu  = "UmuColorBordGeoEye.ppm";
     
     imgCOLOR->h = imgOR->h; /// o n�mero de linhas � o mesmo. Entretanto,
     imgCOLOR->w = 3*(imgOR->w); /// o n�mero de colunas na imagem colorida ("P3") �
                            /// tr�s vezes maior que o n�mero de colunas de uma imagem
                            /// em tons de cinza ("P2") ou bin�ria ("P1"). O valor de
                            /// colunas 3 vezes maior que as outras imagens se deve ao
                            /// fato que agora precisamos de 3 valores (R, G, B) para cada
                            /// pixel da imagem.

     imgCOLOR->max = 255; /// campo in�til (maior valor de brilho na imagem)

    /// observe que, por enquanto, temos apenas o descritor da imagem imgCOLOR.
    /// Precisamos alocar o reticulado de suporte da imagem (MATRIZ). Uma maneira �
    /// copiar o decritor e criar uma imagens com pixels com valor zero.
    MemImgZero(imgCOLOR, imgCOLOR);  /// com isso, a imagem imgCOLOR tem estrutura de
                    /// uma imagem colorida e todos os pixels dela s�o pretos.

    int j, k;
    /// vamos percorrer os pixels da imagem que cont�m somente a borda do objeto desejado
    int TotalPix = imgBORD->w * imgBORD->h;
    j = -1;
    for (k = 0; k<TotalPix; k++){
        if (imgBORD->pData[k]) { /// se o k-�simo pixel da borda � "1"
                /// mostra ele na cor vermelha na imagem colorida
            imgCOLOR->pData[++j] = 255; /// R = 255 (brilha o vermelho)
            imgCOLOR->pData[++j] = 0; /// G = 0 (desliga o verde)
            imgCOLOR->pData[++j] = 0; /// B = 0 (desliga o azul)
        } else { /// se n�o � borda, mostrar os brilhos de cinzas originais
            imgCOLOR->pData[++j] = imgOR->pData[k];  /// repetir o o mesmo valor de
            imgCOLOR->pData[++j] = imgOR->pData[k];  /// cinza para completar os valores
            imgCOLOR->pData[++j] = imgOR->pData[k];  /// RGB dos pixels da imagem colorida
        }

    } // for
     WritePGM(NColorBORDUmu, "P3", imgCOLOR); /// gravar a imagem PPM ("P3")
}

int main(){

    ///                 caminhos e NOMES dos arquivos em disco
    const char* NimgOR   = "C:\\ProgramasC\\UmuNirGeoEye.pgm"; /// imagem original cinza
    const char* NimgGROW = "UmuGrowGeoEye.pbm";/// imagem bin�ria da silhueta do lago
    const char* NimgBORD = "UmuBordGeoEye.pbm";///imagem bin�ria da borda do lago



    /// descritores para os dados das imagens na mem�ria principal
    /// estruturas de dados para armazenar dados de imagens como
    ///                    VETORES ou MATRIZES
    pgm *imgOR, *imgGROW, *imgBORD;

    /// aloca��o dos descritores de cada imagem
    
    imgOR = malloc (sizeof(pgm));///descritor para dados da imagem original
    imgGROW = malloc (sizeof(pgm));///descritor para dados da imagem da silhueta do lago
    imgBORD = malloc (sizeof(pgm));///descritor para dados da imagem da borda do lago


    ///      ( NOME,  DESCRITOR )
    ReadPGMP2(NimgOR, imgOR);  /// transferir do arquivo para a mem�ria principal
                               /// os dados da da imagem original.
///
    MemImgZero(imgOR, imgGROW); /// faz uma c�pia da estrutura do descritor
          ///  da imagem imgOR para o descritor imgGROW e aloca todos os pixels
          ///  de  imgGROW->pData com o valor ZERO
    
    

    int critsim = 10;   /// limite do crit�rio de similaridade
    int LS = 377, CS = 507; /// coordenada linha (LS) e coluna (CS) do ponto semente
    int VS = GetPixel(imgOR, LS, CS); /// VS - valor de brilho do ponto semente

    /// ---------------------------------------------------
    /// Crescimento de Regi�o - propaga��o do ponto semente
    /// ---------------------------------------------------

    ///                 criar  pilha

    TpPILHA *pilha;
    TpDADO  x, y;

    /// alocar o descritor da PILHA
    pilha = (TpPILHA*) malloc(sizeof(TpPILHA));
    if (!pilha) {
        printf("\n ERRO de alocacao da PILHA:\n");
        exit(0);
    }

    x = pilha_semente(pilha, x, LS, CS, VS, imgGROW); // Coloca o pixel semente na pilha e na imagem

    mapear_os_vizinhos(pilha, x, y, imgOR, imgGROW,  VS, critsim); // Mapea os pixels vizinhos semelhantes

    MorphGrad33(imgGROW, imgBORD);  /// gerar a borda da regi�o

    WritePGM(NimgGROW, "P1", imgGROW);
    WritePGM(NimgBORD, "P1", imgBORD);

   
     pgm *imgCOLOR; // descritor da imagem colorida
     imgCOLOR = malloc (sizeof(pgm));///aloca��o do descritor para imagem colorida
     

     gerar_imagenspgm_borda(imgCOLOR, imgOR, imgBORD); // Imagem com borda


    /// sequ�ncia correta de desaloca��o:
    ///     (1) desalocar os dados (pixels) da imagem
    ///     (2) desalocar o descritos da imagem


    ///  pixels da imagem    descritor da imagem
        free(imgOR->pData);      free(imgOR);
        free(imgGROW->pData);    free(imgGROW);
        free(imgBORD->pData);    free(imgBORD);
        free(imgCOLOR->pData);   free(imgCOLOR);

    /// desalocar o descritor da PILHA
       free(pilha);


return 0;
} // main



