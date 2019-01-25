/*
Técnicas de Programacao 1
Professor: Marcos Dimas Gubitoso
Integrantes do grupo
Paulo Silva - NUSP 8941112
Thiago Pena - NUSP 6847829
Raphael Ribeiro - NUSP 10281601
*/

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "hash.h"
#include "elemento.h"
#include "tabsim.h"
#include <stdio.h>


TabSim tabsim_cria(int tam){
    /*Cria uma tabela de simbolos retornando seu endereço */
    int i;
    TabSim nova = malloc(sizeof(tabsim));
    nova->nomes = malloc(tam*sizeof(char *));
    nova->valores = malloc(tam*sizeof(Elemento *));
    nova->tamanho = tam;
    for (i = 0; i < tam; i++) {
        nova->nomes[i] = NULL;
        nova->valores[i] = NULL;
    }
    return nova;
}

void tabsim_destroi(TabSim t){
    /*Destrói uma tabela de simbolos t*/
    /*Observe que como as strings foram alocadas estaticamente, não é necessário
    iterar para remover uma por uma*/
    free(t->nomes);
    //    for (int i = 0; i<t->tamanho; i++) free(t->valores[i]);
    free(t->valores);
    free(t);
}

int tabsim_insere(TabSim t, char *n, Elemento *val) {
    /*Tenta inserir um elemento val na posicao hash(n) na tabela
    de simbolos t retornando 1 se a inserção ocorreu corretamente
    e 0 caso contrário */
    int i = hash(n,strlen(n));
    /*Verifica se o indice é valido */
    if (i>=4 && i<=59) {
        /*Verifica se a posicao na tabela de simbolos ainda nao foi utilizada */
        if (t->valores[i] == NULL) {
            t->nomes[i] = n;
            t->valores[i] = val;
            return 1;
        }

    }
    return 0;
}

Elemento * tabsim_busca(TabSim t, char * n) {
    /*Busca um elemento na tabela de simbolos t na posicao
    hash(n), retornando o valor desse elemento caso a busca
    seja bem sucedida e NULL caso contrário */
    int i = hash(n,strlen(n));
        /*Verifica se o índice é valido */
    if (i>=4 && i<=59) {
        /*Verifica se o nome buscado é de fato o nome que está
        na tabela de simbolos, retornando o elemento correspondente
        caso verdadeiro */
        if(t->nomes[i]) {
            if (!strcmp(n, t->nomes[i])) return t->valores[i];
        }

        
    }
    return NULL;
}

int tabsim_retira(TabSim t, char * n){
    /*Remove o elemento correspondente a n
     na tabela de símbolos t, retornando 1 se
     foi possível remover o elemento e 0 caso
     contrário */
    int i = hash(n,strlen(n));
     /*Verifica se o índice é valido */
     if (i>=4 && i<=59)
        /*Verifica o nome na tabela */
        if (t->nomes[i] == n) {
            free(t->valores[i]);
            t->valores[i] = NULL;
            return 1;
        }
    return 0;

}
