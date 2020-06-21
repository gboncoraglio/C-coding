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


#include ... // Includere gli header di libreria necessari

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

/* 
1. CaricaViaggi: carica l'elenco dei viaggi effettuati dalla flotta (lettura del file; ogni id viaggio è presente solo una volta nel file) in una lista di viaggi
  Restituisce 1 se l'operazione va a buon fine, 0    altrimenti.
*/
int CaricaViaggi(PNodoLista* plista, char* nome_file)
{
  // ... da completare a cura dello studente ...
}

/* 
 2. AggiungiViaggio: dato un id viaggio, km e costo, se l'id esiste già in lista si sommano ai valori già presenti in lista, 
	in caso contrario inserisce un nuovo viaggio nella lista (fornendo da tastiera in tal caso la targa)
*/
void AggiungiViaggio(PNodoLista* lista,
		   char* id_viaggio, int km, float costo)
{
    // ... da completare a cura dello studente ...
}

/*
3. Data una targa, stampa il totale dei km percorsi ed il costo medio per km di tutti i viaggi ad essa associati
*/
void TotaleVeicolo(PNodoLista lista,
		  char* targa, float* totkm, float* costomedio)
{
  // ... da completare a cura dello studente ...
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

  
  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
	// Invocare la funzione CaricaViaggi e visualizzare un messaggio in caso di errore
	break;

      case 2:
	// Invocare la funzione AggiungiViaggio, caricando prima da tastiera i valori da passare come parametri
	break;

      case 3:
	// Invocare la funzione TotaleVeicolo, acquisendo preventivamente la targa da tastiera
	// Visualizzare km totali e costo medio per km
	break;
      }
    
  } while (scelta != 0);

  DisallocaLista(...); // passare il parametro opportuno
  
  return 0;
}