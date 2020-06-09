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
#include <stdio.h>
#include <string.h>
// #include <malloc.h>
// #include <malloc/malloc.h>
#include <stdlib.h>

#define DIMENSIONE_STRINGA 128
#define DIMENSIONE_DATA     10

//struttura dati
typedef struct s_attivita
{
  char specialita[DIMENSIONE_STRINGA];
  char data[DIMENSIONE_DATA];       // il fomato della data è il seguente AAAA/MM/GG
  int  tempo;               // il tempo e' sempre espresso in secondi
}t_attivita;

typedef struct s_nodo_attivita
{
    t_attivita              dato;
    struct s_nodo_attivita* successivo;
} t_nodo_attivita;

typedef t_nodo_attivita* t_lista_attivita;

t_lista_attivita make_null_lista(){return NULL;}

//funzione di utilità
int attivita_scrivi(FILE *f, const t_attivita* attivita)
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
  else
    lista_aggiungi_ordinato(&((*pt_lista)->successivo), attivita);
}


// La funzione permette di caricare i dati da file, il primo parametro
// e' il descrittore del file ed il secondo la lista da riempire con i
// dati letti.  la funzione restituisce il numero di attività lette
int apri_file(FILE* f,t_lista_attivita *pt_lista)
{
    // lo studente implementi il corpo della funzione
    t_attivita A;
    int contatore;
    while (fscanf(f, "%s\n%s\n%d\n", A.specialita, A.data, &A.tempo) == 3) {
        lista_aggiungi(pt_lista, A);
        contatore ++;
    }
    return contatore;

}

// la funzione seguente legge tutti i dati in ingresso e restituisce
// una lista ordinata rispetto al tempo di tutti gli elementi di una
// determinata specialità
int analizza_specialita(t_lista_attivita lista_ingresso,
            t_lista_attivita* pt_lista_specialita,char* specialita)
{
  // lo studente implementi il corpo della funzione
  int contatore = 0;
  while(lista_ingresso!=NULL){
        if (strcmp(lista_ingresso->dato.specialita,specialita)==0){
            contatore ++;
            lista_aggiungi_ordinato(pt_lista_specialita, lista_ingresso->dato);}

        lista_ingresso = lista_ingresso->successivo;
            }
  return contatore;
}

void empty_list(t_lista_attivita* pt_lista) {
    if (*pt_lista == NULL)
        return;
    t_lista_attivita aux = (*pt_lista);
    *pt_lista = (*pt_lista)->successivo;
    free(aux);
    empty_list(pt_lista);
}


// la funzione restituisce un vettore di attivita effettuate in una
// certa data. I parametri rappresentano la lista in ingresso, la data
// e la dimensione del vettore restituito
t_attivita* attivita_effettuate(t_lista_attivita lista, char* data, int* numero_attivita)
{
    // lo studente implementi il corpo della funzione
    t_lista_attivita corrente_nodo = lista;
    int contatore = 0;

    while (corrente_nodo != NULL) {
        if (strcmp(data, corrente_nodo->dato.data) == 0)
            ++contatore;
        corrente_nodo = corrente_nodo->successivo;
    }
    if (contatore == 0) {
        numero_attivita = 0;
        return NULL;
    }

    // allocazione il vettore;
    t_attivita* vettore_uscita = (t_attivita*)calloc(contatore, sizeof(t_attivita));
    if (vettore_uscita == 0)
        return NULL;


    int i = 0;
    corrente_nodo = lista; // ritorno alla testa
    while (corrente_nodo != NULL) {
        if (strcmp(data, corrente_nodo->dato.data) == 0) {
            vettore_uscita[i] = corrente_nodo->dato;
            ++i;
        }
        corrente_nodo = corrente_nodo->successivo;
    }
    *numero_attivita = contatore;
    return vettore_uscita;
}

void stampa(t_lista_attivita L){
  while(L!=NULL){
    printf("%s\n",L->dato.specialita);
    printf("%s\n",L->dato.data);
    printf("%d\n",L->dato.tempo);
    printf("\n");
    L = L->successivo;
  }
}

// main
int main(void)
{
  int selezione;
  // aggiungere le altre variabili necessarie
  char buffer[DIMENSIONE_STRINGA];
  t_lista_attivita L =make_null_lista();
  t_lista_attivita L_specialita =make_null_lista();
  int numero_attivita;
  FILE* f = NULL;
  // Creare un vettore con elementi di tipo t_attivita
  t_attivita* vettore_attivita = NULL;

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
          printf("inserisci il nome del file:\n");
          scanf("%s",buffer);
      // 2. aprire il file e controllare che non ci siano errori
          f = fopen(buffer, "r");
          if (f == NULL) {
            printf("File non trovato\n");
            return 0; }
      // 3. chiamare la funzione apri_file
            numero_attivita = apri_file(f,&L);
      // 4. stampare il contenuto della lista
            stampa(L);
      break;
    case 2:
      // lo studente implementi quanto necessario a:
      //1. leggere da console la specialità che si desidera analizzare
          printf("inserisci il nome della specialita:\n");
          scanf("%s",buffer);
      //2. chiami la funzione analizza_specialita con i parametri corretti
          numero_attivita = analizza_specialita(L, &L_specialita,buffer);
      //3. stampi il contenuto della lista
          stampa(L_specialita);
      //4. cancelli la lista di specialità
          empty_list(&L_specialita);
      break;
    case 3:
      // lo studente implementi quanto necessario a:
      // 1. leggere da console la data
          printf("Inserire una data: ");
            scanf("%s", buffer);
      // 2. chiamare la funzione attivita_effettuate
          vettore_attivita  = attivita_effettuate(L, buffer, &numero_attivita);
          if (vettore_attivita == NULL) {
                printf("Nessuna attivita in data %s\n", buffer);
                break;
            }
      // 3. stampare i risultati
            for (int i = 0; i < numero_attivita; ++i){
                printf("%s\n",vettore_attivita[i].specialita);
                printf("%s\n",vettore_attivita[i].data);
                printf("%d\n",vettore_attivita[i].tempo);
                printf("\n");
              }
      // 4. liberare l'area eventualmente allocata
            free(vettore_attivita);
    }
  } while (selezione != 0);
}
