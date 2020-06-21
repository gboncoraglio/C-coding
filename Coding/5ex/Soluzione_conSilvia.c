/******************************************************************************
Un archivio contiene i dati relativi ai film trasmessi su un canale telvisivo. I file sono di quattro generi
diversi: "COMMEDIA" "THRILLER" "MUSICAL" e "FANTASCIENZA".
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

/*
  elem = 5
  HEAD -> 7
  nuova_pallina = 5 -> 7


  HEAD -> 5 -> 7

*/
int cons (lista *pL,elemento E){
    lista nuova_pallina = (lista)malloc(sizeof(nodo));
    if (nuova_pallina == NULL)
        return -1;

    nuova_pallina->info = E;
    nuova_pallina->next = *pL;
    *pL = nuova_pallina;
    return 0 ;
}

/*
  elem = 5
  HEAD -> 2 -> 4 -> 7

  elem = 5
  HEAD -> 4 -> 7

  elem = 5
  HEAD -> 7

*/


/*
 strcmp(str1,str2)  --> = 0 se str1 == str2
                        >0  se str1 > str2
                        < 0 se str1 < str2
*/
int inserimento_ordinamento(lista *pL, elemento E){
    int risultato = 0;
    // lista --> 2018/02/23
    // E ------> 2018/03/20
    if (*pL == NULL || strcmp(  E.data, (*pL)->info.data ) < 0 )
        risultato = cons( pL,E);
    else
        risultato = inserimento_ordinamento( &((*pL)->next) ,E );
    return risultato;
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

int menu(){
    printf("1) questito1:carica e stampa\n");
    printf("2) questito2:ricerca film più nuovo e più vecchio\n");
    printf("3) questito3:film di un dato genenre\n");
    int scelta;
    scanf("%d",&scelta);
    return scelta;
}

/*quesito1*/
void quesito1(lista *pL){
    //INSERIRE CODICE QUESITO 1
    // FILE* f = NULL;
    FILE* f;
    elemento E;
    char nomefile[30];
    char g[20];
    int risultato;

    printf("Dimmi il nome del file!!!!!\n");
    scanf("%s",nomefile);
    f = fopen(nomefile,"r");
    if (f == NULL){
        printf("File not found!\n");
        return;
    }

    // COMMEDIA
    // 2018/02/23
    // OLD MAN & THE GUN
    while (fscanf(f, "%s\n%s\n", g,E.data ) == 2  ){
            E.genere =  ritorna_indice(g);
            fgets(E.titolo,leng,f);
            risultato = inserimento_ordinamento(pL, E);
            if (risultato == -1){
                printf("Errore durante l inserimento\n");
                return;}
    }
    fclose(f);
}


/*quesito2*/
void quesito2(lista L, lista *old, lista *new) {
    //INSERIRE CODICE QUESITO 2
    *old = NULL;
    *new = NULL;

    *old = L;
    while (L->next != NULL)
        L = L->next;
    *new = L;
}

/*quesito3*/
lista quesito3(lista L,char *genere){
    //INSERIRE CODICE QUESITO 2
    lista result = NULL;
    int genere_int = ritorna_indice(genere);

    while(L != NULL){
        if (L->info.genere == genere_int)
            cons(&result,L->info);
        L = L->next;
    }
    return result;
}



//main
int main (void){
    lista L=make_null_lista();
    // lista L= NULL;

    int scelta=0;
    lista old, nuovo,result;
    char g[20];
    do {
        scelta =menu();
        switch (scelta){
            case 1: quesito1(&L);
                stampa(L);
                break;
            case 2: quesito2(L,&old, &nuovo);
                printf("il film più vecchio e' %s\n", old->info.titolo);
                printf("il film più nuovo e' %s\n", nuovo->info.titolo);
                break;
            case 3: printf("inserisci il genere\n");
                scanf("%s",g);
                result=quesito3(L,g);
                stampa(result);
                break;
        }
    } while (scelta!=0);
}




