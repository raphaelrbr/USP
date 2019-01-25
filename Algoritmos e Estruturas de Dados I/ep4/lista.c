#include "palavra.h"
#include "lista.h"
#include "string.h"
#include "vetor.h"
#include <stdio.h>
#include <stdlib.h>


Lista insereListaDesordenada(Lista l, Palavra pp){
	if (l == NULL){
		Lista novaLista = malloc(sizeof(cel));
		novaLista->prox = NULL;
		novaLista->info = pp;
		return novaLista;
	}
	else if (strcmp(l->info->p,pp->p) == 0) {
		l->info->ocr = (l->info->ocr) + 1;
		return l;
	}
	else {
		l->prox = insereListaDesordenada(l->prox, pp);
		return l;
	}
}

Lista insereListaOrdenada(Lista l, Palavra pp){
	Lista ap = l;
	Lista ant = NULL;
	if (l == NULL){
		Lista novaLista = malloc(sizeof(cel));
		novaLista->prox = NULL;
		novaLista->info = pp;
		return novaLista;
	}
	while (ap != NULL){
		if (strcmp(ap->info->p, pp->p) == 0) {
			ap->info->ocr = (ap->info->ocr) + 1;
			return l;
		}
		if (strcmp(ap->info->p, pp->p) > 0) {
			Lista novaLista = malloc(sizeof(cel));
			novaLista->info = pp;
			novaLista->prox = ap;
			if (ant == NULL){
				return novaLista;
			}
			ant->prox = novaLista;
			return l;
		}
		ant = ap;
		ap = ap->prox;
	}
	/*Nenhuma palavra na lista é igual ou maior que a palavra a ser adicionada, 
	adiciona a palavra no fim da lista*/
	Lista novaLista = malloc(sizeof(cel));
	novaLista->info = pp;
	novaLista->prox = NULL;
	ant->prox = novaLista;
	return l;

}

void passaLista(Lista l, int * tamanho){

	Lista ap = l;
	int i = 0;
	while(ap != NULL){
		vetor[i++] = ap->info;
		ap = ap->prox;
	}
	*tamanho = i;
}

void imprimeLista(Lista l){
	Lista ap = l;
	while (ap != NULL){
		printf("%s %d\n", ap->info->p, ap->info->ocr);
	}
}