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

  Referências: Não há

  """

from random import randint


def verificaRima(palavra1, palavra2):
    """verifica se as duas ultimas letras de palavra1 e palavra2 são iguais,
    retornando True caso verdadeiro e False caso contrário. Também retorna True
    se palavra2 == '-' ou se o tamanho de uma das palavras é menor que 2.
    """
    if palavra2 == '-' or len(palavra1) < 2 or len(palavra2) < 2:
        return True
    else:
        if palavra1[len(palavra1)-1] == palavra2[len(palavra2)-1] and palavra1[len(palavra1)-2] == palavra2[len(palavra2)-2]:
            return True
        else:
            return False


def sorteia(lista, palavrasSorteadas, M, rima):
    """Sorteia um verbo ou substantivo em lista tentando manter a condição de
    não repetição e rima, segundo os parametros indicadores e rima, até um maximo
    de M tentativas, retornando o ultimo indice sorteado.
    """
    cont = 0
    while cont<M:
        indiceSorteado = randint(0,len(lista)-1)

        if palavrasSorteadas[indiceSorteado] == False:
            if verificaRima(lista[indiceSorteado],rima):
                palavrasSorteadas[indiceSorteado] = True
                break
        cont = cont + 1

    return lista[indiceSorteado]

def declina(verbo,objeto):
    """Declina preposição do verbo segundo as regras gramaticais da lingua portuguesa,
    retornando uma string com a preposição declinada.
    """
    preposicao = verbo.split()[1]
    artigo = objeto.split()[0]
    contracao = preposicao + ' ' + artigo #Em caso da preposição ser para ou com
    if preposicao == "-":
        contracao = artigo
    if artigo == "a":
        if preposicao == "a":
            contracao = "à"
        elif preposicao == "de":
            contracao = "da"
        elif preposicao == "em":
            contracao = "na"
        elif preposicao == "por":
            contracao = "pela"
    elif artigo == "o":
        if preposicao == "a":
            contracao = "ao"
        elif preposicao == "de":
            contracao = "do"
        elif preposicao == "em":
            contracao = "no"
        elif preposicao == "por":
            contracao = "pelo"
    return contracao

def produzVersos(substantivos, verbos, numeroDeVersos, rima):
    """gera (na tela)
    um poema, usando as listas de substantivos e verbos e com o numero
    de versos desejado, com ou sem rima, dependendo do valor do parametro
    booleano  rima.
    """
    M = len(substantivos)+len(verbos)
    substantivosSorteados = []
    verbosSorteados = []

    for i in range(len(substantivos)):
        substantivosSorteados.append(False)
    for i in range(len(verbos)):
        verbosSorteados.append(False)
    ultimaRima = '-'
    
    for i in range(1,numeroDeVersos + 1):
    
        #Verifica se o verso terá conjunção, sorteando-o caso verdadeiro.
        conj = randint(0,8)
        if conj < 3:
            conjuncoes = ["como ","e ","enquanto ","mesmo quando ","porque ","quando ","se ","toda vez que "]
            conjuncao = conjuncoes[randint(0,7)]
        else:
            conjuncao = ''
        #Forma uma frase do poema, sorteando a ordem dos elementos da frase entre
        #3 casos possíveis:
        #0) sujeito + verbo + objeto
        #1) sujeito + objeto + verbo
        #2) verbo + objeto + sujeito
        caso = randint(0,3)
        if caso == 0:
            sujeito = sorteia(substantivos, substantivosSorteados, M, '-')
            verbo = sorteia(verbos, verbosSorteados, M, '-')
            objeto = sorteia(substantivos, substantivosSorteados, M, ultimaRima)
            frase = conjuncao + sujeito + ' ' + verbo.split()[0] + ' ' + declina(verbo,objeto) + ' '+ objeto.split()[1]
            ultimaPalavra = objeto.split()[1]
        elif caso == 1:
            sujeito = sorteia(substantivos, substantivosSorteados, M, '-')
            objeto = sorteia(substantivos, substantivosSorteados, M, '-')
            verbo = sorteia(verbos, verbosSorteados, M, ultimaRima)
            frase = conjuncao + sujeito + ' ' + declina(verbo,objeto) + ' ' + objeto.split()[1] + ' ' + verbo.split()[0]
            ultimaPalavra = verbo.split()[0]

        else:
            verbo = sorteia(verbos, verbosSorteados, M, '-')
            objeto = sorteia(substantivos, substantivosSorteados, M, '-')
            sujeito = sorteia(substantivos, substantivosSorteados, M, ultimaRima)
            frase = conjuncao + verbo.split()[0] + ' ' + declina(verbo,objeto) + ' ' + objeto.split()[1] + ' ' + sujeito
            ultimaPalavra = sujeito.split()[1]

        if i%2 == 1: #i é impar
            #Deixa a primeira letra do verso em letra maiscula
            frase = frase.capitalize()
            #Nos versos impares, guardamos a ultima palavra para o verso a seguir
            #rimar. Se rima == false, ultimaRima sempre será igual a '-', dispensando
            #a necessidade de rimas na construção dos versos.
            if rima:
                ultimaRima = ultimaPalavra
            else:
                ultimaRima = '-'

        else: #i é par
            ultimaRima = '-' #A proxima frase será impar, portanto não precisa
            #rimar
        if i == numeroDeVersos or i%2 == 0: #Ultimo verso
            frase = frase + '.' #adiciona ponto final ao final do verso
        print(frase)
        if i%4 == 0: #pula uma linha a cada quatro versos
            print('')

def main():
    substantivos = []
    verbos = []
    numeroDeSubstantivos = int(input("Quantos substantivos você deseja utilizar?\n"))
    print("Digite um substantivo (com artigo) por linha:")
    for i in range(numeroDeSubstantivos):
        substantivos.append(input(''))

    numeroDeVerbos = int(input("Quantos verbos você deseja utilizar?\n"))
    print("Digite um verbo (com preposição) por linha")
    for i in range(numeroDeVerbos):
        verbos.append(input(''))

    rima = input("Você deseja rimas? S para Sim, N para Não\n")
    if rima == 'S':
        rima = True
    else:
        rima = False
    numeroDeVersos = int(input("Quantos versos você deseja?\n"))
    print("Imprimindo poesia")
    print("")
    produzVersos(substantivos, verbos, numeroDeVersos, rima)

main()
