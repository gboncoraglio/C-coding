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
#define _CRT_SECURE_NO_WARNINGS
#define leng 226

/*struttura lista*/
typedef struct s{
    int genere; //0 per COMMEDIA, 1 per TRHILLER, 2 per MUSICAL e 3 per FANTSCIENZA
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
    lista aux = (lista)malloc(sizeof(nodo));
    if (aux == NULL)return 1;
    aux->info.genere = E.genere;
    strcpy(aux->info.data, E.data);
    strcpy(aux->info.titolo, E.titolo);
    aux->next = *pL;
    *pL = aux;
    return 0 ;   
}
int inserimento_ordinamento(lista *pL, elemento E){
    int x=0;

    if (*(pL)==NULL||strcmp(E.data,(*pL)->info.data) < 0) {
        cons(pL, E);

    }
    else x=inserimento_ordinamento(&(*pL)->next, E);
    if (x == 1)return 1;
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
    if (strcmp(genere,"FANTASCIENZA")==0) return 3;
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

int menu(void){
    int x;
    printf("1) questito1:carica e stampa\n");
    printf("2) questito2:ricerca film più nuovo e più vecchio\n");
    printf("3) questito3:film di un dato genenre\n");
    scanf("%d", &x);
    return x;
}

/*quesito1*/
void quesito1(lista* pL) {
    //INSERIRE CODICE QUESITO 1
    FILE* f;
    char nomefile[15];
    char genere[13];
    elemento temp;
    printf("inserire nome del file");
    scanf("%s", nomefile);
    f = fopen(nomefile, "r");
    if (f == NULL) { printf("File non trovato"); return; }
    while (feof(f)==0) {
        fscanf(f, "%s\n%s\n", genere, temp.data);
       
        temp.genere = ritorna_indice(genere);
        if (temp.genere == -1) { printf("genere non previsto letto da file"); return; }
        fgets(temp.titolo, leng, f);
        if (inserimento_ordinamento(pL, temp) == 1) {
            printf("Errore caricamento dati");
            break;
        }
       
    }
 fclose(f);

}


/*quesito2*/
void quesito2(lista*vecchio,lista*nuovo,lista in){
    //ricerca del film più nuovo e piu vecchio
    //INSERIRE CODICE QUESITO 2
    *nuovo = *vecchio = make_null_lista();
    *vecchio = in;
    while (in->next != NULL) {
        in = in->next;
    }
    *nuovo = in;
}

/*quesito3*/
lista quesito3(lista in,char *genere){
   // estrazioni dei film di un dato genere
    //INSERIRE CODICE QUESITO 3
    lista out=make_null_lista();
    int int_genere = ritorna_indice(genere);
    while (in != NULL) {
        if (in->info.genere == int_genere) {
            cons(&out, in->info);
        }

        in = in->next;
    }
    return out;
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
            case 2: quesito2(&old,&nuovo,L);
                printf("il film più vecchio e' %s\n", old->info.titolo);
                printf("il film più nuovo e' %s\n", nuovo->info.titolo);
                break;
            case 3: printf("inserisci il genere\n");
                scanf("%s",g);
                result=quesito3(L,g);
                stampa(result);
        }
    } while (scelta!=0);
}
    



