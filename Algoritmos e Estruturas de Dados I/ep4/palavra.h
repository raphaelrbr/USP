#ifndef __PALAVRA_H__
#define __PALAVRA_H__

/*Estrutura de uma palavra*/
typedef struct palavra{
	char * p;
	int ocr;
} palavra;

typedef palavra * Palavra;

/*Função para criar uma palavra a partir
de uma string*/
Palavra criaPalavra(char * palavra);

#endif