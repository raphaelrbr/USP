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
#include "comandos.h"
#include "tabsim.h"
#include <stdio.h>
#include "myString.h"
#include <string.h>
#include <stdlib.h>
#include "acao.h"
TabSim tabela;
Lista * ObjetosAnimados;
char * fimJogo;
int yyparse();

int main(){

    /*Inicializa objetos, adicionando nomes e descricao a partir de
    descricao.txt*/
     FILE * fl;
     long fl_size;
     char * buffer;
     long res;
     char * artigo;
     char * nome;
     char * descCur;
     char * descLong;
     char * tipo;
     char * introducao;
     int tipo_int;

     Elemento * elAtual;

     fl = fopen ( "descricao.txt" , "r+" );



    if (fl==NULL) {

        fprintf (stderr, "Arquivo descricao.txt nao encontrado!\n");
        exit (1);

    }

    fseek (fl , 0 , SEEK_END);
    fl_size = ftell (fl);
    rewind (fl);
    buffer = (char*) malloc (sizeof(char)*fl_size);

    if (buffer == NULL) {

        fputs ("Erro na alocação de memoria",stderr);
        exit (1);

    }

    res = fread (buffer,1,fl_size,fl);

    if (res != fl_size) {
        fputs ("Erro na leitura do arquivo.",stderr);
        exit (1);
    }

    /*Quebra a string por meio do delimitador */
    char * strtok_res = 'a';
    fimJogo = strtok(buffer, "^");
    introducao = strtok(NULL, "^");

    /*Cria uma tabela de simbolos de tamanho 100 */
    tabela = tabsim_cria(100);




    while (strtok_res != NULL){

        artigo = strtok(NULL, "^");
        strtok(NULL, "^");
        nome = strtok(NULL, "^");
        strtok(NULL, "^");
        descCur = strtok(NULL, "^");
        strtok(NULL, "^");
        descLong = strtok(NULL, "^");
        strtok(NULL, "^");
        tipo = strtok(NULL, "^");
        strtok_res = strtok(NULL, "^");


        /*Verifica se o elemento não é nulo */
        if (nome){
        /*Cria o elemento e adiciona na tabela de simbolos */
            if (!strcmp(tipo, "0")) tipo_int = 0;
            else tipo_int = 1;
            elAtual = elemento_cria(artigo, nome,descCur,descLong,tipo_int);
            tabsim_insere(tabela, nome, elAtual);
        }
    }



    //Alguns apontadores
    Elemento * LadoExterno;
    Elemento * Lanterna;
    Elemento * Kit;
    Elemento * Banco;
    Elemento * Mesas;
    Elemento * Cadeiras;
    Elemento * Lousas;
    Elemento * Banheiro;
    Elemento * Detergente;
    Elemento * ProfessorGubi;
    Elemento * Cafe;
    Elemento * Maquina;
    Elemento * Container;
    Elemento * Saguao;
    Elemento * Lanchonete;
    Elemento * SalaAula;
    Elemento * SalaDeFerramentas;
    Lanterna = tabsim_busca(tabela, "lanterna");
    Kit = tabsim_busca(tabela, "Kit de Ferramentas");
    LadoExterno = tabsim_busca(tabela, "IME - Lado Externo");
    Banco = tabsim_busca(tabela, "banco");
    Mesas = tabsim_busca(tabela, "mesas");
    Cadeiras = tabsim_busca(tabela, "cadeiras");
    Lousas = tabsim_busca(tabela, "lousas");
    Banheiro = tabsim_busca(tabela, "banheiro");
    Detergente = tabsim_busca(tabela, "detergente");
    ProfessorGubi = tabsim_busca(tabela, "Professor Gubi");
    Cafe = tabsim_busca(tabela, "Cafe de Ma Qualidade");
    Maquina = tabsim_busca(tabela, "Fantastica Maquina dos Sonhos");
    Container = tabsim_busca(tabela, "container");
    Saguao = tabsim_busca(tabela, "Saguao do IME");
    Lanchonete = tabsim_busca(tabela, "Lanchonete");
    SalaAula = tabsim_busca(tabela, "Sala de Aula");
    SalaDeFerramentas = tabsim_busca(tabela, "Sala de Ferramentas");

    /*Ponteiro para o jogador*/
    player = tabsim_busca(tabela, "jogador");

    /*Inicializa lista de ações gerais */
    acoes_gerais = lista_cria();
    lista_insere(acoes_gerais, criaAcao("olharInventario", &olhar_inventario));
    lista_insere(acoes_gerais, criaAcao("imprimeDescricao", &imprimeDescricao));
    lista_insere(acoes_gerais, criaAcao("imprimeConteudo", &imprimeConteudo));
    lista_insere(acoes_gerais, criaAcao("imprimeNome", &imprimeNome));
    lista_insere(acoes_gerais, criaAcao("pegar", &pegar_geral));
    lista_insere(acoes_gerais, criaAcao("consertar", &consertar_geral));
    lista_insere(acoes_gerais, criaAcao("quebrar", &quebrar_geral));
    lista_insere(acoes_gerais, criaAcao("apagado", &sala_apagar_geral));
    lista_insere(acoes_gerais, criaAcao("andar", &andar));
    lista_insere(acoes_gerais, criaAcao("olhar", &olhar));


    /*Inicializa ações especificas para objetos*/
    lista_insere(Lanterna->acoes, criaAcao("pegar", &pegar_pegavel) );
    lista_insere(Detergente->acoes, criaAcao("pegar", &pegar_pegavel));
    lista_insere(Lanterna->acoes, criaAcao("apagar", &apagar_lanterna));
    lista_insere(Lanterna->acoes, criaAcao("acender", &acender_lanterna));
    lista_insere(Kit->acoes, criaAcao("pegar", &pegar_pegavel));
    lista_insere(Kit->acoes, criaAcao("consertar", &consertar_kit));
    lista_insere(Banco->acoes, criaAcao("quebrar", &quebrar_quebravel));
    lista_insere(Lousas->acoes, criaAcao("quebrar", &quebrar_quebravel));
    lista_insere(Mesas->acoes, criaAcao("quebrar", &quebrar_quebravel));
    lista_insere(Cadeiras->acoes, criaAcao("quebrar", &quebrar_quebravel));
    lista_insere(Banheiro->acoes, criaAcao("apagado", &sala_apagar_escura));
    lista_insere(ProfessorGubi->acoes, criaAcao("anima", &anima_gubi));
    lista_insere(Cafe->acoes, criaAcao("comprar", &comprar_cafe));
    lista_insere(Cafe->acoes, criaAcao("oferecer", &oferecer_cafe));
    lista_insere(Container->acoes, criaAcao("entrar", &entrar_container));
    lista_insere(Detergente->acoes, criaAcao("passar", &passar_detergente));
    lista_insere(Maquina->acoes, criaAcao("mover", &mover_maquina));
    lista_insere(Maquina->acoes, criaAcao("conectar", &conectar_maquina));

    /*Inicializa saídas das salas*/
    char * saidas_LadoExterno[] = {"Saguao do IME", "estacionamento"};
    char * saidas_saguao[] = {"IME - Lado Externo", "Lanchonete", "Sala de Aula", "banheiro", "Sala de Ferramentas"};
    char * saidas_Estacionamento[] = {"IME - Lado Externo"};
    char * saida_padrao[] = {"Saguao do IME"};
    elemento_insere_saidas("IME - Lado Externo", saidas_LadoExterno , 2, tabela);
    elemento_insere_saidas("Saguao do IME", saidas_saguao, 5, tabela);
    elemento_insere_saidas("estacionamento", saidas_Estacionamento, 1, tabela);
    elemento_insere_saidas("Lanchonete", saida_padrao , 1, tabela);
    elemento_insere_saidas("Sala de Aula", saida_padrao , 1, tabela);
    elemento_insere_saidas("banheiro", saida_padrao, 1, tabela);
    elemento_insere_saidas("Sala de Ferramentas", saida_padrao, 1, tabela);

    /*Inicializa conteudo das salas*/
    elemento_insere_conteudo("estacionamento", "container", tabela);
    elemento_insere_conteudo("Lanchonete", "mesas", tabela);
    elemento_insere_conteudo("Lanchonete", "cadeiras", tabela);
    elemento_insere_conteudo("Sala de Ferramentas", "Kit de Ferramentas", tabela);
    elemento_insere_conteudo("Sala de Ferramentas", "lanterna", tabela);
    elemento_insere_conteudo("IME - Lado Externo", "banco", tabela);
    elemento_insere_conteudo("IME - Lado Externo", "lousas", tabela);
    elemento_insere_conteudo("banheiro", "detergente", tabela);
    elemento_insere_conteudo("Sala de Aula", "Professor Gubi", tabela);
    elemento_insere_conteudo("Lanchonete", "Cafe de Ma Qualidade", tabela);
    elemento_insere_conteudo("estacionamento", "Fantastica Maquina dos Sonhos", tabela);

    /*Inicializa dicionario*/
    dd.tam = 0;
    insere_dicionario("andar", "andar");
    insere_dicionario("olhar", "olhar");
    insere_dicionario("quebrar", "quebrar");
    insere_dicionario("pegar", "pegar");
    insere_dicionario("acender", "acender");
    insere_dicionario("apagar", "apagar");
    insere_dicionario("oferecer", "oferecer");
    insere_dicionario("comprar", "comprar");
    insere_dicionario("entrar", "entrar");
    insere_dicionario("dar", "oferecer");
    insere_dicionario("consertar", "consertar");
    insere_dicionario("passar", "passar");
    insere_dicionario("mover", "mover");
    insere_dicionario("conectar", "conectar");


    /*Adiciona sinonimos a tabela de simbolos*/
    tabsim_insere(tabela, "ladoexterno", LadoExterno);
    tabsim_insere(tabela, "fora", LadoExterno);
    tabsim_insere(tabela, "saguao", Saguao);
    tabsim_insere(tabela, "saguaodoime", Saguao);
    tabsim_insere(tabela, "saguaoime", Saguao);
    tabsim_insere(tabela, "lanchonete", Lanchonete);
    tabsim_insere(tabela, "lanchonetedoime", Lanchonete);
    tabsim_insere(tabela, "salaaula", SalaAula);
    tabsim_insere(tabela, "saladeaula", SalaAula);
    tabsim_insere(tabela, "saladeferramentas", SalaDeFerramentas);
    tabsim_insere(tabela, "kitferramenta", Kit);
    tabsim_insere(tabela, "professor", ProfessorGubi);
    tabsim_insere(tabela, "professorgubi", ProfessorGubi);
    tabsim_insere(tabela, "gubi", ProfessorGubi);
    tabsim_insere(tabela, "kit", Kit);
    tabsim_insere(tabela, "café", Cafe);
    tabsim_insere(tabela, "cafe", Cafe);
    tabsim_insere(tabela, "maquina", Maquina);
    tabsim_insere(tabela, "kitferramentas", Kit);
    tabsim_insere(tabela, "kitferramentas", Kit);


    /*Modifica parametros default*/
    Banheiro->visivel = FALSE;
    Maquina->visivel = FALSE;
    Cafe->visivel = FALSE;

    /*Adiciona atributos iniciais*/
    lista_insere(Container->objeto.atributos, criaAtributo("quebrado", CARACTERISTICA));
    lista_insere(Maquina->objeto.atributos, criaAtributo("presa", CARACTERISTICA));

    // /*A sala inicial é a sala ladoexterno*/
    salaAtual = LadoExterno;

    /*Inicializa lista de objetos animados*/
    ObjetosAnimados = lista_cria();
    lista_insere(ObjetosAnimados, ProfessorGubi);


    /*Imprime mensagem de introdução*/
    print_string(introducao);


    while(yyparse()){
        /*Anima objetos que devem ser animados*/
        anima_objetos();
    }

    return 0;
}
