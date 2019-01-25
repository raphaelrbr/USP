LOADLIBES = -lfl -lreadline
CFLAGS=-Wextra -Wall -std=c99 -g 

.PHONY: clean

%.c: %.y
	bison $<
	mv $*.tab.c $*.c

avent: main.o avent.o aventl.o lista.o hash.o tabsim.o elemento.o acao.o aventl.o avent.o comandos.o myString.o 

avent.c : avent.y

aventl.o: aventl.l avent.c

clean: 
	rm -rf avent  *.o *~ avent.c \.\#* main
	rm -f avent.tab.h	
