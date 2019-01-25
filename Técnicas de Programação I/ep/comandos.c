/*
Técnicas de Programacao 1
Professor: Marcos Dimas Gubitoso
Integrantes do grupo
Paulo Silva - NUSP 8941112
Thiago Pena - NUSP 6847829
Raphael Ribeiro - NUSP 10281601
*/




#include <stdio.h>
#include "lista.h"
#include <stddef.h>
#include "comandos.h"
#include "myString.h"
#include "elemento.h"
#include <string.h>
#include <stdlib.h>
#include "acao.h"
#include "tabsim.h"


/*COMANDOS DE VERBO*/


int andar(Elemento * sala, Elemento* null){
  null += 0;
  if (sala == NULL) return 0;
  /* "Se é possivel mover para a sala requisitada" */
  if (lista_busca(salaAtual->lugar.saidas, sala->n) != NULL) {
    /*move para a sala e imprime descricao */
    salaAtual = sala;
    printf("Você move para %s\n", sala->n);
    /*Executa a ação de imprimir descricao seguindo a ordem de prioridade
    sala -> objeto -> acoes gerais */
    executaAcao("imprimeDescricao", sala, NULL);
   }
  else {
      printf("\nNão há nenhuma saída para ");
      print_string(sala->n);
      printf("\n");
  }

  return 1;
}

int pegar(Elemento * objeto, Elemento * null){
  null += 0;
  printf("verificando se a sala %s possui %s\n", salaAtual->n, objeto->n);
  /* se o objeto está visivel e a sala possui esse objeto*.
  salaAtual é variavel global */
  if (lista_busca(salaAtual->conteudo, objeto->n) != NULL && objeto->visivel) { 
    /*chama a funcao pegar seguindo a ordem de prioridade
    sala -> objeto -> acoes gerais */
    executaAcao("pegar", objeto, NULL);
   }
  /*Se não é possível ver o objeto ou ele não está na sala.
   * Observe que a funcao pegar do objeto ainda pode ter
   * um comportamento único, como verificar se o objeto
   * pode ser pego */
  else{
    printf("Não vejo nenhum ");
    print_string(objeto->n);
    printf("\n");
  }

  return 0; 
}

int chorar(Elemento * null, Elemento * null2){
  null += 0;
  null2 += 0;
  printf("\nbuááááá, buáááá, buáááaá, buáááá\n");
  return 0;
}

int olhar(Elemento * elem, Elemento * null){
  if(elem == NULL) return 0;
  null += 0;
  /*Se o objeto a ser olhado é a sala atual ou é um objeto dentro da sala atual */
  if (elem->n == salaAtual->n || 
      (lista_busca(salaAtual->conteudo, elem->n) != NULL && elem->visivel)){
    /*Executa a ação de imprimir descricao seguindo a ordem de prioridade
    sala -> objeto -> acoes gerais */
    executaAcao("imprimeDescricao", elem, NULL);
    executaAcao("imprimeConteudo", elem, NULL);

    return 1;

  }

  /*Se nao é possivel ver o elem ou ele não está na sala */
  else {
      printf("Não vejo nenhum ");
      print_string(elem->n);
      printf("\n");
      return 0; 
  }
}

int consertar(Elemento * objeto, Elemento * ferramenta){
  if(lista_busca(salaAtual->conteudo, objeto->n) != NULL && objeto->visivel){
    if(lista_busca(ferramenta->acoes, "consertar") != NULL){
      executaAcao("consertar", ferramenta, objeto);
      return 1;
    }
    else {
      printf("Não consigo consertar %s com %s\n", objeto->n, ferramenta->n);
      return 0;
    }
  }
  else {
    printf("Não vejo nenhum ");
    print_string(objeto->n);
    printf("\n");
    return 0;
  }
}

int quebrar(Elemento * objeto, Elemento * ferramenta){
  /*Se ferramenta é null, então supoe-se que o jogador
  está tentando quebrar objeto com as proprias mãos*/
  if (lista_busca(salaAtual->conteudo, objeto->n) != NULL && objeto->visivel) {
    if (ferramenta == NULL) {
      executaAcao("quebrar", objeto, NULL);
    }
    else executaAcao("quebrar", ferramenta, objeto);
    return 1;
  }
  else {
    printf("Não vejo nenhum ");
    print_string(objeto->n);
    printf("\n");
    return 0;
  }
}

