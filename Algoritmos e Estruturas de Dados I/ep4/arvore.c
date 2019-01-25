#include "arvore.h"
#include "palavra.h"
#include "vetor.h"
#include <stdlib.h>
#include "string.h"
#include <stdio.h>

Arvore insereArvore(Arvore a, Palavra pp){
	if (a == NULL){
		Arvore novaArvore = malloc(sizeof(no));
		novaArvore->esq = NULL;
		novaArvore->dir = NULL;
		novaArvore->info = pp;
		return novaArvore;
	}
	else if(strcmp(a->info->p, pp->p) == 0) {
		a->info->ocr = (a->info->ocr) + 1;
		return a;
	}
	else if (strcmp(a->info->p, pp->p) > 0){
		a->esq = insereArvore(a->esq, pp);
		return a;
	}
	else {
		a->dir = insereArvore(a->dir, pp);
		return a;
	}
}

void inOrdem(Arvore a){
	if (a != NULL){
		inOrdem(a->esq);
		printf("%s %d\n", a->info->p, a->info->ocr);
		inOrdem(a->dir);
	}
}

void passaArvore(Arvore a, int * tamanho){
	if (a != NULL){
		passaArvore(a->esq, tamanho);
		vetor[*tamanho] = a->info;
		(*tamanho) = (*tamanho) + 1;
		passaArvore(a->dir, tamanho);
	}

}