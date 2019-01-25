/*
Técnicas de Programacao 1
Professor: Marcos Dimas Gubitoso
Integrantes do grupo
Paulo Silva - NUSP 8941112
Thiago Pena - NUSP 6847829
Raphael Ribeiro - NUSP 10281601
*/


#include <stdio.h>
#include "myString.h"

void print_string(const char* texto)
{
  int i;
  for(i = 0; texto[i] != '\0'; i++)
    printf("%c", texto[i]);
}
