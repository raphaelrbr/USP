#ifndef __VETOR_H__
#define __VETOR_H__

#include "palavra.h"

/*Vetor global*/
extern Palavra vetor[1000000];

/*Insere uma palavra em um vetor, de forma 
desordenada*/
void insereVetorDesordenado(Palavra p, int * tamanho);

/*Insere uma palavra em um vetor, de forma
ordenada */
void insereVetorOrdenado(Palavra palavra, int * tamanho);

/*Imprime um vetor*/
void imprimeVetor(int tamanho);

#endif