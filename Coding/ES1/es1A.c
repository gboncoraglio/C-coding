#include <stdio.h>
#include <stdlib.h>
/*
La funzione legge un vettore di numeri interi fino all'inserimento del valore 0 o il raggiungimento del numero massimo di elementi n. La funzione restituisce il numero dei valori effettivamente letti
*/
int lettura_dati(int* v, int n) {
    for (int i = 0;i < n; ++i) {
        scanf("%d", &v[i]);
        if (v[i] == 0) return i;
    }
    return n;
}
/*

[-1 2 3 -4 5 6 10 -11]  ->  [2 3  5]
           -
                       (5)

   funzione (INPUTS)   ----> (OUTPUTS)

La funzione dato un vettore di ingresso che contiene valori diversi da zero restituisce un vettore contenente tutti i valori positivi presenti nel vettore di ingresso.
Il vettore deve essere allocato all’interno della funzione della dimensione esattamente uguale al numero di valori positivi presenti nel vettore di ingresso
la funzione restituisce (return) il vettore generato
dim è la dimensione del vettore di ingresso vettoreIngresso è il vettore di ingresso
*dim2 consente di restituire la dimensione del vettore
*/
int *estrae_numeri_positivi(int* vettoreIngresso, int dim, int *dim2) {
// Il codice deve essere inserito dallo studente
    // - calcolare dim2
    *dim2 = 0;
    for (int i= 0; i<dim; i++){
        if (vettoreIngresso[i] > 0){
            (*dim2) ++;}
    }

    // - creare un vett di dimensione dim2 (allocare spazio per dim2 elementi)
    int *v2;
    v2 = (int *)malloc(sizeof(int)*(*dim2));    //allocazione DINAMICA
    // - riempirlo con i numeri positivi
    int j = 0;
    for (int i= 0; i<dim; i++){
        if (vettoreIngresso[i] > 0){
            v2[j] = vettoreIngresso[i];
            j++;
        }
    }
    //ritornare il vettore
    return v2;
}
/*
La funzione stampa su console il contenuto di un vettore
*/
void stampa( int *vettore, int dim) {
// Il codice deve essere inserito dallo studente
    //vedi ogni elemento del vettore
    for (int i= 0; i<dim; i++){
    //stampa quell elemento
        printf("%d ", vettore[i]);
    }
    printf("\n");
}
int main(void) {
        int *v1;
        int *v2;
        int dim;
        int dim2;
// Inserire il codice per implementare la lettura da tastiera del numero massimo di elementi inseribili nel vettore v1
        printf("\n Digitare la dimensione del vettore 1: \n");
        scanf("%d", &dim);
// Lettura da tastiera del primo vettore utilizzando la funzione
        dim = lettura_dati(v1, dim);

//Lo studente deve chiamare la funzione estrae_numeri_positivi salvando i valori nel vettore v2 allocato // all’interno della funzione.
        v2  = estrae_numeri_positivi(v1, dim, &dim2);
// lo studente, usando la funzione stampa, stampa il risultato contenuto in v2
        stampa(v2, dim2);
// disallocazione
        free(v2);
        return 0;
}