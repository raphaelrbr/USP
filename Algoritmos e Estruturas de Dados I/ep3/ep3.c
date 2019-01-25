#include <stdio.h>
#include <stdlib.h>

int vezes;


void flip(long int * v, int k, int r) {
    /*Inverte a ordem do vetor v[k,...,r]*/
    int aux, p = k, q = r;
    
    if (k<r){
        printf("%d ", k);
        vezes++;
        while(p<q){
            aux = v[p];
            v[p] = v[q];
            v[q] = aux;
            p++, q--;
        }    
    }
}

int buscaMax(long int * v, int k, int r){
    /*Retorna o indice do maior elemento no vetor
    v[k,...,r]*/

    int max = k;

    for (int i = k+1; i<=r; i++){
        if (v[i] > v[max]) max = i;
    }

    return max;
}

void ordenaPanquecas(long int * pan, int tam) {
    /*Ordena o vetor pan[0,...,tam-1], em ordem decrescente,
    utilizando a única operação flip */
    int max;
    int i = 0;

    while (i<tam-1) {
        max = buscaMax(pan, i, tam-1);
        if (i != max) {
            flip(pan,max,tam-1);
            flip(pan,i,tam-1);
        }
        i++;
    }
}

int main(){
    long int * panquecas;
    int tamanho;

   
    scanf("%d", &tamanho);
    panquecas = malloc (tamanho * sizeof(long int));
    for (int i = 0; i<tamanho; i++) scanf("%li", &panquecas[i]);     
    ordenaPanquecas(panquecas,tamanho);

    


    

    return 0;
}