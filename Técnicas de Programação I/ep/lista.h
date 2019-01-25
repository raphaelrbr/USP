/*
Técnicas de Programacao 1
Professor: Marcos Dimas Gubitoso
Integrantes do grupo
Paulo Silva - NUSP 8941112
Thiago Pena - NUSP 6847829
Raphael Ribeiro - NUSP 10281601
*/

#ifndef __LISTA_H__
#define __LISTA_H__


typedef struct elo {
  struct elo *next, *previous;
  void *val;
} Elo;

typedef struct {
  Elo *cabec;
} Lista;

/* Cria e retorna uma lista vazia */
Lista *lista_cria();

/* Destroi a lista l */
void lista_destroi(Lista *l);

/* Insere o valor val na lista l, retornando o endereco do elemento inserido */
/* ou NULL em caso de erro. */
Lista *lista_insere(Lista *l, void *val);

/* Retorna o valor associado ao nome n na lista l */
/* ou NULL caso o elemento nao seja encontrado. */
void *lista_busca(Lista *l, char *n);

/* Remove o elemento associado ao valor val na lista l, sem remove-lo da memoria. */
void lista_retira(Lista *l, void * val);

#endif
