/*
Sviluppare un'applicazione in ANSI C che permette di tracciare le
proprie prestazioni sportive in differenti specialità.

Ogni prestazione viene salvata in un archivio storico implementato
mediante una lista; l'utente può successivamente analizzare le prestazioni
nelle singole specialità caricandole in una lista ordinata rispetto al tempo
che poi viene stampata.

Il sistema prevede che vengano implementate le seguenti funzioni:

1. caricamento da un file di testo dei dati (funzione apri_file)

2. copia delle prestazioni di una determinata specialità in una lista
ordinata (funzione analizza_specialita)

3. restituisce in un vettore le attività effettuate in una certa data
(funzione attivita_effettuate)


*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define DIMENSIONE_STRINGA 128
#define DIMENSIONE_DATA	    10

//struttura dati
typedef struct s_attivita
{
    char specialita[DIMENSIONE_STRINGA];
    char data[DIMENSIONE_DATA];		// il fomato della data è il seguente AAAA/MM/GG
    int  tempo;				// il tempo e' sempre espresso in secondi
}t_attivita;

typedef struct s_nodo_attivita
{
    t_attivita              dato;
    struct s_nodo_attivita* successivo;
} t_nodo_attivita;

typedef t_nodo_attivita* t_lista_attivita;

//funzione di utilità
int attivita_scrivi(FILE* f, const t_attivita* attivita)
{
    if (f == NULL)
        return 0;
    return
        fprintf(f, "%s %s %d\n",
            attivita->specialita, attivita->data, attivita->tempo);
}

int attivita_leggi(FILE* f, t_attivita* attivita)
{
    if (f == NULL)
        return 0;
    return
        fscanf(f, "%s%s%d\n",
            attivita->specialita, attivita->data, &attivita->tempo);
}

int attivita_confronta_tempo(t_attivita a, t_attivita b)
{
    return b.tempo - a.tempo;
}

// Funzione che effettua un inserimento in lista
void lista_aggiungi(t_lista_attivita* pt_lista, t_attivita attivita)
{
    t_lista_attivita aux = (t_lista_attivita)malloc(sizeof(t_nodo_attivita));
    if (aux == NULL)
        return;

    aux->dato = attivita;
    aux->successivo = *pt_lista;
    *pt_lista = aux;
}

// Funzione effettua un inserimento ordinato in lista in base al tempo
void lista_aggiungi_ordinato(t_lista_attivita* pt_lista, t_attivita attivita)
{
    if (*pt_lista == NULL || attivita_confronta_tempo(attivita, (*pt_lista)->dato) < 0)
        lista_aggiungi(pt_lista, attivita);
    // E' presente un errore nel testo, manca l'else
    else
        lista_aggiungi_ordinato(&((*pt_lista)->successivo), attivita);
}

void lista_stampa(FILE* f, t_lista_attivita lista) {
    if (f == NULL)
        return;
    while (lista != NULL) {
        attivita_scrivi(f, &(lista->dato));
        lista = lista->successivo;
    }
}
// La funzione permette di caricare i dati da file, il primo parametro
// e' il descrittore del file ed il secondo la lista da riempire con i
// dati letti.  la funzione restituisce il numero di attività lette
void lista_svuota(t_lista_attivita* pt_lista) {
    if (*pt_lista == NULL)
        return;
    t_lista_attivita aux = (*pt_lista);
    *pt_lista = (*pt_lista)->successivo;
    free(aux);
    lista_svuota(pt_lista);
}
int apri_file(FILE *file_ingresso, t_lista_attivita * pt_lista)
{
    int contatore = 0;
    t_attivita a;
    if (file_ingresso == NULL)
        return -1;
    while (attivita_leggi(file_ingresso, &a) == 3) {
        lista_aggiungi(pt_lista, a);
        ++contatore;
    }
    return contatore;
}

// la funzione seguente legge tutti i dati in ingresso e restituisce
// una lista ordinata rispetto al tempo di tutti gli elementi di una
// determinata specialità
// Il testo conteneva un errore, bisogna passare il nome della specialità
int analizza_specialita(t_lista_attivita lista_ingresso,
    t_lista_attivita* pt_lista_specialita, const char * specialita)
{
    int contatore = 0;
    while (lista_ingresso != NULL) {
        if (strcmp(specialita, lista_ingresso->dato.specialita) == 0) {
            lista_aggiungi_ordinato(pt_lista_specialita, lista_ingresso->dato);
            ++contatore;
        }
        lista_ingresso = lista_ingresso->successivo;
    }
    return contatore;
}

// la funzione restituisce un vettore di attivita effettuate in una
// certa data. I parametri rappresentano la lista in ingresso, la data
// e la dimensione del vettore restituito
t_attivita* attivita_effettuate(t_lista_attivita lista, char* data, int* numero_attivita)
{
    // calcolo delle dimensioni del vettore di uscita, e' necessaria una variabile di appoggio
    // per non perdere la testa della lista
    t_lista_attivita aux = lista;
    int contatore = 0;
    // Calcolo dell edimensioni del vettore di uscita
    while (aux != NULL) {
        if (strcmp(data, aux->dato.data) == 0)
            ++contatore;
        aux = aux->successivo;
    }
    if (contatore == 0) {
        numero_attivita = 0;
        return NULL;
    }
    // allocazione del vettore di uscita;
    t_attivita* vettore_uscita = (t_attivita*)calloc(contatore, sizeof(t_attivita));
    if (vettore_uscita == 0)
        return NULL;
    // visita della lista per inserire i dati nel vettore di uscita
    int i = 0;
    aux = lista; // Non ho perso il valore dell radice della lista!
    while (aux != NULL) {
        if (strcmp(data, aux->dato.data) == 0) {
            vettore_uscita[i] = aux->dato;
            ++i;
        }
        aux = aux->successivo;
    }
    *numero_attivita = contatore;
    return vettore_uscita;
}

// main
int main(void)
{
    int selezione;
    // aggiungere le altre variabili necessarie
    char buffer[DIMENSIONE_STRINGA];
    t_lista_attivita elenco_attivita = NULL;
    t_lista_attivita lista_temporanea = NULL;
    t_attivita* vettore_attivita = NULL;
    FILE* f = NULL;
    int numero_elementi;
    do {
        printf("1. Apri file\n");
        printf("2. valuta prestazioni di una specialita'\n");
        printf("3. stampa i migliori tempi\n");
        printf(">>> ");
        scanf("%d", &selezione);
        switch (selezione) {
        case 0:
            break;
        case 1:
            // lo studente implementi quanto necessario a
            // 1. acquisire il nome del file
            printf("Inserire il nome del file: ");
            scanf("%s", buffer);
            // 2. aprire il file e controllare che non ci siano errori
            if ((f = fopen(buffer, "r")) == NULL) {
                printf("Impossibile aprire %s\n", buffer);
                break;
            }
            // 3. chiamare la funzione apri_file
            numero_elementi = apri_file(f, &elenco_attivita);
            if (numero_elementi == -1) {
                printf("Problemi nel caricamento dei dati;");
                fclose(f);
                break;
            }
            fclose(f);
            lista_stampa(stdout, elenco_attivita);
            // 4. stampare il contenuto della lista
            break;
        case 2:
            // lo studente implementi quanto necessario a:
            //1. leggere da console la specialità che si desidera analizzare
            printf("Inserire il nome della specialita': ");
            scanf("%s", buffer);
            //2. chiami la funzione analizza_specialita con i parametri corretti
            numero_elementi = analizza_specialita(elenco_attivita, &lista_temporanea, buffer);
            //3. stampi il contenuto della lista
            lista_stampa(stdout, lista_temporanea);
            //4. cancelli la lista di specialità
            lista_svuota(&lista_temporanea);
            break;
        case 3:
            // lo studente implementi quanto necessario a:
            // 1. leggere da console la data
            printf("Inserire una data: ");
            scanf("%s", buffer);
            // 2. chiamare la funzione attivita_effettuate
            vettore_attivita = attivita_effettuate(elenco_attivita, buffer, &numero_elementi);
            if (vettore_attivita == NULL) {
                printf("Nessuna attivita in data %s\n", buffer);
                break;
            }
            // 3. stampare i risultati
            for (int i = 0; i < numero_elementi; ++i)
                attivita_scrivi(stdout, &(vettore_attivita[i]));
            // 4. liberare l'area eventualmente allocata
            free(vettore_attivita);
            break;
        }
    } while (selezione != 0);
}
