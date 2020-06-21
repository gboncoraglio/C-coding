/******************************************************************************
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


#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define DIMENSIONE_STRINGA 128
#define NOME_ARCHIVIO "archivio.dat"

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
//---------

// la funzione restituice vero se la coda e' vuota
int coda_vuota(t_coda_clienti coda) {
	return (coda.primo == NULL);
}
// La funzione inserisce un elemento in coda
void coda_aggiungi(t_coda_clienti* pt_coda, t_cliente cliente) {
	t_nodo_sequenza* aux = (t_nodo_sequenza*)malloc(sizeof(t_nodo_sequenza));
	if (aux == 0) return;
	aux->successivo = NULL;
	aux->info = cliente;
	if(coda_vuota(*pt_coda)) pt_coda->primo = pt_coda->ultimo = aux;
	else {
	    pt_coda->ultimo->successivo=aux;
	    pt_coda->ultimo= aux;
	}
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
	int num=0;
	int somma=0;
	int tempoArrivo;
	int tempoUscita;
	while (clienti!=NULL){
	    tempoArrivo = converti_ora(clienti->info.tempo_ingresso);
	    tempoUscita = converti_ora(clienti->info.tempo_uscita);
	    somma += tempoUscita-tempoArrivo;
	    num++;
	    clienti = clienti->successivo;
	}
	if (num==0) return 0;
	return ((float)somma)/num;
}


int main(void) {
	int scelta,n;
	int ore, minuti;
	t_lista_clienti clienti_serviti = NULL;
	t_coda_clienti clienti_attesa = { NULL, NULL };
	FILE* file_archivio = NULL;
	int numero_clienti;
	char buffer[128];
	float tempo_medio;
	t_cliente cliente_x;

	file_archivio = fopen(NOME_ARCHIVIO, "r");
	if (file_archivio == NULL) {
		printf("archivio non esistente, non caricato\n");
	}
	else {
		numero_clienti = carica_clienti_da_file(&clienti_attesa, file_archivio);
		fclose(file_archivio);
		printf("Caricati %d clienti\n", numero_clienti);
	}
	do {
		printf("1. Inserimento cliente\n");
		printf("2. Accettazione clienti\n");
		printf("3. Calcolo tempo medio di attesa\n");
		printf("\n0. esci\n");
		printf(">>> \n");
		scanf("%d", &scelta);
		switch (scelta) {
		case 1:
			printf("\n inserisci il tuo nickname");
			scanf("%s",cliente_x.nickname);
			do {
			    printf("\n inserisci il tempo di ingresso");
			    scanf("%s",cliente_x.tempo_ingresso);
			    //controllo correttezza della stringa
	            sscanf(cliente_x.tempo_ingresso, "%d:%d", &ore, &minuti);
			} while (ore<=0 || ore>24 || minuti<=0 || minuti>59);
			strcpy(cliente_x.tempo_uscita,"");
            cliente_x.giudizio=0;
			coda_aggiungi(&clienti_attesa,cliente_x); //inserimento cliente in coda
			numero_clienti++;
			break;
		case 2:
		    //acquisizione del numero di clienti da accettare
			do {
			    printf("inserisci il numero di clienti che possono entrare al supermercato");
			    scanf("%d", &n);
			} while(n<=0);
			//verifica se nella coda ci sono abbastanza clienti
			if (n>numero_clienti) n = numero_clienti;
			for (int i=0;i<n;i++){
			    //trasferimento di num elementi dalla coda di attesa alla lista dei clienti serviti
			    cliente_x = *coda_primo_elemento(clienti_attesa);
			    coda_cancella_elemento(&clienti_attesa);
			    do {
			        printf("\n inserisci il tempo di uscita di %s", cliente_x.nickname);
			        scanf("%s",cliente_x.tempo_uscita);
			        //controllo correttezza della stringa
	                sscanf(cliente_x.tempo_uscita, "%d:%d", &ore, &minuti);
			    } while (ore<=0 || ore>24 || minuti<=0 || minuti>59);
			    do {
			        printf("\n inserisci il tuo giuszio 1-5");
			        scanf("%d",&cliente_x.giudizio);  //controllo che sia un valore compreso fre 1 e 5
			    } while (cliente_x.giudizio<1 || cliente_x.giudizio>5);
			    clienti_serviti= lista_aggiungi(clienti_serviti,cliente_x);
			    printf("il cliente entrato è %s", cliente_x.nickname);
			    numero_clienti--;
			}
			break;
		case 3: // calcolo del tempo medio di attesa, nota che il supermercato non fa servizio notturno.
			tempo_medio=calcolo_tempo_medio(clienti_serviti);
			printf("tempo medio attesa = %f", tempo_medio);
			break;
		case 0: // programma terminato
			break;
		}
	} while (scelta != 0);
}

