#include <stdio.h>
#include <stdlib.h>


/*Estrutura auxiliar que guarda a posicao linha coluna em que uma palavra
de um certo indice foi colocada na matriz. Isto é, 
tab[linha][coluna] guarda a primeira letra de palavras[indice]. */

typedef struct{
    int linha;
    int coluna;
    int indice;
} palavraColocada;

/*Implementação de uma pilha do tipo palavraColocada*/

typedef struct{
    palavraColocada * v;
    int topo;
    int max;
} pilha;

typedef pilha * Pilha;

void resize(Pilha P)
{
    int i;
    palavraColocada*novo=malloc(2*P->max*sizeof(palavraColocada));
    for (i=0;i<P->max;i++) novo[i]=P->v[i];
    P->max=2*P->max;
    free(P->v);
    P->v=novo;
}


int PilhaVazia (Pilha P)
{
    if (P->topo==0)  return(1);
    return(0);
}

void Empilha (Pilha P, palavraColocada el)
{
    if (P->topo==P->max){
        resize(P);
    }
    P->v[P->topo]=el;
    (P->topo)++;
}

void Desempilha(Pilha P)
{
    if (PilhaVazia(P)){
        printf ("Erro!\n");
        return;
    }
    (P->topo)--;
}

palavraColocada TopoDaPilha(Pilha P)
{
    return(P->v[P->topo-1]);
}

Pilha CriaPilha(int max)
{
    Pilha P = malloc(sizeof(pilha));
    P->v=malloc(max*sizeof(palavraColocada));
    P->topo=0;
    P->max=max;
    return(P);
}

void DestroiPilha(Pilha P)
{
    free(P);
}


int calculaTamanho(char * palavra){
    /* Retorna o tamanho de uma palavra */
    int i = 0, tam = 0;
    while (palavra[i] != '\0') tam++, i++;

    return tam;



}

int tamanhoEspacoH(int ** tab, int nColunas, int linha, int coluna){
    /*Calcula o tamanho de um espaço vazio para colocar uma palavra
    horizontalmente no tabuleiro*/

    int tamanho = 0;
    int i = coluna;

    /*Retrocede o marcador até o inicio do espaço para colocar a palavra */
    while(i > 0 && tab[linha][i-1] != -1) i--;

    /*Calcula o tamanho do espaço */
    while(i < nColunas && tab[linha][i] != -1) {
        tamanho++, i++;
    }
    return tamanho;
}


int tamanhoEspacoV(int ** tab, int nLinhas, int linha, int coluna){
    /*Calcula o tamanho de um espaço vazio para colocar uma palavra
    verticalmente no tabuleiro*/

    int tamanho = 0;
    int i = linha;

    /*Retrocede o marcador até o inicio do espaço para colocar a palavra */
    while(i > 0 && tab[i-1][coluna] != -1) i--;

    /*Calcula o tamanho do espaço */
    while(i < nLinhas && tab[i][coluna] != -1) {
        tamanho++, i++;
    }

    return tamanho;
}


int colocaPalavraH(int ** tab, int lin, int col, int nLinhas, int nColunas, char * palavra){
    /*Verifica se é possivel colocar uma palavra horizontalmente no tabuleiro a 
    partir de uma posicao linxcol, retornando 1 se é possível e 0 caso contrário. 
    Observe que esta função só é chamada quando o tamanho da palavra é igual ao
    tamanho do espaço vazio.*/

    int letra = 0, tamanhoPalavra, i = col;

    /*Retrocede o marcador para o inicio do espaço */
    while(i > 0 && tab[lin][i-1] != -1) i--;

    /*Tenta colocar a palavra, letra por letra */
    /* Enquanto ainda tiver letras da palavra a serem colocadas */
    while (palavra[letra] != '\0' ) {

        /*Se acabou o espaço disponivel, retorna 0 */
        if (i == nColunas || tab[lin][i] == -1) return 0;

        /* Se o espaço está livre, coloca a letra */
        if (tab[lin][i] == 0) tab[lin][i] = (int)palavra[letra];

        

        /*Se a letra no tabuleiro é diferente da letra a ser colocada, retorna 0 */
        if (tab[lin][i] != palavra[letra]) return 0;
        
        /*Avança para a próxima letra */
        i++;
        letra++;
    }

    /*Se o espaço foi totalmente preenchido */
    if (i == nColunas || tab[i-1][col] == -1) return 1;

    /*Se o espaço nao foi totalmente preenchido */
    return 0;

}

int colocaPalavraV(int ** tab, int lin, int col, int nLinhas, int nColunas, char * palavra){
    /*Verifica se é possivel colocar uma palavra verticalmente no tabuleiro a 
    partir de uma posicao linxcol, retornando 1 se é possível e 0 caso contrário. 
    Observe que esta função só é chamada quando o tamanho da palavra é igual ao
    tamanho do espaço vazio.*/

    int letra = 0, tamanhoPalavra, i = lin;

    /*Retrocede o marcador para o inicio do espaço */
    while(i > 0 && tab[i - 1][col] != -1) i--;

    /*Tenta colocar a palavra, letra por letra */

    /* Enquanto ainda tiver letras da palavra a serem colocadas */
    while (palavra[letra] != '\0' ) {

        /*Se acabou o espaço disponivel, retorna 0 */
        if (i == nLinhas || tab[i][col] == -1) return 0;

        /*Se o espaço está livre, coloca a letra */
        if (tab[i][col] == 0) tab[i][col] = (int)palavra[letra];

        /*Se a letra no tabuleiro é diferente da letra a ser colocada, retorna 0 */
        if (tab[i][col] != palavra[letra]) return 0;

        /*Avança para a próxima letra */
        i++;
        letra++;
    }

    /*Se o espaço foi totalmente preenchido */
    if (i == nLinhas || tab[i-1][col] == -1) return 1;

    /*Se o espaço nao foi totalmente preenchido */
    return 0;

}


