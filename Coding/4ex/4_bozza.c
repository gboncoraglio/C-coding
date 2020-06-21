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
  lista_aggiungi_ordinato(&((*pt_lista)->successivo), attivita);
}

// La funzione permette di caricare i dati da file, il primo parametro
// e' il descrittore del file ed il secondo la lista da riempire con i
// dati letti.  la funzione restituisce il numero di attività lette
int apri_file(/* lo studente definisca i parametri in accordo alla definizione */)
{
	// lo studente implementi il corpo della funzione
}

// la funzione seguente legge tutti i dati in ingresso e restituisce
// una lista ordinata rispetto al tempo di tutti gli elementi di una
// determinata specialità
int analizza_specialita(t_lista_attivita lista_ingresso,
			t_lista_attivita* pt_lista_specialita)
{
  // lo studente implementi il corpo della funzione
}

// la funzione restituisce un vettore di attivita effettuate in una
// certa data. I parametri rappresentano la lista in ingresso, la data
// e la dimensione del vettore restituito
t_attivita* attivita_effettuate(t_lista_attivita lista, char* data, int* numero_attivita)
{
	// lo studente implementi il corpo della funzione
}

// main
int main(void)
{
  int selezione;
  // aggiungere le altre variabili necessarie

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
      // 2. aprire il file e controllare che non ci siano errori
      // 3. chiamare la funzione apri_file
      // 4. stampare il contenuto della lista
      break;
    case 2:
      // lo studente implementi quanto necessario a:
      //1. leggere da console la specialità che si desidera analizzare
      //2. chiami la funzione analizza_specialita con i parametri corretti
      //3. stampi il contenuto della lista
      //4. cancelli la lista di specialità
      break;
    case 3:
      // lo studente implementi quanto necessario a:
      // 1. leggere da console la data
      // 2. chiamare la funzione attivita_effettuate
      // 3. stampare i risultati
      // 4. liberare l'area eventualmente allocata
    }
  } while (selezione != 0);
}
