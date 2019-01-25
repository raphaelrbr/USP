/*
Técnicas de Programacao 1
Professor: Marcos Dimas Gubitoso
Integrantes do grupo
Paulo Silva - NUSP 8941112
Thiago Pena - NUSP 6847829
Raphael Ribeiro - NUSP 10281601
*/



#ifndef __ACAO_H__
#define __ACAO_H__

/*Estrutura dicionario*/
typedef struct dicionario{
	char * palavras[100];
	char * significados[100];
	int tam;
} dicionario;

/*dicionario global*/
extern dicionario dd;

/*Procura por uma acao no dicionario, executando a funcao
correspondente ao significado dessa acao*/
void buscaAcao_dicionario(char * n, Elemento * obj1, Elemento * obj2);

/*Insere uma palavra e seu significado no dicionario*/
void insere_dicionario(char * p, char * s);

/*Declaração de ponteiro para função */
typedef int (*FunPtr) (Elemento*, Elemento*);

/*Declaração da estrutura ação */
typedef struct {
  char n[50];
  FunPtr fun;
} Acao;

/*Lista ligada global com acoes gerais */
extern Lista * acoes_gerais;

/*Insere uma ação na lista ligada global acoes gerais */
void acoes_gerais_insere(Acao * ac);

/* Busca por uma ação com o nome n seguindo a ordem de prioridade,
e a executa. A ordem de prioridade é:
1) Busca na sala atual pela acao
2) Busca na lista de acoes especificas do objeto
3) Busca na lista geral de acoes 
*/
int executaAcao (char * n, Elemento * obj1, Elemento * obj2);

/*Insere uma ação na lista de ações de um elemento */
void elemento_insere_acao(Elemento * el, Acao * acao);

/*Cria uma ação com nome N e a associa com funcao */
Acao * criaAcao(char * n, FunPtr funcao);

#endif