int acender(Elemento * ferramenta, Elemento * null) {
  null += 0;
  if (ferramenta==NULL) return 0;
  if (lista_busca(player->conteudo, ferramenta->n ) == NULL){
    printf("Você não está segurando nenhuma %s\n", ferramenta->n);
    return 0;
  }
  executaAcao("acender", ferramenta, NULL);
  return 1;
}

int apagar(Elemento * ferramenta, Elemento * null){
  null += 0;
  if (ferramenta==NULL) return 0;
  if (lista_busca(player->conteudo, ferramenta->n ) == NULL){
    printf("Você não está segurando nenhuma %s\n", ferramenta->n);
    return 0;
  }
  executaAcao("apagar", ferramenta, NULL);
  return 1;

}

int colocar(Elemento * obj, Elemento * null){
  null += 0;
  if (obj == NULL) return 0;
  if (lista_busca(player->conteudo, obj->n ) == NULL){
    printf("Você não está segurando nenhuma %s\n", obj->n);
    return 0;
  }
  printf("Você coloca %s no chão.\n", obj->n);
  lista_insere(salaAtual->conteudo, obj);
  lista_retira(player->conteudo, obj);
  return 1;

}

/*COMANDOS ESPECÍFICOS GERAIS */

int olhar_inventario(Elemento * null, Elemento * null1){
  null += 0;
  null1 += 0;
  Elo * ap = player->conteudo->cabec->next;
  if (ap != NULL)
  printf("Você está carregando\n");
  else
    printf("Você não tem nada\n");
  while (ap != NULL){
    /*Imprime o nome do objeto, precedido de seu artigo indefinido*/
    Elemento * el = (Elemento *) ap->val;
    printf("\t ");
    if(el->visivel){
    imprimeNome(el, NULL);

    imprimeAtributos(el, NULL);
    printf("\n");
    }
    ap = ap->next;
  }
  return 1;
}

int quebrar_quebravel(Elemento * obj, Elemento * null){
  null += 0;
  Atributo * quebrado = criaAtributo("quebrado", CARACTERISTICA);
  lista_insere(obj->objeto.atributos, quebrado);
  printf("Você destrói %s\n", obj->n);
  return 1;
}

int quebrar_geral(Elemento * objeto, Elemento * null){
  null += 0;
  printf("Não consigo quebrar %s\n", objeto->n);
  return 1;
}

int consertar_geral(Elemento * objeto, Elemento * null){
  null += 0;
  printf("Não consigo consertar %s\n", objeto->n);
  return 1;
}

int consertar_kit(Elemento * null, Elemento * obj){
  if(obj == NULL) {
    printf("Consertar o que?\n");
    return 0;
  }
  if(lista_busca(player->conteudo, "Kit de Ferramentas") == NULL){
    printf("Você não tem nenhum Kit de Ferramentas");
    return 0;
  }
  if(lista_busca(salaAtual->conteudo, obj->n) == NULL || obj->visivel == FALSE){
    if(obj)
    printf("Não vejo nenhum %s\n", obj->n);
    return 0;
  }
  null += 0;
  Elemento * el = lista_busca(obj->objeto.atributos, "quebrado");
  if (el == NULL) {
    printf("%s não está quebrado\n", obj->n);
    return 0;
  }
  printf("Você conserta %s\n", obj->n);
  lista_retira(obj->objeto.atributos, el);
  return 1;
}

int pegar_pegavel( Elemento * obj, Elemento * null) {
  null += 0;
  if(lista_busca(salaAtual->conteudo, obj->n) == NULL){
    printf("Não há nenh%s %s aqui\n", obj->artigo, obj->n);
    return 0;
  }
  if(salaAtual->visivel == FALSE || obj->visivel == FALSE){
    printf("Não vejo nenhum %s\n", obj->n);
    return 0;
  }
  printf("Você pega ");
  imprimeNome(obj, NULL);
  insere_inventario(obj);
  lista_retira(salaAtual->conteudo, obj);
  printf("\n");
  return 1;
}

int pegar_geral(Elemento * obj1, Elemento * null) {
  obj1 += 0;
  null += 0;
  printf("Não consigo pegar isso\n");
  return 1;
}

