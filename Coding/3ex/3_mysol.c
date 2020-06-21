/*
Sviluppo di un programma – Supermercato
Un supermercato vuole gestire gli articoli dei propri reparti.Per ciascun articolo devono essere
memorizzati :
- un codice alfanumerico
- il nome
- la casa produttrice
- il reparto di appartenenza
- il prezzo unitario
- la quantità presente nel supermercato.
0) Progettare la struttura dati adatta a mantenere in memoria centrale le informazioni di ogni
prodotto. In particolare, utilizzare una lista realizzata tramite strutture e puntatori.
1) Scrivere un opportuno main in cui sia previsto un menù di scelta delle operazioni seguenti, che
invochi tali funzioni passando in modo opportuno i parametri ritenuti necessari
2) Realizzare una funzione che legga da standard input i dati di un articolo e li inserisca in modo
opportuno all’interno della lista degli articoli
3) Scrivere una funzione che calcoli e restituisca il prezzo massimo e minimo degli articoli di una
determinata casa produttrice passata come parametro
4) Scrivere una funzione che restituisca in un opportuno vettore gli articoli di un determinato
reparto passato come parametro
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <malloc.h>

#define REPARTO_NUMERO  3
#define REPARTO_FRUTTA  0
#define REPARTO_CARNE   1
#define REPARTO_SALUMI  2
#define REPARTO_NON_DEFINITO -1

#define STRINGA_DIMENSIONE  128

const char TABELLA_REPARTI[REPARTO_NUMERO][STRINGA_DIMENSIONE] = { "frutta", "carne", "salumi" };

int stringa2reparto(const char* stringa) {
    for (int i = 0; i < REPARTO_NUMERO; ++i)
        if (strcmp(TABELLA_REPARTI[i], stringa) == 0)
            return i;
    return -1;
}
char * reparto2stringa(int reparto) {
    if (reparto >= REPARTO_NUMERO || reparto < 0)
        return "non definito";
    return TABELLA_REPARTI[reparto];
}

typedef struct _s_prodotto {
    char codice[STRINGA_DIMENSIONE];
    char nome[STRINGA_DIMENSIONE];
    char casa_produttrice[STRINGA_DIMENSIONE];
    int reparto_appartenenza;
    int prezzo_unitario;
    int quantita_presente;
} t_prodotto;

void prodotto_stampa(FILE* file_uscita, t_prodotto prodotto) {
    printf("codice:\t\t\t%s\nnome:\t\t\t%s\ncasa produttrice:\t%s\nreparto:\t\t%s\nprezzo:\t\t\t%.2f\nquantita':\t\t%d\n\n",
        prodotto.codice,
        prodotto.nome,
        prodotto.casa_produttrice,
        reparto2stringa(prodotto.reparto_appartenenza),
        prodotto.prezzo_unitario / 100.00,
        prodotto.quantita_presente);
}

typedef struct _s_nodo_prodotto {
    t_prodotto dato;
    struct _s_nodo_prodotto* successivo;
} _t_nodo_prodotto;
typedef _t_nodo_prodotto* t_lista_prodotti;

// la funzione restituisce ilpuntatore al prodotto appena inserito o NULL
// nel caso di problema
t_prodotto* lista_aggiungi(t_lista_prodotti* pt_lista, t_prodotto prodotto) {
    _t_nodo_prodotto* aux = (_t_nodo_prodotto *) malloc(sizeof(_t_nodo_prodotto));
    if (aux == 0)
        return NULL;
    aux->dato = prodotto;
    aux->successivo = *pt_lista;
    *pt_lista = aux;
    return &(aux->dato);
}

// t_prodotto* elenco_prodotti_reparto(t_lista_prodotti lista, int reparto, int *numero_elementi) {
void elenco_prodotti_reparto(t_lista_prodotti lista, int reparto, int *numero_elementi) {
    // da implementare
}
t_prodotto* elenco_prodotti_reparto_bis(t_lista_prodotti lista, int reparto, int *numero_elementi) {
    int contatore = 0;
    t_lista_prodotti aux = lista;
    int dimensione_vettore = 2; // valore due scelto per fare scattare il meccanismo
    t_prodotto* vettore = (t_prodotto*)malloc(sizeof(t_prodotto)*dimensione_vettore);
    t_prodotto* result;
    while (lista != NULL) {
        if (lista->dato.reparto_appartenenza == reparto) {
            if (contatore < dimensione_vettore)
                vettore[contatore] = lista->dato;
            else {
                dimensione_vettore += 2;
                result = realloc(vettore, sizeof(t_prodotto) * dimensione_vettore);
                if (result == NULL) {
                    printf("Errore di allocazione\n");
                    free(vettore);
                    return NULL;
                }
                vettore = result;
                vettore[contatore] = lista->dato;
            }
            ++contatore;
        }
        lista = lista->successivo;
    }
    result = realloc(vettore, sizeof(t_prodotto) * contatore);
    if (result == NULL) {
        printf("Errore di allocazione\n");
        free(vettore);
        return NULL;
    }
    *numero_elementi = contatore;
    return result;
}

int menu(void) {
    int scelta = 0;
    char buffer[STRINGA_DIMENSIONE];
    do {
        printf(" \
1) Carica da file \n \
2) funzione che legge da standard input \n \
3) calcolo del prezzo massimo e minimo degli articoli di una determinata casa produttrice \n \
4) articoli di un determinato reparto \n \
5) elenco degli articoli aventi quantità minore di un determinato valore \n\n");
        printf(">>> ");
        fgets(buffer, STRINGA_DIMENSIONE, stdin);
        scelta = atoi(buffer);
    } while (scelta < 0 || scelta > 5);
    return scelta;
}

// f : lista * stringa -> int * int
void calcolo_estremi(t_lista_prodotti lista,  char *casa_produttrice ,int *valore_massimo,int *valore_minimo) {
    *valore_massimo = -1;
    *valore_minimo = 3000000;

    while (lista != NULL) {
        printf("%d\n",strcmp(lista->dato.casa_produttrice, casa_produttrice));
        printf("%s\n",lista->dato.casa_produttrice);
        printf("%s\n",casa_produttrice);
        if (strcmp(lista->dato.casa_produttrice, casa_produttrice) == 0) {
            printf("%d\n",lista->dato.prezzo_unitario);
            if (lista->dato.prezzo_unitario > *valore_massimo)
                *valore_massimo = lista->dato.prezzo_unitario;
            if (lista->dato.prezzo_unitario < *valore_minimo)
                *valore_minimo = lista->dato.prezzo_unitario;
        }
        lista = lista->successivo;
    }

}
//
// questa funzione legge i dati dal file elenco.txt, opera le conversioni necessarie
// e li carica nella lista.
// la funzione restituisce il numero di recordo letti o -1 in caso di errore
//
// La funzione mostra un esempio di uso di scanf per leggere nomi che comprendono
// caratteri spaziatura
int carica_file(const char* nome_file, t_lista_prodotti* pt_lista) {
    FILE* f;
    if ((f = fopen(nome_file, "r")) == NULL)
        return -1;

    t_prodotto p;
    char reparto[STRINGA_DIMENSIONE];
    float prezzo;
    int contatore = 0;
    while (fscanf(f, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%f\n%d\n", p.codice,
        p.nome, p.casa_produttrice, reparto, &prezzo, &p.quantita_presente) == 6) {
        p.reparto_appartenenza = stringa2reparto(reparto);
        p.prezzo_unitario = prezzo * 100;
        lista_aggiungi(pt_lista, p);
        ++contatore;
    }
    return contatore;
}


int main(void) {
    int scelta, somma;
    t_lista_prodotti elenco_prodotti = NULL;
    t_prodotto un_prodotto;
    char buffer[STRINGA_DIMENSIONE];

    char *nome_file;
    strcpy(nome_file, "3_file.txt");
    do {
        switch (menu()) {
        case 0: // Uscita
            printf("Il programma sta per terminare\n");
            return 1;
        case 1: // carica da file, funzione aggiunta per caricare i dati per il test più
            // rapidamente
            // 1. chiamare la funzione carica con i parametri corretti (il file di ingreso si chiama elenco.txt
                somma = carica_file(nome_file, &elenco_prodotti);
            // 2. stampare il numero di elemento caricati
                printf("%d\n",somma);
            break;
        case 2:
            // 2) Realizzare una funzione che legga da standard input i dati di un articolo e li inserisca in modo
            // opportuno all’interno della lista degli articoli
            // 1. leggere un record da console
                printf("Inserisci un un codice alfanumerico:\n");
                scanf("%s", un_prodotto.codice);
                printf("Inserisci il nome:\n");
                scanf("%s", un_prodotto.nome);
                printf("Inserisci la casa produttrice:\n");
                scanf("%s", un_prodotto.casa_produttrice);
                printf("Inserisci il reparto di appartenenza:\n");
                scanf("%s", buffer);
                un_prodotto.reparto_appartenenza = stringa2reparto(buffer);
                printf("Inserisci il prezzo unitario:\n");
                scanf("%d", &un_prodotto.prezzo_unitario);
                printf("Inserisci la quantità presente nel supermercato.:\n");
                scanf("%d", &un_prodotto.quantita_presente);
            // 2. inserire nell'archivio
                lista_aggiungi(&elenco_prodotti, un_prodotto);
            break;
        case 3:
            // Scrivere una funzione che calcoli e restituisca il prezzo massimo e minimo degli articoli di una
            // determinata casa produttrice passata come parametro
            printf("\t casa produttrice: ");
            // fgets(buffer, STRINGA_DIMENSIONE, stdin);
            // buffer[strlen(buffer) - 1] = '\0';
            scanf("%s", buffer);
            int valore_massimo, valore_minimo;
            // Chiamare la funzione corretta con i parametri corretti
            calcolo_estremi(elenco_prodotti, buffer ,&valore_massimo,&valore_minimo);
            printf("%d %d\n", valore_massimo, valore_minimo);
            break;
        case 4:
            printf("\t reparto: ");
            fgets(buffer, STRINGA_DIMENSIONE, stdin);
            buffer[strlen(buffer) - 1] = '\0';
            // 1. chiamare la funzione con i parametri corretti
            // 2. stampare il risultato
            break;
        }
    } while (1);
}
