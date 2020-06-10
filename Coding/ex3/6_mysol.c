/*
Un file contiene la raccolta di 10 frasi (il file contioene esattamente 10 frasi).
Ogni frase è composta da un numero di parole generico.
Non si usano in queste frasi simboli separatori come l'apostrofo e non si utilizza nessun simbolo di
interpunzione ad eccezione del punto che viene utilizzato come separatore fra una frase e la successiva.
Tutte le parole sono separate da uno spazio bianco (o da un ritorno a capo) e anche il punto è preceduto e
seguito da uno spazio bianco o da un ritorno a capo.

Scrivere un programma C che effettui le seguenti operazioni:
1. Funzione Carica che consente di copiare il contenuto del file in un vettore di frasi. Ciascuna frase è
realizzata come una lista di parole;
2. Funzione che restituisce il numero di volte che compare una data parola (passata come argomentoo) in ciascuna
delle frasi
3. Funzione che restituisce la lunghezza (numero di parole) della frase più breve e della frase più lungha
*/
#define _CRT_SECURE_NO_WARNINGS
//inserire qua le istruzioni di precompilazione necessarie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DIM 10  //numero delle frasi contenute nel file
#define LM 20   //lunghezza stringhe

//definizione struttura dati lista

typedef struct n {
    char parola[LM];
    struct n* next;
}nodo, * lista;

/** Funzioni primitive per uso lista1 ***/

//makenullList restituisce la lista vuota
lista makenullList() {
    return NULL;
}
//test lista vuota
int emptyLista(lista l) {
    if (l == NULL) return 1;
    return 0;
}
/*cons premette di inserire una operazione in testa alla lista restituisce 1 se l’operazione è avvenuta con successo,
0 altrimenti*/
int cons(lista* pl, char* word) {
    lista aux;
    aux = (lista)malloc(sizeof(nodo));
    if (aux == NULL) return 0;
    strcpy(aux->parola, word);
    aux->next = *pl;
    *pl = aux;
    return 1;
}
/*funzione che restituisce il numero di elementi contenuti nella lista*/
int lunghezza(lista L) {
    int cont = 0;
    while (L != NULL) {
        cont++;
        L = L->next;
    }
    return cont;
}

/*funzione per la gestione del menu*/
int menu(void) {
    int scelta;
    printf("\n 1) esegui quesito 1");
    printf("\n 2) esegui quesito 2");
    printf("\n 3) esegui quesito 3");
    printf("\n 0) esci dal programma\n");
    scanf("%d", &scelta);
    return scelta;
}


//definizione dei quesiti
/*
quesito 1, consente il carimamente delle informazioni presenti nel vettore
in un vettore di liste.
Il nome del file è acquisito all'interno della funzione
La funzion restituisce un tipo void
*/
void quesito1(lista *archivio) {
    char nomefile[LM], parola[LM];
    FILE* fp;
    int indice = 0;
    printf("\n inserisci il nome del file \n");
    scanf("%s", nomefile);
    fp = fopen(nomefile, "r");
    if (fp == NULL) return;
    /* lettura del file e trasferimento dei dati nel vettore di liste */

    while (fscanf(fp, "%s\n", parola) == 1) {
        if (strcmp(parola,".") != 0)
            cons(&archivio[indice], parola);
        else{
            indice++;
        }
    }
}

//stampa il contenuto del vettore di liste
void stampaLista(lista L1) {
    printf("\n");
    for (; L1 != NULL; L1 = L1->next)
        printf("%s ", L1->parola);
}

void stampaArchivio(lista* vettoreListe) {
    /*scrivere l'implementazione della funzionw */
    for (int i = 0; i < DIM; i++)
        stampaLista(vettoreListe[i]); //inizializza l'archivio vuoto
}

//Funzione che restituisce il numero totale volte che compare una data parola in una frase
int occorrenze(lista L1, char* word) {
    int contatore = 0;
    while (L1 != NULL){
        if (strcmp(word,L1->parola) == 0)
            contatore++;
        L1 = L1->next;
    }
    return contatore;
}

int quesito2(lista* vettoreListe, char* word) {
    int conta = 0;
    for (int i = 0; i < DIM; i++)
        conta += occorrenze(vettoreListe[i], word);
    return conta;
}

void quesito3(lista* vettoreListe,int *min, int *max) {
    *min = 30;
    *max = 0;
    int numero_parole;
    for (int i = 0; i < DIM; i++){
        numero_parole = lunghezza(vettoreListe[i]);
        if (numero_parole > *max)
            *max = numero_parole;
        if (numero_parole < *min)
            *min = numero_parole;
    }
}

//main
int main(void) {
    lista archivio[DIM];  //archivio è il vettore di liste in cui copiare il contenuto del file
//aggiungere definizione di eventuali altre variabili necessarie ed inizializzazioni
    int scelta = 0, minimo, massimo;
    int somma;

    for (int i = 0; i < DIM; i++)
        archivio[i] = makenullList(); //inizializza l'archivio vuoto
    char parola[LM];
    do {
        scelta = menu();
        switch (scelta) {
        case 1:
            quesito1(archivio);
            stampaArchivio(archivio);
            break;
        case 2:
            printf("inserisci la parola di cui vuoi calcolare il numero delle occorrenze\n");
            scanf("%s", parola);
            //aggiungere la chiamata della funzione quesito 2 e la stampa dei risultati
            somma = quesito2(archivio, parola);
            printf("numero delle occorrenze: %d\n", somma);
            break;
        case 3:
            quesito3(archivio,&minimo, &massimo);
            printf("\nlunghezza minima %d, lunghezzza massima %d", minimo, massimo);
        }
    } while (scelta != 0);
}
