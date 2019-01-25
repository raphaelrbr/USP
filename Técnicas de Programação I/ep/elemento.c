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
#include "comandos.h"
#include <string.h>
#include "tabsim.h"
#include <stdio.h>



Elemento * elemento_cria(char * artigo, char * nome, char * curta, char * longa, TipoDeElemento tipo){

    Elemento * novoElemento = malloc(sizeof(Elemento));

    strcpy(novoElemento->n, nome);
    novoElemento->artigo = artigo;
    novoElemento->curta = curta;
    novoElemento->longa = longa;
    novoElemento->ativo = TRUE;
    novoElemento->visivel = TRUE;
    novoElemento->conhecido = FALSE;
    novoElemento->conteudo = lista_cria();
    novoElemento->acoes = lista_cria();
    novoElemento->tipoDeElemento = tipo;
    // Se é um lugar, é necessário alocar a lista saidas.
    // Caso contrário, aloca a lista de atributos do objeto
    if (!tipo) {
        novoElemento->lugar.saidas = lista_cria();

    }
    else {
        novoElemento->objeto.atributos = lista_cria();
    }

    return novoElemento;
}

void elemento_insere_conteudo(char * elemento, char * conteudo, TabSim tab) {
    Elemento * s = tabsim_busca(tab, elemento);
    Elemento * h = tabsim_busca(tab, conteudo);

    lista_insere(s->conteudo, h);
}

void elemento_insere_saidas(char * sala, char ** saidas, int n, TabSim tab){
    Elemento * s = tabsim_busca(tab, sala);

    for (int i = 0; i < n; i++) {
        lista_insere(s->lugar.saidas, tabsim_busca(tab, saidas[i]));
    }
}

/*Insere um objeto na lista de conteudo do elemento jogador,
isto é equivalente a adicionar um item no inventário*/
void insere_inventario(Elemento * obj){
    lista_insere(player->conteudo, obj);
}

Atributo * criaAtributo(char * nome, TipoDeAtributo tipo){
    Atributo * novoAtributo = malloc(sizeof(Atributo));
    strcpy(novoAtributo->n, nome);
    novoAtributo->tipoDeAtributo = tipo;
    return novoAtributo; 
}



/*Variavel global que armazena a sala atual*/
Elemento * salaAtual;
Elemento * player;

/*Lista global de objetos animados */
extern Lista * objetosAnimados;
    

