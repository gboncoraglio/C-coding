/*
Progettare ed implementare in ANSI C un programma che permetta di gestire 4 code di attesa in uno studio medico. Ogni singola coda gestisce i pazienti in attesa di uno dei medici, i medici sono identificati dai numeri 0, 1, 2, 3.
Ogni paziente è identificato dai seguenti attributi
- Codice Fiscale
- Cognome (senza spazi bianchi)
- Nome (senza spazi bianchi)
- Urgenza (valore booleano implementato con gli interi)
Progettare la struttura dati adatta a mantenere in memoria centrale le informazioni utilizzando
strutture e puntatori per la coda;
Scrivere un opportuno main in cui sia previsto un menù di scelta delle operazioni richieste.
Tutti i valori necessari al funzionamento devono essere passati utilizzando parametri,
non è permesso l’uso di variabili globali;
Il programma deve prevedere le seguenti funzionionalita:
1) funzione Carica che legga dal file Elenco.txt i dati dei pazienti e li inserisca nelle code appropriate;
2) funzione StampaCada di Attesa, che dato il codice di un medico stampa l'elenco dei clienti in coda
3) funzione che dato il medico tramite il suo codice numerico (0, 1, 2, 3) estrae il primo paziente
in attesa e lo restituisce al main all’interno del quale viene stampato
4) Scrivere una funzione che restituisca in un vettore il numero di pazienti presenti in ogni lista
(l’elemento di indice 0 contiene il numero di pazienti nella coda del medico 0,
l’elemento di indice 1 contiene il numero di pazienti nella coda del medico 1, ecc.)
*/
#include <stdio.h>
// #include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define strLL 20
#define nMEdici 4
#define NOMEFILE "2_file.txt"

/*definizione tipo paziente*/
typedef struct paz{
        char CF[17];
        char nome[strLL],cognome[strLL];
        int urgenza; //0 non urgente, 1 urgente
}paziente;

void stampaPaziente(paziente p){
    printf("%s  %s %s  %s\n",p.CF,p.nome,p.cognome,p.urgenza?"urgente":"non urgente");
}

/*definizione coda e funzioni coda*/
typedef struct nd{
    paziente info;
    struct nd* successivo;
}nodoCoda;

typedef struct c{
    nodoCoda *primo,*ultimo;
}coda;

coda creaCodaVuota(){
    //crea coda vuota
    // coda c = {NULL,NULL};
    coda c;
    c.primo = c.ultimo = NULL;
    return c;
}

int testCodaVuota(coda c){
    //verifica se una coda è vuota
    return c.primo==NULL;
}

coda EliminaCoda(coda c){
    //elimina un elemento dalla coda restituendo la coda senza il primo elemento
    nodoCoda *aux = NULL;
    if (testCodaVuota(c)) return c;

    aux = c.primo;
    if (c.primo==c.ultimo)
        c.primo=c.ultimo=NULL;
    else
        c.primo = c.primo->successivo;

    free (aux);
    return c;
}

paziente PrimoInCoda(coda c){
    //restituisce il primo elemento della cosa
    if (!testCodaVuota(c)) return c.primo->info;
}

coda inCoda(coda c,paziente p){
    //inserisce un elemento in coda;
    nodoCoda * aux;
    aux = (nodoCoda*)malloc(sizeof(nodoCoda));
    if (aux==NULL) return c;
    aux->info=p;
    aux->successivo=NULL;

    // if (testCodaVuota(c))
    if (c.primo==NULL)
        c.primo=c.ultimo=aux;
    else {
        c.ultimo->successivo = aux;
        c.ultimo = aux;
    }
    return c;
}

int size(coda c){
    //calcola e restituisce la lunghezza di una coda
    int i=0;
    nodoCoda *l = c.primo;
    while(l!=NULL) {
        l=l->successivo;
        i++;
    }
    return i;
}

/*funzioni di utilita*/
int menu(){
    int x;
    printf("\n 1: Carica file nel vettore di code\n");
    printf("\n 2: Stampa Coda di attesa di un medico\n");
    printf("\n 3: Estrae primo paziente in attesa di un medico e lo stampa\n");
    printf("\n 4: Contolla e stampa le lunghezze delle code\n");
    scanf("%d",&x);
    return x;
}

void stampaVettore(int *vettore, int n){
    for(int i=0; i<n;i++)
        printf("\n elemento %d = %d",i,vettore[i]);
}

int leggiCodiceMedico(){
    int codice;
    //leggi un codice del medico da tastiera verificando che sia uno di quelli ammessi
    do {
        printf("inserisci il codice del medico");
        scanf("%d",&codice);
     } while (codice<0 || codice > nMEdici-1);
    return codice;
}

/*quesito 1 Carica file nel vettore di code*/
void quesito1 (char *nome, coda *archivio){
    //inserire il codice richiesto
    FILE *fp;
    int codicemedico;
    paziente p;
    fp = fopen(nome, "r");
    if (fp==NULL) return;

    while(fscanf(fp,"%s\n%s\n%s\n%d\n%d\n",p.CF,p.nome,p.cognome,&p.urgenza,&codicemedico)==5)
        archivio[codicemedico] =inCoda(archivio[codicemedico],p);
    return;
}

/*stampa coda di attesa
  quesito 2*/
void quesito2(coda c){
    //la funzione stampa la coda di attesa c
    //inserire il codice richiesto
    nodoCoda *l=c.primo;
    while(l!=NULL){
        stampaPaziente(l->info);
        l=l->successivo;
    }

}
/*quesito 3*/
coda quesito3(coda c){
    //estrae il primo paziente e lo stampa;
    if(!testCodaVuota(c)) {
        stampaPaziente(PrimoInCoda(c));
        return EliminaCoda(c);
    }
    return c;
}

/*quesito 4*/
int *quesito4(coda *c){
   // restituisce il vettore contenente le dimensioni di tutte le code
   int *v;
   v = (int *) malloc(sizeof(int));
   if (v==NULL) return v;

   for (int i= 0; i<nMEdici; i++)
        v[i] = size(c[i]);
   return v;
}


/*main*/

int main(){
    int medico, scelta=0;
    coda archivio[nMEdici];

    for(int i=0;i<nMEdici;i++)
        archivio[i]=creaCodaVuota();

    int *vettoreLunghezzaCode;
    do {
        scelta = menu();
        switch (scelta){
            case 1:
                quesito1(NOMEFILE,archivio);
                break;
            case 2:
                medico =leggiCodiceMedico();
                quesito2(archivio[medico]);
                break;
            case 3:
                medico =leggiCodiceMedico();
                archivio[medico]= quesito3(archivio[medico]);
                break;
            case 4:
                vettoreLunghezzaCode = quesito4(archivio);
                stampaVettore(vettoreLunghezzaCode,nMEdici);
                break;
            }
    } while (scelta!=0);
}