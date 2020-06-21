#include <stdio.h>
#include <stdlib.h>

void LeggiVettore(int *v, int n) {
    for (int i=0; i<n; i++) {
    printf("Inserisci elemento di indice %d: ", i);
    scanf("%d", &v[i]);
    }
}
/* Dato v1 di dimensione d1, restituisce un array di dimensione d2 che contiene gli elementi di v1 intervallati dalla media dei valori contigui di v1. Per esempio, se v1 = {1,2,5,8} il vettore restituito sarà {1.0, 1.5, 2.0, 3.5, 5.0, 6.5, 8.0}

        {1 , 2,  5,   8}   dim1  +
           -   -    -      dim1-1     = 2*dim1 -1


           {1,2,5,8}
            - -
            media(1,2) = 1.5

            i  =   0   1   2   3
            v1 = [ 1   2   5   8]
            v2 = [ - - - - - - | -]
            j  =   0  1   2   3     4   5    6
                                    j1 j2

*/
float* Interpola(int* v1, int d1, int* d2) {

    *d2 = 2*d1-1;
    float *vet2 = (float *) malloc(sizeof(float)*(*d2));
    float media;
    int j1 = 0;
    int j2 = 1;
    for (int i=0;i<d1-1;i++){    // for (INIZIO | FINE | COME INCREMENTARE)
        media = (float)(v1[i]+v1[i+1])/2;
        vet2[j1] = v1[i];
        vet2[j2] = media;
        j1 += 2;
        j2 += 2;
    };
    vet2[*d2-1] = v1[d1-1];
    return vet2;
}

// void Interpola1(int* v1,int* v2, int d1, int* d2) {...}

// Visualizza gli elementi di un array di float passati come parametro
void VisualizzaVettore(float *vet,int n) {
    for (int i=0;i<n;i++)
        printf("%f\n",vet[i] );
}

int main(void)
{
    int   *vett1;
    float *vett2;
    int dim1, dim2;
    printf("Inserisci la dimensione del vettore: ");
    scanf("%d", &dim1);
    vett1 = (int*)malloc(sizeof(int)*dim1); // Alloca
    LeggiVettore(vett1,dim1);

    vett2 = Interpola(vett1,dim1,&dim2);
    VisualizzaVettore(vett2,dim2);
      free(vett1);
      free(vett2);
    return 0;
}