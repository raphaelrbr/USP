#include "palavra.h"

#ifndef __LISTA_H__
#define __LISTA_H__


/*Estrutura de uma celula da lista ligada*/
typedef struct cel{
	struct cel * prox;
	Palavra info;
} cel;

typedef cel * Lista;

/*Insere uma palavra na lista ligada de forma
desordenada*/
Lista insereListaDesordenada(Lista l, Palavra pp);

/*Insere uma palavra na lista ligada de forma
ordenada*/
Lista insereListaOrdenada(Lista l, Palavra pp);

/*Passa a lista ligada l para o vetor global
atualizando o tamanho do vetor em tamanho*/
void passaLista(Lista l, int * tamanho);

/*Imprime uma lista ligada*/
void imprimeLista(Lista l);

#endif