/*
Técnicas de Programacao 1
Professor: Marcos Dimas Gubitoso
Integrantes do grupo
Paulo Silva - NUSP 8941112
Thiago Pena - NUSP 6847829
Raphael Ribeiro - NUSP 10281601
*/

#include "lista.h"
#include "elemento.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "comandos.h"

Lista *lista_cria()
{
  Lista *l;
  l = malloc (sizeof (Lista));
  l->cabec = malloc (sizeof (Elo));
  l->cabec->next = NULL;
  l->cabec->previous = NULL;
  l->cabec->val = NULL;
  return l;
}

void lista_destroi(Lista *l)
{
  Elo *atual, *prox;
  atual = l->cabec;
  while(atual->next){
    prox = atual->next;
    free(atual->val);
    atual = prox;
  }
  free(atual);
  free(l);
}

Lista *lista_insere(Lista *l, void *val)
{
  Elo *e = malloc (sizeof (Elo));
  e->val = val;
  e->next = l->cabec->next;
  if(l->cabec->next)
    l->cabec->next->previous = e;
  e->previous = l->cabec;
  l->cabec->next = e;
  return l;
}

void *lista_busca(Lista *l, char *n)
{
  Elo *elo;
  elo = l->cabec->next;
  while(elo != NULL && strcmp (((Elemento*)(elo->val))->n, n)){
    elo = elo->next;
  }
  if (elo == NULL) 
    return elo;
  return elo->val;
}

Elo *elo_busca(Lista *l, void *val)
{
  Elo *e = l->cabec->next;
  while(e){
    if(e->val == val) break;
    e = e->next;
  }
  return e;
}

void lista_retira(Lista *l, void * val)
{
  Elo *e = elo_busca(l, val);
  e->previous->next = e->next;
  if(e->next) e->next->previous = e->previous;
}
