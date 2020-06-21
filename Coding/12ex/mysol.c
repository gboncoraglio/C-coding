/*
Sviluppare una applicazione desktop in ANSI C che permetta di gestire una coda di attesa con priorità.
La struttura è composta da un vettore che contiene due code, ognuna delle code è caratterizzata da un
livello di priorità crescente (la coda 0 è prioritaria).
Gli elementi vengono estratti in base al seguente algoritmo:
1. Gli elementi sono sempre estratti dalla coda con priorità maggiore (coda 0) tranne quando questa è vuota,
    in questo caso vengono estratti dalla coda a priorità più bassa

Implementare le seguenti funzioni
1. caricamento dei dati da un file di ingresso
2. estrazione del primo elelemnto secondo l'algoritmo descritto
3. conteggio degli elementi presenti in ognuna delle due code
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <malloc.h>
// #include <malloc/malloc.h>

#define VERO    1
#define FALSO   0

#define DIMENSIONE_STRINGA  128
// Definizioni relative alla partita

typedef struct s_nodo {
    char nome[DIMENSIONE_STRINGA];
    struct s_node* successivo;
} t_elemento, * pt_elemento;

typedef struct {
    pt_elemento primo;
    pt_elemento ultimo;
} t_coda;

// coda_vuota
//  verifica se la coda è vuota
//  return:     retistuisce vero se la coda è vuota
int coda_vuota(t_coda c) {
    return (c.primo == NULL) ? VERO : FALSO;
}
// coda_aggiungi
//  La funzione inserisce un elemento in coda
//  parametri:  coda da modificare, nome da inserire
//  return:     VERO se corretta, FALSO altrimenti
// Lo studente implementi la funzione
int coda_aggiungi(t_coda* pc, const char *n) {
    //inserisce un elemento in coda;
    pt_elemento aux;
    aux = (pt_elemento)malloc(sizeof(t_elemento));
    if (aux==NULL) return FALSO;
    strcpy(aux->nome,n);
    aux->successivo=NULL;

    if (coda_vuota(*pc))
        (*pc).primo= (*pc).ultimo=aux;
    else {
        (*pc).ultimo->successivo = aux;
        (*pc).ultimo = aux;
    }
    return VERO;
}

// coda_primo
//  La funzione restituisce il puntatore al primo elemento
//  parametri:  coda
//  return:     primo elemento o NULL se vuota
char * coda_primo(t_coda c) {
    if (coda_vuota(c))
        return NULL;
    return c.primo->nome;
}


// coda_rimuovi
//  La funzione rimuove il primo elemento della coda
//  parametri:  coda
//  return:     void
void coda_rimuovi(t_coda* pc) {
    if (coda_vuota(*pc))
        return;
    pt_elemento aux = pc->primo;
    if (pc->primo == pc->ultimo)
        pc->primo = pc->ultimo = NULL;
    else
        pc->primo = pc->primo->successivo;
    free(aux);
}
// 1. caricamento dei dati da un file di ingresso
//  carica_dati
//      parametri:  struttura dati, nome del file
//      return:     void
// Lo studente completi L'iimplementazione della funzione
void carica_dati(t_coda c[], const char* nome_file) {
    FILE* f;
    char nome[DIMENSIONE_STRINGA];
    int priorita;
    if ((f = fopen(nome_file, "r")) == NULL) {
        printf("Errore aprendo %s\n", nome_file);
        return;
    }
    while (fscanf(f, "%s %d\n", nome,&priorita) == 2)
        coda_aggiungi( &c[priorita], nome);
}

// funzione estrai_archivio
//  parametri:  strtuttura dati
//  return:     1 se riuscito, 0 se la coda è vuota
// Lo studente implementi la funzione
int estrai_archivio(t_coda coda_attesa[], int numero_elementi) {
    int coda_idx;
    for (int i=0;i <numero_elementi; i++){
        if (coda_vuota(coda_attesa[0])){
            if (coda_vuota(coda_attesa[1]))
                return 0;
            coda_idx = 1;
        }
        else
            coda_idx = 0;
        printf("cliente %s\n", coda_attesa[coda_idx].primo->nome);
        coda_rimuovi(&coda_attesa[coda_idx]);
    }
    return 1;
}
// conteggio_elementi
//  il vettore deve essere allocato nella funzione
//  parametri:  struttura dati,
//  return:     vettore che contiene il risultato
// Lo studente implementi la funzione
int* conteggio_elementi( t_coda coda_attesa[]) {
    // - creare un vett di dimensione dim2 (allocare spazio per dim2 elementi)
    int *risultato;
    risultato = (int *)malloc(sizeof(int)*(2));

    for (int i=0;i <2; i++){
        risultato[i] = 0;
        pt_elemento aux = coda_attesa[i].primo;
        while (aux != NULL){
            risultato[i]++;
            aux = aux->successivo;
        }
    }
    return risultato;
}

int main(void) {
    int selezione;
    char buffer[DIMENSIONE_STRINGA];
    t_coda coda_attesa[2] = { {NULL,NULL} };
    int contatore = 0;
    int ris;
    int numero_elementi;
    int* risultato = NULL;
    do {
        printf("1. caricamento dei dati da un file di ingresso\n");
        printf("2. estrazione del primo elelemnto secondo l'algoritmo descritto\n");
        printf("3. conteggio degli elementi presenti in ognuna delle due code\n");
        printf("0. fine\n");
        printf(">>> ");
        scanf("%d", &selezione);
        switch (selezione) {
        case 0:
            printf("fine programma\n");
            break;
        case 1:
            // Lo studente implementi quanto necessario a svolgere le seguenti operazioni
            // 1. richiesta del nome del file da cui caricare i dati
            printf("Nome del file: ");
            scanf("%s", buffer);
            // 2. chiamata della funzione carica_dati
            carica_dati(coda_attesa, buffer);
            // da completare
            break;
        case 2:
            // Scrivere il codice necessario ad implementare l'estrazione di un elementi dalla
            // struttura dati.
            // 1.   implementare quanto necessario ad acquisire il numero di elementi
            //      da estrarre
            // 2.   scrivere il codice per estrarre il numero di elementi richiesto e stamparne
            //      il contenuto liberando le risorse non più necessarie
            printf("Inserire il numero di elementi da estrarre: ");
            scanf("%d", &numero_elementi);
            // da completare
            ris = estrai_archivio(coda_attesa, numero_elementi);
            if (ris==0)
                printf("Errore, numero di elementi in coda minore del numero richiesto!\n");
            break;
        case 3:
            // Lo studente implementi quanto necessario a chiamare la funzione conteggio elementi
            // stampare il risultato e deallocare se necessario
            // da completare
            risultato = conteggio_elementi(coda_attesa);
            for (int i=0;i <2; i++)
                printf("Nella coda %d ci sono %d clienti\n",i, risultato[i]);
            free(risultato);
            break;
        }
    } while (selezione != 0);
}