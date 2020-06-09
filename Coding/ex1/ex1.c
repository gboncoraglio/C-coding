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

#define NOME_ARCHIVIO "5_file.txt"

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
    lista aux = (lista)malloc(sizeof(nodo));
    //Non ha create il nodo
    if (aux == NULL)
        return -1;

    aux->info = E;
    aux->next = *pL;
    *pL = aux;
    return 0;
}
int inserimento_ordinamento(lista *pL, elemento E){
    int res;
    if (*pL == NULL ||  strcmp(E.data, (*pL)->info.data) < 0  )   //if Return value < 0
                                                              //then it indicates str1 is less than str2.
        res = cons(pL, E);
    else
        inserimento_ordinamento( &( (*pL)->next ), E );
    return res;
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
    scanf("%d", &scelta);
    return scelta;
}

/*quesito1*/
void quesito1(lista *pL){
    //INSERIRE CODICE QUESITO 1
    FILE* f;
    elemento E;
    int res;
    char g[20];
    f = fopen(NOME_ARCHIVIO, "r");

    // char data[11];
    //NO
    // data = "2018/02/23"
    // YES
    // strcpy(data, "2018/02/23");

    while (fscanf(f, "%s\n%s\n", g, E.data) == 2) {
        fgets (E.titolo, leng, f);
        E.genere =  ritorna_indice(g);
        res = inserimento_ordinamento(pL,E);
        if (res == -1){
            printf("Lista non aggiornata correttamente\n");
            return;}
        // printf("%s\n",E.data);
        // printf("%d\n",E.genere);
        // printf("%d\n",strcmp(E.data, data));
        // inserimento_ordinamento(pL,E);
    }

}


/*quesito2*/
void quesito2(lista L,lista *old,lista *new){
    //INSERIRE CODICE QUESITO 2
    *old = NULL;
    *new = NULL;

    *old = L;
    //itera in tutta la lista
    while(L->next!=NULL){
        L = L->next;
    }
    *new = L;
}

/*quesito3*/
lista quesito3(lista L, char *genere){
    lista result  = make_null_lista();
    int genere_int  = ritorna_indice(genere);

    while(L != NULL){
        if (L->info.genere == genere_int)
            cons (&result,L->info);
        L = L->next;
    }
    return result;
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
            case 2: quesito2(L,&old, &nuovo);
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
