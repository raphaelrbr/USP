#ifndef __ARVORE_H__
#define __ARVORE_H__

#include "palavra.h"

/*Estrutura de um no da arvore*/
typedef struct no{
	struct no * esq;
	struct no * dir;
	Palavra info;
} no;

typedef no * Arvore;

/*Insere uma palavra na arvore a*/
Arvore insereArvore(Arvore a, Palavra pp);

/*Percorre a arvore a in ordem*/
void inOrdem(Arvore a);

/*Passa a arvore a para o vetor global vetor,
e guarda em tamanho o tamanho do vetor */
void passaArvore(Arvore a, int * tamanho);

#endif