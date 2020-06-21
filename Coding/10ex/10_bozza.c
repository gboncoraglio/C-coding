/******************************************************************************
Implementare una applicazione per la gestione del “carrello” in un sistema di acquisto online.
La struttura dati da utilizzare è una lista di articoli, ove ogni articolo è caratterizzato dai seguenti attributi (il codice è univoco):
 Codice (intero)
 Valore (in euro)
 Quantità (intero senza segno)
La lista di articoli è ordinata in base al campo Valore.
Implementare le seguenti funzioni:
1. creziaone di una lista ordinata leggendo i dati dal file testo che contiene le informazioni 
una per riga e stampa del contenuto della lista.
2. cambio della quantita per un articolo selezionato attraverso il codice
3. funzione che restituisce la lista degli articoli la cui quantità è minori di un valore fornito
da console
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define LM 15

/*struttura lista */
typedef struct a{
    int codice, quantita;
    float valore;
} articolo;

typedef struct n{
    articolo info;
    struct n*next;
} t_nodo, *t_lista;

void crea_lista_vuota(t_lista *pL){
    *pL=NULL;
}

int inserimento_ordinato(t_lista *pL, articolo A){
    t_lista aux,p,q;
    aux =(t_lista)malloc(sizeof(t_nodo));
    if (aux==NULL) return 0;
    aux->info=A;
    aux->next =NULL;
    if (*pL==NULL || (*pL)->info.valore>A.valore) {
        //inserimemtno in testa
        aux->next = *pL;
        *pL = aux;
    }
    else {
     //inseirmento dell'elemnento in un pssto diverso dal primo
    return 1;
}

//cerca un elemento dato il codice, e restituisce il puntatore all'elemento
t_lista cerca(t_lista L, int codice ){
    if (L==NULL) return NULL;
    if (L->info.codice == codice) return L;
    return cerca(L->next,codice);
}

void stampa(t_lista L){
    printf("\n");
    while (L!=NULL){
        printf("codice = %d, valore = %f, quantita =%d \n",L->info.codice,L->info.valore,L->info.quantita);
        L=L->next;
    }
}

/*funzioni di utilita*/
int menu(void) {
    int scelta;
    printf("\n 1) esegui quesito 1");
    printf("\n 2) esegui quesito 2");
    printf("\n 3) esegui quesito 3");
    printf("\n 0) esci dal programma");
    scanf("%d", &scelta);
    return scelta;
}


//definizione dei quesiti 
/*creziaone di una lista ordinata leggendo i dati dal file testo.*/
void quesito1(//argomenti della funzione){
    char nomefile [LM], parola[LM];
    articolo A;
    FILE *fp;
    printf("\n inserisci il nome del file ");
    scanf("%s",nomefile);
    fp = fopen(nomefile,"r");
    if (fp==NULL) return;
   //caricamento dei dai nella lisra
    }
}

/*cambio della quantita per un articolo selezionato attraverso il codice, restituisce 0
se l'articolo non è stato trovato*/


int quesito2(/*ardomenti della funzione**/){
        //inserire qui il codice
}

/*funzione che restituisce la lista degli articoli la cui quantità è minori di un valore fornito
da console*/

t_lista quesito3(t_lista L, int Q){
   //inserire qui il codice
}

//main
int main(void) {
    t_lista Archivio;  //Archivio è la lista in cui verranno caricati i dati del file
    int scelta = 0, codice, Q;
    t_lista result3; //lista da utilizzare come risultato del quesito 3
    crea_lista_vuota(&Archivio);
    do {
        scelta = menu();
        switch (scelta) {
        case 1: //inserire il codice del caso 1
        case 2: printf("inserisci il codice dell'articolo di cui vuoi modificare la quantita");
            scanf("%d",&codice);
            printf("inserisci il valore di cui vuoi modificare la quantita");
            scanf("%d",&Q);
            //stampare se l'aggiornamento è avvenuto con successo
            //utilizzado la funzione quesito2
            break;
        case 3: ; printf("inserisci la quantita limite");
            scanf("%d",&Q);
            result3 = //chiamata della funzione quesito3;
            stampa(result3);
        }
    } while (scelta != 0);
}
