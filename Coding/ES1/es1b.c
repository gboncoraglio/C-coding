#include <stdio.h>
#include <stdlib.h>

void LeggiBuffer(int* buf, int n) {
    for (int i=0; i<n; i++) {
        printf("Inserisci elemento di posizione %d: ", i);
            scanf("%d", &buf[i]);
    }
}

int* RunLengthDecoding(int* bc, int nbc, int* nbd) {
    *nbd = 0;
    for (int i= 0; i<nbc; i += 2)
        (*nbd) += bc[i];

    // - creare un vett di dimensione dim2 (allocare spazio per dim2 elementi)
    int *v2;
    v2 = (int *)malloc(sizeof(int)*(*nbd));    //allocazione DINAMICA
    // - riempirlo con i numeri positivi

    int numero_di_volte = 0;
    int numero_da_ripetere = 0;
    int idx_v2 = 0;
    for (int i= 0; i<nbc; i += 2){
        numero_di_volte = bc[i];        //5  ->  4
        numero_da_ripetere = bc[i+1];   //2  ->  3
        for (int j= 0; j<numero_di_volte; j++){
            v2[idx_v2] = numero_da_ripetere;
            idx_v2++;
        }
    }

    //ritornare il vettore
    return v2;
}



// Visualizza gli elementi di un array passato come parametro
void Visualizza(int *vettore, int dim){
    //vedi ogni elemento del vettore
    for (int i= 0; i<dim; i++){
    //stampa quell elemento
        printf("%d ", vettore[i]);
    }
    printf("\n");
}

int main(void)
{
    int *buffer_c, *buffer_d;
    int dim_c, dim_d;

    // Assicurarsi che dim_c sia un numero pari e se non lo è ripetere l’inserimento
    while (1){
        printf("Inserisci la dimensione del buffer compresso (la dimensione deve essere un numero pari): ");
        scanf("%d", &dim_c);
        if (dim_c %2 ==0)
            break;
    }


    buffer_c = (int *)malloc(sizeof(int)*(dim_c)); // Alloca un array di 'dim_c' elementi interi
    LeggiBuffer(buffer_c, dim_c); // Acquisisce gli elementi in buffer_c

    buffer_d = RunLengthDecoding(buffer_c,dim_c,&dim_d);
    Visualizza(buffer_d,dim_d); // Visualizza buffer_d

    free(buffer_c); // Disalloca buffer_c
    free(buffer_d); // Disalloca buffer_d
    return 0;
}