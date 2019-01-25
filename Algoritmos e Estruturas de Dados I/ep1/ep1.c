
/*
BCC 2018 - EP3
Nome: Raphael Ribeiro da Costa e Silva
NUSP: 10281601
*/


#include <stdio.h>

//Vetor para guardar as respostas do problema de 1 a 999999.
//Isto é, o valor de respostas[i] é o numero de passos necessários para o número i converger para 1 segundo a regra de Collatz. 
//Se respostas[i] == 0, entao o numero de passos necessarios para i converger para 1 é desconhecido.

long int respostas[1000000];


long int numeroPassos (unsigned int n) {
	long int resposta;
	/*Verifica no vetor respostas se já se conhece a resposta para n,
	caso contrário calcula recursivamente a resposta.
	Caso n seja maior que 999999, calcula recursivamente.
	*/
 
	if (n==1) return 0;

	//Se a resposta é conhecida ou o numero é maior que 999999, retorna a resposta.
	//Observe que se o numero é maior que 999999, a segunda condição do if não é verificada
	else if (n < 1000000 && respostas[n]!=0) return respostas[n];

	//Se o o numero é par, calcula recursivamente a resposta utilizando a regra par da Conjectura de Collatz
	else if (n%2 == 0) {

		//Calcula a resposta recursivamente
		resposta = 1 + numeroPassos(n/2);

		//Armazena a resposta para o numero n
		if (n<1000000) respostas[n] = resposta;

		return resposta;


	} 

	//Numero é impar, utiliza a regra ímpar da Conjectura de Collatz
	else {

		//Calcula a resposta recursivamente
		resposta = 1 + numeroPassos(n*3+1);

		//Armazena a resposta para o numero n
		if (n<1000000) respostas[n] = resposta;

		return resposta;
	}
}


int main() {
	long int i, f;

	scanf("%li", &i);
	scanf("%li", &f);

	//Inicializa o vetor respostas com valor desconhecido (0)
	for (long int cont = 2; cont<1000000; cont++) respostas[cont] = 0;

	//Para cada valor no intervalo, imprime a quantidade de passos para este valor convergir para 1
	for (long int cont = i; cont<= f; cont++) {
		printf("%li\n", numeroPassos(cont));
	}



	return 0;
}