/*
Técnicas de Programacao 1
Professor: Marcos Dimas Gubitoso
Integrantes do grupo
Paulo Silva - NUSP 8941112
Thiago Pena - NUSP 6847829
Raphael Ribeiro - NUSP 10281601
*/


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "lista.h"
#include "tabsim.h"
#include "comandos.h"
#include "myString.h"
#include "comandos.h"
#define MAXLEN 100

Elemento * salaAtual;

int main()
{
  Lista *l, *l2;
  Elemento *mento, *mento1, *bus, *val, *sala, *corda;
  TabSim t;
  Objeto obj;
  Atributo atr1, *atr2;
  Acao *acao1, *acao2;

  // TESTE PARA IMPRIMIR STRING
  print_string("aehooo\n");

  // TESTE PARA INSERIR
  l = lista_cria();
  mento = malloc (sizeof (Elemento));
  strcpy(mento->n, "ad");
  lista_insere(l, mento);
  mento1 = malloc (sizeof (Elemento));
  strcpy(mento1->n,"ncmdkoeofjw");
  lista_insere(l, mento1);
  printf("%c\n", ((Elemento*)(l->cabec->next->val))->n[8]);
  printf("%c\n", ((Elemento*)(l->cabec->next->next->val))->n[1]);

  // TESTE PARA DESTROI
  l2 = lista_cria();
  if(!l2)
    puts("é null 0");
  if(!l2->cabec)
    puts("é null 1");
  lista_insere(l2, mento1);
  lista_destroi(l2);
  if(!l2->cabec->next)
    puts("é null 2");
  if(!l2->cabec)
    puts("é null 3");
  if(!l2)
    puts("é null 4");

  // TESTE PARA BUSCA
  bus = lista_busca(l, "ad");
  printf("do busca: %c\n", bus->n[1]);

  // TESTE PARA RETIRA
  val = l->cabec->next->val;
  if(l->cabec->next->val == val) puts("Tá aqui");
  val = lista_retira(l, val);
  if(l->cabec->next->val != val) puts("Removeu");

  // TESTE PARA TABELA DE SÍMBOLOS //
  printf("---Iniciando teste para tabela de símbolos---\n");

  // TESTE PARA INSERE
  t = tabsim_cria(50);
  printf("---Teste para função insere---\n");

  //Insere alguns elementos na tabela de simbolos
  if (tabsim_insere(t, "dinossauro", mento)) printf("Nome dinossauro inserido com sucesso\n");
  else printf("Erro ao inserir\n");
  if (tabsim_insere(t, "floresta", mento)) printf("Nome floresta inserido com sucesso\n");
  else printf("Erro ao inserir\n");
  if (tabsim_insere(t, "mago", mento1)) printf("Nome mago inserido com sucesso\n");
  else printf("Erro ao inserir\n");
  if (tabsim_insere(t, "borboleta", mento1)) printf("Nome borboleta inserido com sucesso\n");
  else printf("Erro ao inserir\n");

  //TESTE PARA BUSCA
  printf("---Teste para função busca---\n");
  if (tabsim_busca(t, "dinossauro") == mento) printf("Nome dinossauro localizado\n");
  if (tabsim_busca(t, "floresta") == mento) printf("Nome floresta localizado\n");
  if (tabsim_busca(t, "mago") == mento1) printf("Nome mago localizado\n");
  if (tabsim_busca(t, "borboleta") == mento1) printf("Nome borboleta localizado\n");

  //Teste de busca para um elemento fora da tabela
  if (tabsim_busca(t, "leopardo") == NULL) printf("Nome leopardo não está na tabela\n");

  //TESTE PARA RETIRA
  printf("---Teste para função retira---\n");
  if (tabsim_retira(t, "dinossauro")) printf("Nome dinossauro foi removido da tabela\n");
  if (tabsim_busca(t, "dinossauro") == NULL) printf("Nome dinossauro não está mais na tabela\n");

  //TESTE PARA DESTROI
  printf("---Teste para função destroi\n");
  tabsim_destroi(t);


  //TESTE DE TIPOS E STRUCT
  printf("--Testes para tipos e structs--\n");
  obj.atributos = lista_cria();
  atr1.tipoDeAtributo = QUANTIDADE;
  strcpy(atr1.n, "energia");
  atr1.quantidade = 42;
  lista_insere(obj.atributos, &atr1);
  atr2 = lista_busca(obj.atributos, "energia");
  printf("Achei a energia. Vale %d!\n", atr2->quantidade);

  //TESTE PARA COMANDO
  sala = malloc(sizeof(Elemento));
  strcpy(sala->n, "Sala Branca");
  sala->tipoDeElemento = LUGAR;
  correr(sala, NULL);

  //TESTE LISTA DE ACAO
  corda = malloc(sizeof(Elemento));
  strcpy(corda->n, "corda grande");
  corda->acoes = lista_cria();
  acao1 = malloc(sizeof(Acao));
  strcpy(acao1->n, "pular");
  acao1->fun = pular;
  lista_insere(corda->acoes, acao1);
  acao2 = lista_busca(corda->acoes, "pular");
  acao2->fun(corda, NULL);

  printf("Fim dos testes\n");
  return 0;
}