int resolve(int **tab, int nLinhas, int nColunas, char ** palavras, int nPalavras){
    /*Preenche o tabuleiro tab a partir do vetor de palavras,
    retornando 1 se é possível resolver o tabuleiro e 0 caso
    contrário */

    /*Cria uma pilha auxiliar de tamanho 100 para
    armazenar os índices das palavras colocadas no
    tabuleiro e suas posições */

    Pilha P = CriaPilha(100);
    int lin = 0, col = 0, deuCerto = 0, palavraAtual, tamanhoAtualH, tamanhoAtualV;

    int * palavrasDisponiveis = malloc (nPalavras * sizeof(int));
    for(int i = 0; i< nPalavras; i++) palavrasDisponiveis[i] = 0;

    palavraColocada aux;

    /*Vetor auxiliar para armazenar o tamanho das palavras */
    int * tamanhoPalavras = malloc (nPalavras * sizeof(int));
    for (int i = 0; i< nPalavras; i++) {
        tamanhoPalavras[i] = calculaTamanho(palavras[i]);
    }

    while (lin < nLinhas) {
        col = 0;
        while (col < nColunas) {
            if (tab[lin][col] == 0){ 
                tamanhoAtualH = tamanhoEspacoH(tab, nColunas, lin, col);
                tamanhoAtualV = tamanhoEspacoV(tab, nLinhas, lin, col);

                deuCerto = 0;
                palavraAtual = 0;
                

                while(!deuCerto){
                    /*Se a palavra está disponível */
                    if (palavrasDisponiveis[palavraAtual] != -1) {

                        /*tenta colocar a palavra horizontalmente */
                        if (tamanhoPalavras[palavraAtual] == tamanhoAtualH)
                            deuCerto = colocaPalavraH(tab, lin, col, nLinhas, nColunas, palavras[palavraAtual]);

                        /*Se nao foi possivel colocar a palavra horizontalmente, tenta colocar verticalmente */
                        if (!deuCerto && tamanhoPalavras[palavraAtual] == tamanhoAtualV)
                            deuCerto = colocaPalavraV(tab, lin, col, nLinhas, nColunas, palavras[palavraAtual]);

                    }

                    /*Se foi possivel colocar a palavra, empilha a palavra colocada*/
                    if (deuCerto){
                        if (col == nColunas - 1) {
                        lin++;
                        }
                        col++;
                        aux.linha = lin;
                        aux.coluna = col;
                        aux.indice = palavraAtual;
                        Empilha(P, aux);
                        palavrasDisponiveis[palavraAtual] = -1;
                    }
                        
                            
                    /*Caso contrário, tenta a proxima palavra. Se não há mais palavras,
                    backtrack */
                    else {

                        if (palavraAtual + 1< nPalavras) palavraAtual++;

                        

                        else {

                            if (PilhaVazia(P)) return 0;
                            aux = TopoDaPilha(P);
                            Desempilha(P);
                            lin = aux.linha;
                            col = aux.coluna;
                            palavraAtual = aux.indice;
                        }
                    }
                }



                
            }

            else {
                if (col == nColunas -1) lin++;
                col++;
            }
        }
    }

    /*Imprime a matriz */

    for(int i = 0; i<nLinhas ; i++) {
        for (int k = 0; k<nColunas; k++) {
            if (tab[i][k] == -1) printf("* ");
            else printf("%c ",(char)tab[i][k] );
        }
        printf("\n");
    }
    return 1;
}





int main(){
    int l = -1,c = -1,h, a, z = 1;




    /* Le a primeira matriz */
    scanf("%d", &l);
    scanf("%d", &c);

    /*Repete o laço principal enquanto a última matriz lida não for 0x0 */
    while(l != 0 && c != 0) {

   
        int ** tab = malloc(l *sizeof(int));
        for (int i = 0; i< l; i++) tab[i] = malloc(c * sizeof(int));

        for(int i = 0; i<l; i++) {
            for(int k = 0; k<c; k++) scanf("%d", &tab[i][k]);
        }

        /* Le o numero de palavras */
        scanf("%d", &h);

        /* Cria um vetor de h posições de strings de 100 caracteres no máximo */
        char ** palavras = malloc(h * sizeof(char));
        for (int i = 0; i< h; i++) palavras[i] = malloc(100 * sizeof(char));

        /*Le as palavras e armazena no vetor */
        for (int i = 0; i< h; i++) scanf("%s", palavras[i]);

        printf("Instancia %d\n", z);
        a = resolve(tab, l, c, palavras, h); 
        if (!a) printf("nao ha solucao\n");

        /*Le a proxima matriz */
        scanf("%d", &l);
        scanf("%d", &c);
        z++;

    }


    
}