int acender_lanterna(Elemento * lanterna, Elemento * null){
  lanterna += 0;
  null += 0;
  printf("Você acende a lanterna!\n");
  salaAtual->visivel = TRUE;
  return 1;
}

int mover_maquina(Elemento * maquina, Elemento * destino){
  if(strcmp(salaAtual->n,"estacionamento")!= 0 || maquina->visivel != TRUE){
    printf("Que maquina?\n");
    return 0;
  }
  if (destino == NULL) {
    printf("Para onde você quer mover a maquina?\n");
    return 0;
  }
  if(lista_busca(maquina->objeto.atributos, "presa") != NULL){
    printf("A máquina está presa, não quer sair!\n");
    return 0;
  }
  printf("Você move a Fantástica Máquina dos Sonhos para %s\n", destino->n);
  lista_retira(salaAtual->conteudo, maquina);
  lista_insere(destino->conteudo, maquina);
  return 1;
  
}

int passar_detergente(Elemento * detergente, Elemento * maquina){
  detergente += 0;
  if(lista_busca(player->conteudo, "detergente") == NULL){
    printf("Você não tem nenhum detergente\n");
    return 0;
  }
  if(maquina == NULL){
    printf("Onde você quer passar isso?\n");
    return 0;
  }
  if(strcmp(maquina->n, "Fantastica Maquina dos Sonhos") != 0){
    printf("Tem certeza que é nisso que você passar o detergente?\n");
    return 0;
  }
  if(lista_busca(salaAtual->conteudo,"Fantastica Maquina dos Sonhos") == NULL || maquina->visivel == FALSE){
    printf("Não vejo a Fantastica Maquina dos Sonhos \n");
    return 0;
  }
  printf("Você passa o detergente na Fantastica Maquina dos Sonhos\n");
  Elemento * el = lista_busca(maquina->objeto.atributos, "presa");
  lista_retira(maquina->objeto.atributos, el);
  return 1;
}

int conectar_maquina(Elemento * maq, Elemento * professor){
  maq += 0;
  if(lista_busca(salaAtual->conteudo,"Fantastica Maquina dos Sonhos") == NULL){
    printf("Que máquina?\n");
    return 0;
  }
  if(professor == NULL){
    printf("Em quem você quer conectar a maquina?\n");
    return 0;
  }
  if(strcmp(professor->n, "Professor Gubi") != 0){
    printf("Nao da pra conectar a maquina nisso!\n");
    return 0;
  }
  if(strcmp(salaAtual->n, "Sala de Aula") != 0 ){
    printf("O professor Gubi não está aqui\n");
    return 0;
  }
  if(lista_busca(professor->objeto.atributos, "dormindo") == NULL){
    printf("professor = %s\n", professor->n);
    printf("atributos\n");
    imprimeAtributos(professor, NULL);
    printf("O professor Gubi não está dormindo!\n");
    return 0;
  }
    print_string(fimJogo);
    printf("\n");

  exit(0);

  return 1;

}



int apagar_lanterna(Elemento * lanterna, Elemento * null){
  lanterna += 0;
  null +=0;
  printf("Você apaga a lanterna!\n");
  executaAcao("apagado", salaAtual, NULL);
  return 1;

}

int sala_apagar_escura(Elemento * null, Elemento * null1){
  null += 0;
  null1 += 0;
  salaAtual->visivel = FALSE;
  return 1;
}

int sala_apagar_geral(Elemento * sala, Elemento * null){
  sala += 0;
  null += 0;
  return 1;
}

int entrar_container(Elemento * container, Elemento * null2){
  null2 += 0;
  if(!(strcmp(salaAtual->n,"estacionamento"))) {
    if (lista_busca(container->objeto.atributos, "quebrado") != NULL){
      printf("A porta do container está quebrada, não é possível entrar\n");
      return 0;
    } 
    /*Uma vez que o jogador entre no container, a maquina se torna visivel */
    if(lista_busca(salaAtual->conteudo, "Fantastica Maquina dos Sonhos") == NULL) {
      printf("Voce moveu a maquina, ela nao esta mais aqui\n");
      return 0;
    }
    printf("Aqui está, a Fantástica Máquina Dos Sonhos\n");
    Elemento * el;
    el = tabsim_busca(tabela, "Fantastica Maquina dos Sonhos");
    el->visivel = TRUE;
    return 1;
  }
  return 0;
}

