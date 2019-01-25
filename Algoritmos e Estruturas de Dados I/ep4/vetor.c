#include "palavra.h"
#include <string.h>
#include <stdio.h>

Palavra vetor[1000000];

void insereVetorDesordenado(Palavra palavra, int * tamanho){
	/*Verifica se a palavra ja esta no vetor */
	for(int i = 0; i < (*tamanho); i++){
		if(strcmp(vetor[i]->p,palavra->p) == 0) {
			(vetor[i]->ocr) = (vetor[i]->ocr) + 1;
			return;
		}
	}
	/*Se a palavra nao esta no vetor, adiciona a palavra no fim do vetor */
	vetor[(*tamanho)] = palavra; 
	(*tamanho) = (*tamanho) + 1;
}


void insereVetorOrdenado(Palavra palavra, int * tamanho){
	if (*tamanho == 0) {
		vetor[0] = palavra;
		*tamanho = (*tamanho) + 1;
		return;
	}
	int p = 0;
	int q = (*tamanho)-1;
	int n = (*tamanho);
	int h;
	int c;
	int k;
	while(p <= q){
		h = (p+q)/2;
		c = strcmp(vetor[h]->p,palavra->p);

		if ( c == 0) {
			(vetor[h]->ocr) = (vetor[h]->ocr)  + 1;
			return;
		}

		else if ( c < 0){
			p = h+1;

		}
		else {
			q = h-1;
		}

	}
	/*Nesse ponto, a palavra nao esta no vetor */
	/*A palavra deve ser inserida em p ou h;*/
	if (c<0) k = p;
	else k = h;
	while(n > k){
		vetor[n] = vetor[n-1];
		n--;
	}
	vetor[k] = palavra;
	(*tamanho) = (*tamanho) + 1;

}

void imprimeVetor(int tamanho){
	for(int i = 0; i<tamanho; i++){
		printf("%s %d\n", vetor[i]->p, vetor[i]->ocr);
	}
}



