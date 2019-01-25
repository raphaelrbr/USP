/*
Técnicas de Programacao 1
Professor: Marcos Dimas Gubitoso
Integrantes do grupo
Paulo Silva - NUSP 8941112
Thiago Pena - NUSP 6847829
Raphael Ribeiro - NUSP 10281601
*/



#ifndef __COMANDOS_H__
#define __COMANDOS_H__

#include "elemento.h"

/*Ponteiro para string de fim de jogo*/
extern char * fimJogo;

/*Verbos */
int correr(Elemento* lugar, Elemento* null);

int pular(Elemento* coisa, Elemento* null);

int andar(Elemento * sala, Elemento* null);

int pegar(Elemento * objeto, Elemento * null);

int chorar(Elemento * null, Elemento * null2);

int olhar(Elemento * elem, Elemento * null);

int consertar(Elemento * objeto, Elemento * ferramenta);

int quebrar(Elemento * objeto, Elemento * ferramenta);

int acender(Elemento * ferramenta, Elemento * null);

int apagar(Elemento * ferramenta, Elemento * null);

int colocar(Elemento * obj, Elemento * null);

/*Comandos gerais */

/*Comando específico de pegar para objetos que 
podem ser pegos */
int pegar_pegavel( Elemento * obj, Elemento * null);

/*Comandos geral de pegar. Serve para todos os 
objetos que nao podem ser pegos*/
int pegar_geral(Elemento * obj1, Elemento * null);

/*Comando especifico de quebrar para objetos quebraveis */
int quebrar_quebravel(Elemento * obj, Elemento * null);

/*Comando de quebrar para objetos em geral */
int quebrar_geral(Elemento * objeto, Elemento * null);

/*Comando de consertar sem ferramenta */
int consertar_geral(Elemento * objeto, Elemento * null);

/*Comando específico de consertar para kit de ferramentas */
int consertar_kit(Elemento * null, Elemento * obj);

/*Comando especifico de acender para lanterna */
int acender_lanterna(Elemento * lanterna, Elemento * null);

/*Comando especifico de apagar para lanterna */
int apagar_lanterna(Elemento * lanterna, Elemento * null);

/*Comportamento caso uma sala escura tenha a iluminação encerrada */
int sala_apagar_escura(Elemento * null, Elemento * null1);

/*Comportamento geral para uma sala ter uma iluminação externa encerrada */
int sala_apagar_geral(Elemento * sala, Elemento * null);

/*Comando especifica do container*/
int entrar_container(Elemento * container, Elemento * null2);

/*Comando especifico do objeto cafe*/
int comprar_cafe(Elemento * cafe, Elemento * null2);

/*Comando especifico do objeto cafe*/
int oferecer_cafe(Elemento * cafe, Elemento * professor);

/*Comando especifico do objeto detergente*/
int passar_detergente(Elemento * detergente, Elemento * maquina);

/*Comando especifico do objeto maquina*/
int mover_maquina(Elemento * maquina, Elemento * destino);

/*Comando especifico do objeto maquina*/
int conectar_maquina(Elemento * maq, Elemento * professor);

/*Comando especifico de animacao do professor gubi*/
int anima_gubi(Elemento * null1, Elemento * null2);

/*funcao auxiliar para chamar a funcao especifica de animar em cada objeto na lista global ObjetosAnimados*/
void anima_objetos();

/*Imprime a descricao longa da sala ou a curta, dependendo
se a sala ja foi visitada ou nao */
int imprimeDescricao(Elemento * sala, Elemento * null);

/*Imprime o conteudo da sala*/
int imprimeConteudo (Elemento * elem, Elemento * null);

/*Imprime o nome de um objeto precedido por seu artigo*/
int imprimeNome (Elemento * obj1, Elemento * null);

/*Imprime todos os atributos de um objeto */
int imprimeAtributos(Elemento * obj, Elemento * null);

/*Olha para o inventario*/
int olhar_inventario(Elemento * null, Elemento * null1);


#endif
