/*
Técnicas de Programacao 1
Professor: Marcos Dimas Gubitoso
Integrantes do grupo
Paulo Silva - NUSP 8941112
Thiago Pena - NUSP 6847829
Raphael Ribeiro - NUSP 10281601
*/
#include "elemento.h"

#ifndef __TABSIM_H__
#define __TABSIM_H__


typedef struct tabsim{
    char ** nomes;
    Elemento ** valores;
    int tamanho;
} tabsim;

typedef tabsim * TabSim;


/*Cria uma tabela de símbolos */
TabSim tabsim_cria(int tam);

/*Destrói uma tabela de simbolos t*/
void tabsim_destroi(TabSim t);

/*Tenta inserir um elemento val na posicao hash(n) na tabela
    de simbolos t retornando 1 se a inserção ocorreu corretamente
    e 0 caso contrário */
int tabsim_insere(TabSim t, char *n, Elemento *val);

/*Busca um elemento na tabela de hash, retornando esse elemento
caso encontrado e NULL se não encontrado */
Elemento * tabsim_busca(TabSim t, char * n);

/*Remove o elemento correspondente a n 
na tabela de símbolos t, retornando 1 se
foi possível remover o elemento e 0 caso
contrário */
int tabsim_retira(TabSim t, char * n);

extern TabSim tabela;
#endif
