"""
  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP,
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA.
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES
  DESSE EP E QUE PORTANTO NÃO CONSTITUEM DESONESTIDADE ACADÊMICA
  OU PLÁGIO.
  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS AS CÓPIAS
  DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO E
  DESONESTIDADE ACADÊMICA SERÃO TRATADOS SEGUNDO OS CRITÉRIOS
  DIVULGADOS NA PÁGINA DA DISCIPLINA.
  ENTENDO QUE EPS SEM ASSINATURA NÃO SERÃO CORRIGIDOS E,
  AINDA ASSIM, PODERÃO SER PUNIDOS POR DESONESTIDADE ACADÊMICA.

  Nome : Raphael Ribeiro da Costa e Silva
  NUSP : 10281601
  Turma: 45
  Prof.: Marcelo Gomes de Queiroz

  Referências: Não há referências.



  """

from random import randint

def distribuicao(N):
    """Devolve um inteiro dist onde cada dígito n=0,...N-1 representa
    um peso relativo em uma distribuição de probabilidade,
    verificando que dist esteja entre 0 e 10**N-1.
    """
    # calcula, calcula, calcula...
    dist = 0
    cont = 0
    pot = 1
    #Forma a variável dist, escolhendo cada digito aleatoriamente
    while cont < N:
        numeroSorteado = randint(0,9)
        dist = dist + numeroSorteado*pot
        pot = pot * 10
        cont = cont + 1
    assert dist in range(10**N)
    return dist


def jogada(N,jogador,lanceanterior):
    """Processa e devolve uma jogada do jogador ("humano" ou "computador"),
    que deve estar entre 0 e N-1 e não pode ser igual a lanceanterior.
    """
    # processa, processa, processa…
    if jogador == "humano":
        lance = int(input("É a sua vez de jogar: "))
        while lance == lanceanterior or lance < 0 or lance > N-1:
            if lance == lanceanterior:
                print("A mesa já escolheu esse número.")
            lance = int(input("Por favor digite outro número: "))
    else:
        print("É a vez da mesa jogar.")
        lance = randint(0,N-1)
        while lance == lanceanterior:
            lance = randint(0,N-1)
        print("A mesa escolhe o número ",lance,".",sep='')

    assert lance in range(N) and lance != lanceanterior
    return lance

def sorteia(N,dist):
    """Devolve o resultado de um sorteio enviesado dentre os
    inteiros de 0 a N-1 de acordo com a distribuição dist.
    """
    # computa, computa, computa...
    aux = dist #Variável auxiliar
    S = 0
    #Calcula S, tal que S = P0 + P1 + P2 + .. + Pn-1
    #Onde onde Pi , 0<=i<=n-1 são os pesos de cada valor a ser sorteado.
    while aux>0:
        S = S + aux%10
        aux = aux//10
    s = randint(0,S-1)
    #Inicialização para o laço a seguir
    Patual = dist%10
    sorteio = 0
    dist = dist//10
    #O seguinte laço termina quando sorteio < P0 + P1 + P2 + ... + Pn-1
    #Na ultima iteraçao, a variável sorteio guarda o resultado do sorteio envieasado
    while s>=Patual:
        Patual = Patual + dist%10
        dist = dist//10
        sorteio = sorteio + 1
    assert sorteio in range(N)
    return sorteio

def distanciaCircular(a,b, N):
    """Devolve a distancia circular modulo N, entre a e b inteiros"""
    if ((a-b)%N <= (b-a)%N):
        return (a-b)%N
    else:
        return (b-a)%N

