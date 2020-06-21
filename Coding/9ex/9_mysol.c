/*
Sviluppo di applicazione in ANSI C per gestire i viaggi di una flotta aziendale di veicoli

In un archivio memorizzato su un file di testo (allegato "viaggi.txt") è memorizzato
l'elenco dei viaggi effettuati dai diversi veicoli.
Ogni viaggio è memorizzato su una riga del file, con i campi: id viaggio, targa veicolo,
km percorsi, costo viaggio.

Implementare le seguenti funzioni:

1. CaricaViaggi: carica l'elenco dei viaggi effettuati dalla flotta (lettura del file; ogni id viaggio è presente solo una volta nel file) in una lista di viaggi.
2. AggiungiViaggio: dato un id viaggio, km e costo, se l'id esiste già in lista si sommano ai valori già presenti in lista, in caso contrario inserisce un nuovo viaggio nella lista (fornendo da tastiera in tal caso anche la targa)
3. Data una targa, stampa il totale dei km percorsi ed il costo medio per km di tutti i viaggi ad essa associati

*/


// #include ... // Includere gli header di libreria necessari
#include <stdio.h>
#include <string.h>
// #include <malloc.h>
#include <stdlib.h>

#define NOME_FILE "viaggi.txt"

typedef struct Viaggio
{
  char  id_viaggio[5];
  char  targa[9];
  int   km;
  float costo;
} TViaggio;

typedef struct NodoLista
{
  TViaggio viaggio;
  struct NodoLista* succ;
} TNodoLista;

typedef TNodoLista* PNodoLista;

/* ListaAggiungi inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int ListaAggiungi(PNodoLista* plista, TViaggio viaggio)
{
  PNodoLista aux;

  aux = (PNodoLista)malloc(sizeof(TNodoLista));

  if (aux == 0)
    return 0;

  aux->viaggio = viaggio;
  aux->succ = *plista;

  *plista = aux;

  return 1;
}


void stampa(PNodoLista lista){
  while (lista != NULL){
    printf("%s %s %d %f\n",lista->viaggio.id_viaggio,lista->viaggio.targa,lista->viaggio.km,lista->viaggio.costo);
    printf("\n");
    lista = lista->succ; }
}

/*
1. CaricaViaggi: carica l'elenco dei viaggi effettuati dalla flotta (lettura del file; ogni id viaggio è presente solo una volta nel file) in una lista di viaggi
  Restituisce 1 se l'operazione va a buon fine, 0    altrimenti.
*/
int CaricaViaggi(PNodoLista* plista, char* nome_file)
{
  // ... da completare a cura dello studente ...
  FILE* fp;
  int risultato = 1;
  TViaggio viaggio;
  fp = fopen(nome_file, "r");
  if (fp == NULL){
    risultato = 0;
    return risultato;}

  while (fscanf(fp, "%s%s%d%f\n", viaggio.id_viaggio,viaggio.targa,&viaggio.km,&viaggio.costo) == 4) {
    risultato = ListaAggiungi(plista,  viaggio);
  }
  fclose(fp);
  return risultato;
}



/*
 2. AggiungiViaggio: dato un id viaggio, km e costo, se l'id esiste già in lista si sommano ai valori già presenti in lista,
	in caso contrario inserisce un nuovo viaggio nella lista (fornendo da tastiera in tal caso la targa)
*/
void AggiungiViaggio(PNodoLista* lista,
		   char* id_viaggio, int km, float costo)
{
    // ... da completare a cura dello studente ...
    //Cerca nella lista se id viaggio esiste e fai l'update
    PNodoLista currNodo = *lista;
    while (currNodo != NULL){
      if (strcmp(currNodo->viaggio.id_viaggio,id_viaggio)==0){
        currNodo->viaggio.km += km;
        currNodo->viaggio.costo += costo;
        return;}
      currNodo = currNodo->succ;
    }

    //id viaggio non esiste,
    TViaggio viaggio;
    char  targa[9];
    printf("inserisci la targa:\n");
    scanf("%s", targa);
    strcpy(viaggio.id_viaggio,id_viaggio);
    strcpy(viaggio.targa,targa);
    viaggio.km = km;
    viaggio .costo = costo;
    ListaAggiungi(lista,  viaggio);
}
/*
3. Data una targa, stampa il totale dei km percorsi ed il costo medio per km di tutti i viaggi ad essa associati
*/
void TotaleVeicolo(PNodoLista lista,
		  char* targa, float* totkm, float* costomedio)
{
  // ... da completare a cura dello studente ...
  *totkm = 0.0;
  *costomedio = 0.0;

  while (lista != NULL){
      if (strcmp(lista->viaggio.targa,targa)==0){
        *totkm = lista->viaggio.km;
        *costomedio = lista->viaggio.costo/lista->viaggio.km;
        printf("km totali: %f\n",*totkm);
        printf("costo medio: %f\n",*costomedio);
        return;
      }
      lista = lista->succ;
  }
  printf("Targa non trovata!\n");
  return;
}


int Menu()
{
  int scelta;

  printf("* M E N U *\n"
	 "1 - CaricaViaggi\n"
	 "2 - AggiungiViaggio\n"
	 "3 - TotaleVeicolo\n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaLista(PNodoLista lista)
{
  PNodoLista p;

  while (lista != NULL)
    {
      p = lista;
      lista = lista->succ;
      free(p);
    }
}

int main(void)
{
  PNodoLista lista;
  int        scelta;
 // allocare le variabili necessarie...
  int risultato,km;
  float costo, totkm, costomedio;
  char  id_viaggio[5];
  char  targa[9];


  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
	// Invocare la funzione CaricaViaggi e visualizzare un messaggio in caso di errore
      risultato = CaricaViaggi(&lista, NOME_FILE);
      if (risultato == 0)
        printf("Errore nel caricamento dati!\n");
	break;

      case 2:
	// Invocare la funzione AggiungiViaggio, caricando prima da tastiera i valori da passare come parametri
      printf("inserisci id viaggio:\n");
      scanf("%s", id_viaggio);
      printf("inserisci il numero di km:\n");
      scanf("%d", &km);
      printf("inserisci il costo del viaggio:\n");
      scanf("%f", &costo);
      AggiungiViaggio(&lista,id_viaggio, km, costo);
	break;

      case 3:
	// Invocare la funzione TotaleVeicolo, acquisendo preventivamente la targa da tastiera
	// Visualizzare km totali e costo medio per km
      printf("\n inserisci la targa:\n");
      scanf("%s", targa);
      TotaleVeicolo(lista, targa, &totkm, &costomedio);
	break;
      }

  } while (scelta != 0);

  DisallocaLista(lista); // passare il parametro opportuno

  return 0;
}