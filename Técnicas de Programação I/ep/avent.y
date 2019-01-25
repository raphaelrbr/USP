%{
#include <stdio.h>
#include "tabsim.h"
#include "elemento.h"
#include "comandos.h"
#include "acao.h"
#include <readline/readline.h>
#include <readline/history.h>


int yylex();
int yyerror(char *);

static void removeSpaces(char *str) 
{ 
    int count = 0; 

    for (int i = 0; str[i]; i++) 
        if (str[i] != ' ') 
            str[count++] = str[i]; 
                                   
    str[count] = '\0'; 
} 

static void rmSubstr(char *str, const char *toRemove)
{
    size_t length = strlen(toRemove);
    while((str = strstr(str, toRemove)))
    {
        memmove(str, str + length, 1 + strlen(str + length));
    }
}

static void lower_string(char s[]) {
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
} 

%}

/*Declaracoes */
%union{
	Elemento * el;
	char * str;
}

/*Nesta implementacao, verbos sao chamados pelo seu nome*/
%token <str> VERBO

/*Algo desconhecido*/
%token <str> DESC VAPARA

/*OBJ é um ponteiro para um Elemento*/
%token <el> OBJ

/*Mais alguns tokens*/
%token EOL FIM INVENT OLHAR MOVER CONSERTAR AJUDA


%defines

%%
/*Gramatica */

input: EOL { printf("O tempo aguarda sua preciosa vontade de agir...\n");}
	| cmd
	| CONSERTAR {
			executaAcao("consertar", tabsim_busca(tabela,"Kit de Ferramentas"), tabsim_busca(tabela,"container"));
	} eol
	| AJUDA {
			printf(" Para visualizar objetos em um local digite olhar/examinar/investigar ao redor\n Para ir para um lugar, digite ir para DESTINO\n Para ver o inventário, digite i ou inventario\n Para sair do jogo digite fim\n");
	} eol;
	| OLHAR {
			executaAcao("olhar", salaAtual, NULL);
	} eol
	| MOVER {
			executaAcao("mover", tabsim_busca(tabela,"Fantastica Maquina dos Sonhos"), tabsim_busca(tabela,"Sala de Aula"));
	} eol
	| VAPARA {
				/*Movimentação*/
				lower_string($1);
				removeSpaces($1);
				rmSubstr($1,"vapara");
				rmSubstr($1,"sairpara");
				rmSubstr($1,"irpara");
				rmSubstr($1,"andarpara");
				Elemento * s = tabsim_busca(tabela,$1);
				if (s == NULL) printf("Não sei onde é isso\n");
				else buscaAcao_dicionario("andar", tabsim_busca(tabela,$1), NULL);
				} eol
	| INVENT {
				/*listagem do inventario */
				olhar_inventario(NULL, NULL);
				} eol
	| FIM {return 0;}
	| DESC { puts("Desconhecido\n");}
	| error eol;
;

cmd: VERBO {
			/*Intransitivo*/
			buscaAcao_dicionario($1, NULL, NULL);
			} eol
	| VERBO OBJ {
			/* Transitivo direto */
			buscaAcao_dicionario($1, $2, NULL);
			} eol
	| VERBO OBJ OBJ {
			/* Bitransitivo */
			buscaAcao_dicionario($1, $2, $3);
			} eol

;


eol: EOL {
return 1;}

%%

int yyerror(char *s){
	if(s)
	puts("Não entendi...");
	return 0;
}
