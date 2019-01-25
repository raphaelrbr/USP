#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "palavra.h"
#include "vetor.h"
#include "lista.h"
#include "arvore.h"

/*Le e retorna uma sequencia maximal de caracters alfanumericos de um arquivo f*/
char * leAlfaNum(FILE * f){
	int i = 0;
	int n = 50;
	char * buffer = malloc(n*sizeof(char));
	int c;
	while((c = fgetc(f)) != EOF) {
		if(isalnum(c)){
			if (i == n)  {
				buffer = realloc(buffer,2*n*sizeof(char));
				n = 2*n;
			}
			buffer[i] = c;
			i++;
		}
		else break;
	}
	buffer[i] = 0;
	return buffer;

}

/*Retorna 1 se a palavra x é menor ou igual a palavra y,
comparando pelo numero de ocorrencias. O critério
de desempate é a ordem alfabetica */
int menorIgualOcr(Palavra x, Palavra y){
	if ((x->ocr) == (y->ocr)) {
		return (strcmp(x->p, y->p) < 0);
	}
	return ((x->ocr) < (y->ocr));
}

/*Retorna 1 se a palavra x é menor ou igual a palavra y,
comparando por ordem alfabetica. O critério de desempate
é o numero de ocorrencias*/
int menorIgualPlv(Palavra x, Palavra y){
	if (strcmp(x->p, y->p) == 0) {
		return ((x->ocr) <= (y->ocr));
	} 
	return (strcmp(x->p, y->p) < 0);
}

/*Algoritmo do separa*/
int separa (Palavra v[], int p, int r, int(*compara)(Palavra, Palavra) ) {
   Palavra c = v[r]; // pivô
   int j = p;
   Palavra t;
   for (int k = p; k < r; ++k)
      if ((*compara)(v[k], c)) {
         t = v[j], v[j] = v[k], v[k] = t;
         ++j; 
      } 
   t = v[j], v[j] = v[r], v[r] = t;
   return j; 
}

/*Algoritmo quicksort levemente modificado para permitir
a inclusão de uma função de comparação entre dois elementos*/
void quicksort (Palavra v[], int p, int r, int(*compara)(Palavra, Palavra))
{
   if (p < r) {                   
      int j = separa (v, p, r, compara);   
      quicksort (v, p, j-1, compara);      
      quicksort (v, j+1, r, compara);      
   }
}



int main(int argc, char * argv[]){
	FILE * f = fopen(argv[1], "r");
	int tamanho = 0;
	Palavra p;
	Lista l = NULL;
	Arvore a = NULL;
	char * k;
	
	/*laço principal, le sequencia maximal de caracteres insere na estrutura de dados
	correta*/
	 while(!feof(f)){
	 	k = leAlfaNum(f);
	 	if (strcmp(k,"") != 0) {
	 		p = criaPalavra(k);
	 		if(strcmp(argv[2], "VD") == 0) insereVetorDesordenado(p, &tamanho);
	 		else if(strcmp(argv[2], "VO") == 0) insereVetorOrdenado(p, &tamanho);
	 		else if(strcmp(argv[2], "LD") == 0) l = insereListaDesordenada(l, p);
	 		else if(strcmp(argv[2], "LO") == 0) l = insereListaOrdenada(l, p);
	 		else if(strcmp(argv[2], "AB") == 0) a = insereArvore(a, p);
	 	}
	}

	/*As operações a seguir imprimem a saída da forma correta, 
	ordenando por numero de ocorrencias ou em ordem lexicografica*/

	if(strcmp(argv[2], "LD") == 0 || strcmp(argv[2], "LO") == 0) passaLista(l, &tamanho);


	if (strcmp(argv[3],"O") == 0) {
		if (strcmp(argv[2], "AB") == 0 ) passaArvore(a, &tamanho);
		quicksort(vetor, 0, tamanho-1, menorIgualOcr);
		imprimeVetor(tamanho);
	}

	else{
		if ( strcmp(argv[2],"VD") == 0 || strcmp(argv[2],"LD") == 0 ) {
			quicksort(vetor, 0, tamanho-1, menorIgualPlv);
			imprimeVetor(tamanho);
		}
		else if (strcmp(argv[2],"LO") == 0 ) {
			imprimeVetor(tamanho);
		}
		else if (strcmp(argv[2],"VO") == 0 ) {
			imprimeVetor(tamanho);
		}
		else {
			inOrdem(a);
		}

	}


	fclose(f);
	return 0;
}