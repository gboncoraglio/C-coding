/*
Sviluppo di applicazione in ANSI C per gestire i punti fedeltà di un
supermercato.

Su un archivio (allegato all'attività 'spesa.txt') è memorizzato lo
storico degli acquisti dei clienti di un supermercato
(transazioni). L'archivio è un file di testo in cui ogni riga riporta,
separati da spazio, le seguenti informazioni: codice cliente, data,
importo della spesa, saldo punti. Ogni 10 euro di spesa, il cliente
guadagna 1 punto fedeltà. Il cliente, a fronte di una spesa minima di
50 euro utilizzarà 50 punti fedeltà per ricevere uno sconto di 5 euro
sul totale della spesa. I saldo punti verrà aggiornato in base
all'importo effettivamente pagato. E' possibile utilizzare al più 50
punti per transazione.

Alcuni esempi:

1) Saldo punti 30, Importo spesa 100 euro --> Importo pagato 100 euro, saldo punti 40

2) Saldo punti 200, Importo spesa 100 euro --> Importo pagato 95 euro, saldo punti 200-50+9=159


Implementare le seguenti funzioni:

1. CaricaStorico: carica lo storico in una lista di transazioni.

2. ServizioCassa: aggiunge una transazione alla lista delle
transazioni.

3. SpesaMensile: calcola l'importo mensile per spesa di un cliente

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funione.
*/


// #include ... // Includere gli header di libreria necessari
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE "spesa.txt"

typedef struct Transazione
{
  char  codice[8];
  char  data[11]; // nel formato gg/mm/aaaa
  float totale_euro;
  int   saldo_punti;
} TTransazione;

typedef struct NodoLista
{
  TTransazione      transazione;
  struct NodoLista* succ;
} TNodoLista;

typedef TNodoLista* PNodoLista;

/* ListaAggiungi inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int ListaAggiungi(PNodoLista* plista, TTransazione transazione)
{
  PNodoLista aux;

  aux = (PNodoLista)malloc(sizeof(TNodoLista));

  if (aux == 0)
    return 0;

  aux->transazione = transazione;
  aux->succ = *plista;

  *plista = aux;

  return 1;
}

/*
   1. CaricaStorico: carica lo storico in una lista di
   transazioni. Restituisce 1 se l'operazione va a buon fine, 0
   altrimenti.
*/
int CaricaStorico(PNodoLista* plista, char* nome_file)
{
  // ... da completare a cura dello studente ...
    TTransazione transazione;
    int risultato;
    FILE *fp;
    fp = fopen(nome_file,"r");
    if (fp==NULL) return 0;

   //caricamento dei dai nella lista
    // 1006    01/01/2019  30.89   178
    while (fscanf(fp, "%s %s %f %d\n", transazione.codice,transazione.data,&transazione.totale_euro,&transazione.saldo_punti) == 4){
        risultato = ListaAggiungi(plista, transazione);
        if (risultato == 0)
          return 0;
    }
    return 1;
}

/*
   2. ServizioCassa: aggiunge una transazione alla lista delle
   transazioni. Dato il codice_cliente, la data, e l'importo della
   spesa, viene aggiunta una nuova transazione in testa alla lista. Il
   campo saldo_punti della transazione aggiunta dovrà essere
   opportunamente aggiornato in base a quanto descritto nel testo del
   compito. Il saldo attuale del cliente è quello dell'ultima
   transizione effettuata dal cliente (quindi quella più vicina alla
   testa della lista).
*/
void ServizioCassa(PNodoLista* lista,
           char* codice_cliente, char* data, float importo)
{
    // ... da completare a cura dello studente ...
    PNodoLista currNodo = *lista;
    while (currNodo != NULL){
      if (strcmp(currNodo->transazione.codice, codice_cliente)==0)
        break;
      currNodo = currNodo->succ;
    }

    TTransazione transazione;
    strcpy(transazione.codice,codice_cliente);
    strcpy(transazione.data,data);


    //cliente NON trovato
    if (currNodo == NULL){
      transazione.saldo_punti = (int)importo/10;
    }
    else{      //cliente trovato
      int saldo = 0;
      if (currNodo->transazione.saldo_punti >= 50 && importo >= 5){
        saldo = currNodo->transazione.saldo_punti - 50;
        importo -= 5;
      }
      transazione.saldo_punti = saldo + (int)importo/10;
    }
    transazione.totale_euro = importo;
    ListaAggiungi(lista, transazione);
}


/*
3. SpesaMensile: calcola l'importo mensile per spesa di un
cliente. Dato il codice cliente, la funzione restituisce un array che
per ogni mese dell'anno riporta il totale degli importi per la spesa
effettuata da quel cliente.
*/
void SpesaMensile(PNodoLista lista,
          char* codice_cliente, float* spesa_per_mese)
{
  // ... da completare a cura dello studente ...
   for (int i = 0; i < 12; i++)
      spesa_per_mese[i] = 0;

    int giorno, mese, anno;
    while (lista != NULL){
      if (strcmp(lista->transazione.codice, codice_cliente)==0){
          sscanf(lista->transazione.data, "%d/%d/%d", &giorno, &mese,&anno);
          spesa_per_mese[mese] += lista->transazione.totale_euro;
      }
      lista = lista->succ;
    }
}


int Menu()
{
  int scelta;

  printf("* M E N U *\n"
     "1 - CaricaStorico\n"
     "2 - ServizioCassa\n"
     "3 - SpesaMensile\n"
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
  float      spesa_mensile[12];
  char       codice[8];
  char       data[11];
  float      importo;
  int risultato;
  float totale_somma = 0.0;


  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
    // Invocare la funzione CaricaStorico e visualizzare un messaggio in caso di errore
      risultato = CaricaStorico(&lista, NOME_FILE);
      if (risultato == -1)
        printf("Errore nel caricare il file nella lista!\n");
    break;

      case 2:
    // Acquisire il codice cliente, la data e l'importo
      printf("inserisci il codice cliente:\n");
      scanf("%s",codice);
      printf("inserisci la data:\n");
      scanf("%s",data);
      printf("inserisci l'importo\n");
      scanf("%f",&importo);
    // Invocare la funzione ServizioCassa
      ServizioCassa(&lista, codice, data, importo);
    break;

      case 3:
    // Acquisire il codice cliente
      printf("inserisci il codice cliente:\n");
      scanf("%s",codice);
    // Invocare la funzione SpesaMensile
      SpesaMensile(lista,codice, spesa_mensile);
    // Visualizzare l'importo totale della spesa per tutti i mesi dell'anno
      for (int i = 0; i < 12; i++)
        totale_somma += spesa_mensile[i];
      printf("totale somma spesa durante l anno: %f\n",totale_somma);
    break;
      }

  } while (scelta != 0);

  DisallocaLista(lista); // passare il parametro opportuno

  return 0;
}