def desmontaroleta(N,dist):
    """Explicita a estrutura da roleta maluca, enviesada pela
    distribuição dist: para cada inteiro entre 0 e N-1 mostra
    o peso correspondente (entre 0 e 9), a probabilidade
    teórica associada, e a frequência relativa deste dígito
    em uma repetição de 1000 sorteios com essa distribuição.
    """
    xAtual = 0
    pesoAtual = 0
    somaDosPesosAtual = 0
    probAtual = 0
    aux = dist #Variável auxiliar, para nao comprometer a chamada da função sorteia
    S = 0 #Guarda a soma de todos os pesos Pi, 0<=i<=n-1
    print("x \t Peso \t Prob(x) Freq(x)")
    #O laço a seguir soma os pesos P0 + ... + Pn para o calculo da probabilidade de xAtual
    while (aux > 0):
        S = S + aux%10
        aux = aux//10
    aux = dist
    while (xAtual < N):
        somaDosPesosAtual = 0
        pesoAtual = aux%10
        probAtual = pesoAtual/S
        freqAtual = 0
        valorSorteado = 0
        for i in range(1001): #Laço que sorteia mil vezes um numero aleatorio entre 0 e n-1, segundo a distribuição enviesada,
        #contabilizando a frequência de xAtual
            valorSorteado = sorteia(N,dist)
            if valorSorteado == xAtual:
                freqAtual = freqAtual + 1
        #Imprime a linha referente ao xAtual
        print("%d \t %d \t %4.3f \t %4.3f" % (xAtual,pesoAtual,probAtual,freqAtual/1000))
        aux = aux//10
        xAtual = xAtual + 1
        
    

print("Bem vind@ à roleta maluca!")
N = int(input("Por favor digite a quantidade de elementos da roleta (entre 2 e 100): "))
print("A roleta possui os números 0...",N-1,sep='')
print("Aguarde enquanto envieso a roleta...")
#Inicializações
dist = distribuicao(N)
jogoContinua = True
lanceanterior = -1
pontosHumano = 0
pontosComputador = 0
rodada = 1
vencedor = 0

#O jogo acontece indefinidamente, ate o usuário desejar encerrar
while jogoContinua:
    print("")
    print("Rodada",rodada)
    print("Escolhendo jogador inicial...")
    proximoJogador = randint(0,1)

    #Humano joga primeiro
    if proximoJogador == 0:
        lanceHumano = jogada(N,"humano",lanceanterior)
        lanceComputador = jogada(N,"computador",lanceHumano)
    #Computador joga primeiro
    else:
        lanceComputador = jogada(N,"computador",lanceanterior)
        lanceHumano = jogada(N,"humano",lanceComputador)
        
    resultado = sorteia(N,dist)
    print("Sorteio =",resultado)

    #Verifica se o humano acertou o lance
    if lanceHumano == resultado:
        pontosHumano = pontosHumano + 100
        pontosComputador = pontosComputador - 100
        vencedor = "Humano"
    #Verifica se o computador acertou o lance
    elif lanceComputador == resultado:
        pontosComputador = pontosComputador + 100
        pontosHumano = pontosHumano - 100
        vencedor = "Computador"
    #Se nenhum dos jogador acertou o valor, então verifica quem deu o lance mais próximo
    #Em caso de empate, o humano vence
    else:
        distHumano = distanciaCircular(lanceHumano,resultado,N)
        distComputador = distanciaCircular(lanceComputador,resultado,N)
        if (distHumano <= distComputador):
            pontosHumano = pontosHumano + 10
            pontosComputador = pontosComputador - 10
            vencedor = "Humano"
        else:
            pontosHumano = pontosHumano - 10
            pontosComputador = pontosComputador + 10
            vencedor = "Mesa"

    #Imprime o resultado
    if vencedor == "Humano":
        print("Você ganhou!")
        print("Pontuação: Jogador =",pontosHumano,", Mesa =",pontosComputador)
    else:
        print("A mesa ganhou!")
        print("Pontuação: Jogador =",pontosHumano,", Mesa =",pontosComputador)

    #Atualiza o valor de rodada para a proxima Rodada
    rodada = rodada + 1

    #Pergunta ao usuario se deseja continuar jogando e atualiza a
    #variável desejaContinuar
    desejaContinuar = input("Deseja continuar jogando (S/N): ")
    if desejaContinuar == "Abra o jogo!":
          desmontaroleta(N, dist)
    if desejaContinuar != 'S':
        jogoContinua = False

#Imprime mensagens finais
print("")
if vencedor == "Humano":
    print("Você deve receber",-pontosComputador,"da mesa!")

else:
    print("Você deve pagar",-pontosHumano,"para a mesa!")
print("Obrigado por jogar a roleta maluca!")

