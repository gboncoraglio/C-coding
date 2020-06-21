/*
Sviluppo di applicazione desktop in ANSI C per gestire la coda di accesso ad
un supercomercato durante l'emergenza COVID-19.
Ogni cliente inserisce un nickname, l'ora di arrivo nel formato "HH:MM", che viene salvato
in una coda.

Il gestore del supermercato attiva la funzione accetando l'ingresso dell'utente che viene
copiato nella lista delle persone entrate agggiungendo l'ora di inggresso

I dati dei clienti in attesa sono inialmente caricati dal file "archivio.dat"

implementare le seguenti funzioni:
1. carica_clienti_da_file
2. inserisci un nuovo cliente in coda
3. accetta n persone in ingresso estraendo i dati dalla coda ed inserendoli nella lista, ed inserisce un valore da 1
	a 5 che rappresenta un giudizio sul servizio di attesa
4. calcola il tempo medio di attesa

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define DIMENSIONE_STRINGA 128
#define NOME_ARCHIVIO "file.dat"

typedef struct s_cliente {
	char nickname[DIMENSIONE_STRINGA];
	char tempo_ingresso[8];
	char tempo_uscita[8];
	int giudizio;
} t_cliente;

typedef struct s_nodo_sequenza {
	t_cliente info;
	struct s_nodo_sequenza* successivo;
} t_nodo_sequenza;

typedef t_nodo_sequenza* t_lista_clienti;

typedef struct {
	t_nodo_sequenza* primo;
	t_nodo_sequenza* ultimo;
} t_coda_clienti;

// La funzione inserisce un elemento in testa alla lista passata come primo parametro e
// restituisce la lista modificata
t_lista_clienti lista_aggiungi(t_lista_clienti lista_clienti, t_cliente cliente) {
	t_nodo_sequenza* aux = (t_nodo_sequenza*)malloc(sizeof(t_nodo_sequenza));
	if (aux == 0)
		return NULL;
	aux->info = cliente;
	aux->successivo = lista_clienti;
	return aux;
}

// la funzione restituice vero se la coda e' vuota
int coda_vuota(t_coda_clienti coda) {
	return (coda.primo == NULL);
}
// La funzione inserisce un elemento in coda
void coda_aggiungi(t_coda_clienti* pt_coda, t_cliente cliente) {
	t_nodo_sequenza* aux = (t_nodo_sequenza*)malloc(sizeof(t_nodo_sequenza));
	if (aux == 0)
		return NULL;
	// aggiungere il codice necessario a completare l'aggiunta di
	// un elemento alla coda
}

// la funzione restituisce il primo elemento della coda. L'elemento non viene
// cancellato dalla coda.
// Se la coda è vuota restituisce NULL
t_cliente* coda_primo_elemento(t_coda_clienti coda) {
	if (coda_vuota(coda))
		return NULL;
	return &(coda.primo->info);
}

// la funzione cancella il primo elemento della coda.
void coda_cancella_elemento(t_coda_clienti* pt_coda) {
	t_nodo_sequenza* aux = pt_coda->primo;
	if (coda_vuota(*pt_coda))
		return;
	if (pt_coda->primo == pt_coda->ultimo)
		pt_coda->primo = pt_coda->ultimo = NULL;
	else
		pt_coda->primo = pt_coda->primo->successivo;

	free(aux);
}

// funzioni utili per il calclo del tempo
// la funzione converti_ora, data un tempo espresso nel formato "HH:MM" restituisce
// un valore intero che rappresenta i minuti passati dalla mezzanotte (ore 00:00)
int converti_ora(const char* tempo) {
	int ore, minuti;
	sscanf(tempo, "%d:%d", &ore, &minuti);
	return ore * 60 + minuti;
}
//
// la funzione carica i dati dal file passato come parametro e restituisce il
// numero di record letti
// lo studente implementi il corpo ella funzione
int carica_clienti_da_file(t_coda_clienti * pt_clienti, FILE* f) {
	t_cliente c;
	c.giudizio = 0;
	int contatore = 0;
	if (f == NULL)
		return 0;
	while (fscanf(f, "%s%s", c.nickname, c.tempo_ingresso) == 2) {
		coda_aggiungi(pt_clienti, c);
		++contatore;
	}
	return contatore;
}
// la funzione calcola il tempo medio di attesa dei clienti
// numero di record letti
// lo studente implementi il corpo della funzione
float calcolo_tempo_medio(t_lista_clienti clienti) {
	// da fare
}
// la funzione rstituisce un vettore in cui ogni elemento contiene la somma delle
// persone che hanno espresso un giudizio pari all'indice + 1
// Lo studente deve scegliere i parametri corretti ed implementare il corpo della funzione
void sommario_giudizi() {
	// da fare
}

int main(void) {
	int scelta;
	t_lista_clienti clienti_serviti = NULL;
	t_coda_clienti clienti_attesa = { NULL, NULL };
	FILE* file_archivio = NULL;
	int numero_clienti;
	char buffer[128];
	float tempo_medio;

	file_archivio = fopen(NOME_ARCHIVIO, "r");
	if (file_archivio == NULL) {
		printf("archivio non esistente, non caricato\n");
	}
	else {
		// lo studenti completi il codice inserendo i parametri attuali corretti
		numero_clienti = carica_clienti_da_file(/* inserire i parametri */);
		fclose(file_archivio);
		printf("Caricati %d clienti\n", numero_clienti);
	}
	do {
		printf("1. Inserimento cliente\n");
		printf("2. Accettazione clienti\n");
		printf("3. Calcolo tempo medio di attesa\n");
		printf("4. Sommario dei giudizi\n");
		printf("\n0. esci\n");
		printf(">>> ");
		scanf("%d", &scelta);
		switch (scelta) {
		case 1: // Inserimento cliente
			// inserire tutto il codice necessario a
			//	1. leggere i dati del cliente dalla console (inserire il valore "" nel campo tempo_uscita
			//	2. inserire il cliente in coda
			break;
		case 2: // Accettazione clienti
			// inserire tutto il codice necessario a
			//	1. inserire il numero di clienti da accettare (verificare che sia un valore > 0)
			//	2. inserire l'ora corrente
			//	3. estrarre i clienti dalla coda nell'ordine corretto
			//	4. aggiornare il cliente aggiungendo il valore dell'ora corrente e del giudizio dato
			//	5. inserire il cliente nella lista dei clienti serviti
			//	3. stampare il nickname
			break;
		case 3: // calcolo del tempo medio di attesa, nota che il supermercato non fa servizio notturno.
			// inserire tutto il codice necessario a chiamare la funzione calcolo_tempo_medio e
			// stampare il tempo medio di attesa dei clienti
			break;
		case 0: // programma terminato
			break;
		}
	} while (scelta != 0);
}