int comprar_cafe(Elemento * cafe, Elemento * null2){
  null2+=0;
  /*Verifica se o player ja possui o café*/
  if (!strcmp(salaAtual->n,"Lanchonete")) {
  if (lista_busca(player->conteudo, "Cafe de Ma Qualidade") == NULL) {
    printf("Após esperar 84 minutos, 37 segundos e meio, você finalmente consegue comprar um café\n");
    insere_inventario(cafe);
    lista_retira(salaAtual->conteudo, cafe);
    cafe->visivel = TRUE;
    return 1;
  }
  printf("Você já comprou um café, seu dinheiro acabou\n");
  return 0;
  }
  printf("Não há ninguem vendendo café aqui!\n");
  return 0;
}

int oferecer_cafe(Elemento * cafe, Elemento * professor){
  if(professor == NULL) return 0;
  if (!strcmp(salaAtual->n, "Sala de Aula")) {
    if(lista_busca(player->conteudo, "Cafe de Ma Qualidade") != NULL) {
      if (!strcmp(professor->n, "Professor Gubi")){
        printf("Você oferece o Café de Má Qualidade ao professor Gubi\n");
        printf("Parece que o café deu efeito contrário e colocou o professor para dormir\n");
        lista_retira(player->conteudo, cafe);
        lista_retira(ObjetosAnimados, professor);
        Atributo * dormindo = criaAtributo("dormindo", CARACTERISTICA);
        lista_insere(professor->objeto.atributos, dormindo);
        return 1;
      }
    }
  }
  printf("Não entendi\n");
  return 0;
}

int anima_gubi(Elemento * null1, Elemento * null2){
  null1+= 0;
  null2+= 0;
  int r = rand() % 6;
  printf("\nGubi diz: \n");
  switch (r){
    case 0:
    printf("- esse slide aqui veremos com mais detalhes em outro momento, vou apenas passar\n");
    break;
    case 1:
    printf("- como podemos observar, este programa não é muito bom. Eu teria feito diferente\n");
    break;
    case 2:
    printf("- pausa para dica cultural\n");
    break;
    case 3:
    printf("- vocês estão entendendo?\n");
    break;
    case 4:
    printf("- me interrompam se não estiverem entendendo\n");
    break;
    case 5:
    printf("- isso aqui é questão de prova\n");
    break;

  }
  return 1;
}

void anima_objetos(){
  Elo *elo;
  elo = ObjetosAnimados->cabec->next;
  while(elo != NULL){
    if(lista_busca(salaAtual->conteudo, elo->val) != NULL)
    executaAcao("anima", elo->val, NULL);
    elo = elo->next;
  }
}


int imprimeDescricao (Elemento * sala, Elemento * null) {
  null += 0;
  printf("\n");
  if (sala->visivel == FALSE){
    printf("Não consigo ver nada aqui, está escuro!\n");
    return 0;
  } 
  /*Se a sala/objeto já foi vistado antes */
  if (sala->conhecido) {

    print_string(sala->curta);
  }
  /*Se a sala/objeto não foi visitada */
  else {
    print_string(sala->longa);
    sala->conhecido = TRUE;

  }
  printf("\n");

  return 1;
}

int imprimeConteudo (Elemento * elem, Elemento * null) {
  null += 0;
  if (elem->visivel == FALSE) return 0;
  Elo * ap = elem->conteudo->cabec->next;
  if (ap != NULL)
  printf("Você observa em %s", elem->n);
  while (ap != NULL){
    /*Imprime o nome do objeto, precedido de seu artigo indefinido*/
    Elemento * el = (Elemento *) ap->val;
    printf(", ");
    if(el->visivel){
    imprimeNome(el, NULL);
    imprimeAtributos(el, NULL);
    }
    ap = ap->next;
  }
  printf("\n");
  return 1;
}


int imprimeNome (Elemento * obj1, Elemento * null) {
  null += 0;
  if (obj1 == NULL) return 0;
  print_string(obj1->artigo);
  printf(" ");
  print_string(obj1->n);
  return 1;
}

int imprimeAtributos(Elemento * obj, Elemento * null){
  null += 0;
  Elo * ap = obj->objeto.atributos->cabec->next;
  while (ap != NULL){
    Atributo * at = (Atributo *) ap->val;
    printf(" ");
    print_string(at->n);
    ap = ap->next;
  }
  return 1;
}














