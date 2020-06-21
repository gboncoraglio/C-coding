/*

Un’agenzia di un servizio corriere espresso vuole realizzare un programma per la gestione delle spedizioni. In particolare,
le richieste giornaliere di ritiro di pacchi da spedire sono inizialmente memorizzate in un file di testo (un esempio di file è fornito come allegato all'attivita').
Nel file ogni riga riporta, separati da spazio le seguenti informazioni:
- l'identificativo del mittente (stringa senza spazi)
- l'orario in cui è stata effettuata la richiesta (stringa in formato HH:MM)
- la sigla della provincia di destinazione (stringa)


Implementare un programma in ANSI C che contiene le seguenti funzioni:
1) lettura e caricamento dei dati contenuti nel file in una lista ordinata in base all'orario della richiesta. La funzione deve inoltre restituire il numero di elementi letti e caricati nella lista

2) funzione che restituisce il numero di spedizioni richieste nelle seguenti 3 fasce orarie: mattina (fino alle 11:59), pomeriggio (dalle 12:00 alle 17:59), sera (dopo le 18:00).

3) funzione che, fornita in ingresso una provincia, restituisca la lista delle spedizioni per quella provincia

Si implementi inoltre un main che richiami in maniera opportuna le funzioni sopra elencate, seguendo lo schema fornito nel codice.

La descrizione dettagliata di ogni funzione è riportata come commento immediatamente prima della definizione della funzione nello scheletro di programma fornito
*/

#include ...  // Includere gli header di libreria necessari


// Dichiarazione Struttura dati

typedef struct spedizione {
    char  mittente[32];
    char  orario[6]; //nel formato HH:MM
    char  provincia[3];
} TSpedizione;

typedef struct nodo {
    TSpedizione	info;
    struct nodo *next;
} TNodo;

typedef TNodo *TLista;


/* InserisciTestaLista
    inserisce un elemento in testa alla lista passata come primo parametro.
    Restituisce 1 se l'operazione va a buon fine, 0 altrimenti */
int InserisciTestaLista(TLista* lis, TSpedizione elem) {
    TLista paux;

    if ((paux = (TLista)malloc(sizeof(TNodo))) == NULL)
        return 0;

    paux->info = elem;
    paux->next = *lis;
    *lis = paux;

    return 1;
}

/* InserisciInListaOrdinata
    inserisce un elemento in lista in maniera ordinata rispetto al campo orario */
void InserisciInListaOrdinata(TLista* lis, TSpedizione elem) {

    if (*lis == NULL || strcmp((*lis)->info.orario, elem.orario) > 0)
        InserisciTestaLista(lis, elem);
    else
        InserisciInListaOrdinata(&((*lis)->next), elem);
}

/*
   1. CaricaDaFile:
   carica da file la richieste in una lista di spedizioni (ordinata in base all'orario).
   Restituisce il numero di elementi letti da file e caricati nella lista
*/
int CaricaDaFile(TLista *plis, char *nomefile) {
  // ... corpo della funzione da completare a cura dello studente ...
}

/*
    2. NumeroSpedizioni
    funzione che restituisce il numero di spedizioni richieste nelle fasce orarie: mattina (fino alle 11:59), pomeriggio (dalle 12:00 alle 17:59), sera (dopo le 18:00). Tali risultati vengono restituiti in un opportuno vettore di tre elementi:0 mattina, 1 pomeriggio, 2 sera.
*/
void NumeroSpedizioni(/* inserire i parametri */) {
   // ... corpo della funzione da completare a cura dello studente ...
}

/*
    3. SpedizioniProvincia:
    funzione che prevede come parametri di ingresso: la lista delle spedizioni, ed una provincia.
    Essa deve restituire la lista delle spedizioni per la provincia data
*/
TLista SpedizioniProvincia(TLista lis, char* prov) {
  // ... corpo della funzione da completare a cura dello studente ...
}

/*******menu' di scelta *********/
int Menu() {
  int scelta;

  printf("*** M E N U ***\n"
	 "1 - Carica dati da file\n"
	 "2 - Numero spedizioni per fasce orarie\n"
	 "3 - Spedizioni per provincia\n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

/*** funzione di utilità per visualizzare i dati della lista ***/
void VisualizzaLista(TLista lis) {

  // ... corpo della funzione da completare a cura dello studente ...

}


/****** main *********/
int main(void) {
  TLista listaspedizioni;
  int scelta;

  /* inserire le ulteriori variabili necessarie */


  do {
    scelta = Menu();

    switch (scelta) {
      case 1:
          // Acquisire il nome del file
          // Invocare la funzione CaricaDaFile e visualizzare il numero di elementi caricati o un messaggio in caso di errore
          // Visualizzare i dati caricati nella lista

	    break;

      case 2:
          // Invocare la funzione NumeroSpedizioni
          // Visualizzare i dati restituiti dalla funzione

	    break;

      case 3:
          // Acquisire la provincia
	      // Invocare la funzione SpedizioniProvincia
          // Visualizzare i dati della lista restituita dalla funzione

	    break;
     }

  } while (scelta != 0);

  // disallocare la lista

  return 0;
}