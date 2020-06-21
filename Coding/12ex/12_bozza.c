/*
Sviluppare una applicazione desktop in ANSI C che permetta di gestire una coda di attesa con priorità.
La struttura è composta da un vettore che contiene due code, ognuna delle code è caratterizzata da un
livello di priorità crescente (la coda 0 è prioritaria).
Gli elementi vengono estratti in base al seguente algoritmo:
1. Gli elementi sono sempre estratti dalla coda con priorità maggiore (coda 0) tranne quando questa è vuota,
	in questo caso vengono estratti dalla coda a priorità più bassa

Implementare le seguenti funzioni
1. caricamento dei dati da un file di ingresso
2. estrazione del primo elelemnto secondo l'algoritmo descritto
3. conteggio degli elementi presenti in ognuna delle due code
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define VERO	1
#define FALSO	0

#define DIMENSIONE_STRINGA	128
// Definizioni relative alla partita

typedef struct s_nodo {
	char nome[DIMENSIONE_STRINGA];
	struct s_node* successivo;
} t_elemento, * pt_elemento;

typedef struct {
	pt_elemento primo;
	pt_elemento ultimo;
} t_coda;

// coda_vuota
//	verifica se la coda è vuota
//	return:		retistuisce vero se la coda è vuota
int coda_vuota(t_coda c) {
	return (c.primo == NULL) ? VERO : FALSO;
}
// coda_aggiungi
//	La funzione inserisce un elemento in coda
//	parametri:	coda da modificare, nome da inserire
//	return:		VERO se corretta, FALSO altrimenti
// Lo studente implementi la funzione
int coda_aggiungi(t_coda* pc, const char *n) {
	printf("\n== NON IMPLEMENTATA ==\n");
}
// coda_primo
//	La funzione restituisce il puntatore al primo elemento
//	parametri:	coda
//	return:		primo elemento o NULL se vuota
char * coda_primo(t_coda c) {
	if (coda_vuota(c))
		return NULL;
	return c.primo->nome;
}
// coda_rimuovi
//	La funzione rimuove il primo elemento della coda
//	parametri:	coda
//	return:		void
void coda_rimuovi(t_coda* pc) {
	if (coda_vuota(*pc))
		return;
	pt_elemento aux = pc->primo;
	if (pc->primo == pc->ultimo)
		pc->primo = pc->ultimo = NULL;
	else
		pc->primo = pc->primo->successivo;
	free(aux);
}
// 1. caricamento dei dati da un file di ingresso
//	carica_dati
//		parametri:	struttura dati, nome del file
//		return:		void
// Lo studente completi L'iimplementazione della funzione
void carica_dati(t_coda c[], const char* nome_file) {
	FILE* f;
	char nome[DIMENSIONE_STRINGA];
	int priorita;
	if ((f = fopen(nome_file, "r")) == NULL) {
		printf("Errore aprendo %s\n", nome_file);
		return;
	}
	printf("\n== NON IMPLEMENTATA ==\n")

}
// funzione estrai_archivio
//	parametri:	strtuttura dati
//	return:		1 se riuscito, 0 se la coda è vuota
// Lo studente implementi la funzione
int estrai_archivio(t_coda coda_attesa[], char * nome) {
	printf("\n== NON IMPLEMENTATA ==\n")

}
// conteggio_elementi
//	il vettore deve essere allocato nella funzione
//	parametri:	struttura dati,
//	return:		vettore che contiene il risultato
// Lo studente implementi la funzione
int* conteggio_elementi( /* lo studente definisca il parametro corretto */) {
	printf("\n== NON IMPLEMENTATA ==\n")

}
int main(void) {
	int selezione;
	char buffer[DIMENSIONE_STRINGA];
	t_coda coda_attesa[2] = { {NULL,NULL} };
	int contatore = 0;

	int numero_elementi;
	int* risultato = NULL;
	do {
		printf("1. caricamento dei dati da un file di ingresso\n");
		printf("2. estrazione del primo elelemnto secondo l'algoritmo descritto\n");
		printf("3. conteggio degli elementi presenti in ognuna delle due code\n");
		printf("0. fine\n");
		printf(">>> ");
		scanf("%d", &selezione);
		switch (selezione) {
		case 0:
			printf("fine programma\n");
			break;
		case 1:
			// Lo studente implementi quanto necessario a svolgere le seguenti operazioni
			// 1. richiesta del nome del file da cui caricare i dati
			printf("Nome del file: ");
			scanf("%s", buffer);
			// 2. chiamata della funzione carica_dati
			// da completare
			break;
		case 2:
			// Scrivere il codice necessario ad implementare l'estrazione di un elementi dalla
			// struttura dati.
			// 1.	implementare quanto necessario ad acquisire il numero di elementi
			//		da estrarre
			// 2.	scrivere il codice per estrarre il numero di elementi richiesto e stamparne
			//		il contenuto liberando le risorse non più necessarie
			printf("Inserire il numero di elementi da estrarre: ");
			scanf("%d", &numero_elementi);
			// da completare
			break;
		case 3:
			// Lo studente implementi quanto necessario a chiamare la funzione conteggio elementi
			// stampare il risultato e deallocare se necessario
			// da completare
			break;
		}
	} while (selezione != 0);
}