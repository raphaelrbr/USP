%{
#include "tabsim.h"
#include "string.h"
#include "avent.tab.h"
#include "elemento.h"
#include "ctype.h"

/* Para readline */
#include <readline/readline.h>
#include <readline/history.h>

/* Redefinição da entrada do Flex para usar o readline */
#define YY_INPUT(buf,result,max_size) result = mygetinput(buf, max_size);

/* Função que substitui a entrada */
static int mygetinput(char *buf, int size) {
  char *line;
  /* final de arquivo */
  if (feof(yyin))  return YY_NULL;

  /* Lê uma linha, com o prompt "> " */
  line = readline("\n> ");
  if(!line)        return YY_NULL;

  /* segurança */
  if((int)strlen(line) > size-2){
     fprintf(stderr,"input line too long\n");
	 return YY_NULL;
  }

  /* copia para o buffer de enrtada */
  sprintf(buf,"%s\n",line);
  /* adiciona ao histórico */
  add_history(line);

  /* libera memória */
  free(line);
  return strlen(buf);
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



/* Não importa se maiúsculas ou minúsculas */
%option caseless

%%


(ajuda) {return AJUDA;}
(fim|Chega) { return FIM; }

com

consertar[ ]+container[ ]+com[ ]+o?[ ]*kit(a-z)* {
  return CONSERTAR;
}

mover[ ]+maquina[ ]+(para|pra)[ ]+sala[ ]+de[ ]+aula {
  return MOVER;
}

[ao]|uma?s?

algumas? 

d[aoe]|em|n[ao]

ao 

<<EOF>> { puts("Adeus..."); return FIM; }

i(nvent((a|á|Á)rio)?)? {return INVENT; }

(v(a|á|Á)|ir|andar|sair)[ ]+para([ a-z]+) {
  yylval.str = yytext;
	return VAPARA; }

para

(olhar|examinar|investigar)[ ]*(ao)[ ]*(redor) {return OLHAR;}

[a-z]+ {
		/* identificador */
		Elemento * s;
    lower_string(yytext);
    
		if ((s = (tabsim_busca(tabela, yytext)))) {
			yylval.el = s;
			return OBJ;
		}
		else {
      char * s = malloc(100*sizeof(char));
      strcpy(s, yytext);
      yylval.str = s;
			return VERBO;
		}
		}

[ \t]+
[\n;] {return EOL;}

. {yylval.str = yytext; return DESC;}
