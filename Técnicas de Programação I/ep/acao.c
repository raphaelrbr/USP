/*
Técnicas de Programacao 1
Professor: Marcos Dimas Gubitoso
Integrantes do grupo
Paulo Silva - NUSP 8941112
Thiago Pena - NUSP 6847829
Raphael Ribeiro - NUSP 10281601
*/



#include "elemento.h"
#include <string.h>
#include <stdlib.h>
#include "comandos.h"
#include "acao.h"
#include "lista.h"
#include <stdio.h>

Lista * acoes_gerais;
dicionario dd;


void acoes_gerais_insere(Acao * ac){
	lista_insere(acoes_gerais, ac);
}

void buscaAcao_dicionario(char * n, Elemento * obj1, Elemento * obj2){
	for (int i = 0; i<dd.tam; i++) {
		if (!strcmp(n,dd.palavras[i])) {
			executaAcao(dd.significados[i], obj1, obj2); 
			return;
		}
	}
	printf("Não sei o que é isso\n");
}

void insere_dicionario(char * p, char * s){
	char * novaPalavra = malloc(100*sizeof(char));
	char * novoSignificado = malloc(100*sizeof(char));
	strcpy(novaPalavra, p);
	strcpy(novoSignificado, s);
	dd.palavras[dd.tam] = novaPalavra;
	dd.significados[dd.tam] = novoSignificado; 
	dd.tam++;
}

int executaAcao (char * n, Elemento * obj1, Elemento * obj2){
	Acao * ac = lista_busca(salaAtual->acoes, n);
	if (ac == NULL) {
		if(obj1 != NULL) {
			ac = lista_busca(obj1->acoes, n);
		}
		if (ac == NULL) {

			ac = lista_busca(acoes_gerais, n);
		}
	}
	if (ac != NULL){
		(*ac->fun)(obj1, obj2);
		return 1;
	}
	return 0;
}

void elemento_insere_acao(Elemento * el, Acao * acao){
    lista_insere(el->acoes, acao);
}

Acao * criaAcao(char * n, FunPtr funcao){
  Acao * ac = malloc(sizeof(Acao));
  strcpy(ac->n, n);
  ac->fun = funcao;
  return ac;
}