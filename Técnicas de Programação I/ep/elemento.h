/*
Técnicas de Programacao 1
Professor: Marcos Dimas Gubitoso
Integrantes do grupo
Paulo Silva - NUSP 8941112
Thiago Pena - NUSP 6847829
Raphael Ribeiro - NUSP 10281601
*/


#ifndef __ELEMENTO_H__
#define __ELEMENTO_H__
#include "lista.h"



typedef enum {
  FALSE, TRUE
} Bool;

typedef enum {
  LUGAR, OBJETO
} TipoDeElemento;

typedef enum {
  CARACTERISTICA, QUANTIDADE
} TipoDeAtributo;

typedef struct {
  char n[80];
  TipoDeAtributo tipoDeAtributo;
  union {
    char caracteristica[50];
    int quantidade;
  };
} Atributo;

typedef struct {
  Lista* atributos;
} Objeto;

typedef struct {
  Lista* saidas;
} Lugar;

typedef struct {
  char n[80];
  char * curta;
  char * longa;
  char * artigo;
  Bool ativo;
  Bool visivel;
  Bool conhecido;
  Lista* conteudo;
  Lista* acoes;
  TipoDeElemento tipoDeElemento;
  union {
    Objeto objeto;
    Lugar lugar;
  };
} Elemento;


/*Inicializa um elemento mas nao insere nada no conteudo e nas acoes, apenas
inicializa uma lista vazia nesses campos. Campos booleanos são inicializados
com false */
Elemento * elemento_cria(char * artigo, char * nome, char * curta, char * longa, TipoDeElemento tipo);



/*Variável global que armazena a sala atual */
extern Elemento * salaAtual;

/*Variavel global que armazena o ponteiro para o jogador*/
extern Elemento * player;

#include "tabsim.h"
/*Insere saidas em uma sala a partir de um vetor com o nome das saidas de 
tamanho n, buscando na tabela de simbolos tab */
void elemento_insere_saidas(char * sala,char ** saidas, int n, TabSim tab);

/*Insere conteudo em um elemento a partir dos seus respectivos nomes,
pesquisando na tabela de simbolos tab */
void elemento_insere_conteudo(char * elemento, char * conteudo, TabSim tab);

/*Insere um objeto na lista de conteudo do elemento jogador,
isto é equivalente a adicionar um item no inventário*/
void insere_inventario(Elemento * obj);

/*Cria um atributo de nome e tipo para ser inserido em um objeto*/
Atributo * criaAtributo(char * nome, TipoDeAtributo tipo);

extern Lista * ObjetosAnimados;


#endif
