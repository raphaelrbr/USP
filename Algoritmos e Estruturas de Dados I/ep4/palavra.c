#include "palavra.h"
#include "stdlib.h"

Palavra criaPalavra(char * pp){
	Palavra novaPalavra = malloc(sizeof(palavra));
	novaPalavra->p = pp; 
	novaPalavra->ocr = 1;
	return novaPalavra;
}