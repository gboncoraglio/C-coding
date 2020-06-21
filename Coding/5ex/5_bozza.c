/******************************************************************************
Un archivio contiene i dati relativi ai film trasmessi su un canale telvisivo. I file sono di quattro generi
diversi: "COMMEDIA" "THRILLER" "MUSICAL" e "FANTSCIENZA".
L'archivio è costituito da un file testo in cui per ogni film sono memorizzati uno per ciscuna riga le
sguenti informazioni
- titolo del film - una stringa di 255 caratteri che include caratteri bianche
- una stringa contenente il genere
- una stringa contenente la data della prima proiezione nel formato aaaa-mm-gg
Attenzione per il genere nella lista verra memorizzato un codice intero. Vedere il codice
per la corrispondenza.
Scrivere un programma che consente di effettuare le seguenti operazioni
- caricamento dei dati in una lista ordinata rispetto alla data e stampa della lista
- ricerca del film più nuovo e piu vecchio
- estrazioni dei film di un dato genere

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define leng 226

/*struttura lista*/
typedef struct s{
    int genere; //0 per COMMEDIA, 2 per TRHILLER, 2 per MUSICAL e 3 per FANTSCIENZA
    char data[11]; //aaaa-mm-gg
    char titolo[leng];
}elemento;

typedef struct n{
    elemento info;
    struct n*next;
} nodo, *lista;

lista make_null_lista(){return NULL;}
int empty_list(lista l){return l==NULL;}
int cons (lista *pL,elemento E){
    return 0 ;
}
int inserimento_ordinamento(lista *pL, elemento E){
    return 0 ;
}
void stampa(lista L){
    while(L!=NULL){
        printf("%s\n",L->info.titolo);
        L = L->next;
    }
}

/*funzioni di servizio*/
int ritorna_indice(char *genere){
    if (strcmp(genere,"COMMEDIA")==0) return 0;
    if (strcmp(genere,"THRILLER")==0) return 1;
    if (strcmp(genere,"MUSICAL")==0) return 2;
    if (strcmp(genere,"FANTSCIENZA")==0) return 3;
    return -1;
}

char *ritorna_stringa(int indice){
    switch (indice){
        case 0:return "COMMEDIA";
        case 1:return "THRILLER";
        case 2:return "MUSICAL";
        case 3:return "FANTASCIENZA";
    }
    return "NoN";
}

int menu(){
    printf("1) questito1:carica e stampa\n");
    printf("2) questito2:ricerca film più nuovo e più vecchio\n");
    printf("3) questito3:film di un dato genenre\n");
}

/*quesito1*/
void quesito1(lista *pL){
    //INSERIRE CODICE QUESITO 1

}


/*quesito2*/
void quesito1(/*ARGOMENTI DELLA FUNZIONE*/){
    //INSERIRE CODICE QUESITO 2

}

/*quesito3*/
lista quesito2(/*ARGOMENTI DELLA FUNZIONE*/){
    //INSERIRE CODICE QUESITO 2

}



//main
int main (void){
    lista L=make_null_lista();
    int scelta=0;
    lista old, nuovo,result;
    char g[20];
    do {
        scelta =menu();
        switch (scelta){
            case 1: quesito1(&L);
                stampa(L);
                break;
            case 2: quesito2(/*ARGOMENTI DELLA FUNZIONE*/);
                printf("il film più vecchio e' %s\n", old->titolo);
                printf("il film più nuovo e' %s\n", nuovo->titolo);
                break;
            case 3: printf("inserisci il genere\n");
                scanf("%s",g);
                result=quesito3(/*AROGMENTI DELLA FUNZIONE);
                stampa(result);
        }
    } while (scelta!=0);
}




