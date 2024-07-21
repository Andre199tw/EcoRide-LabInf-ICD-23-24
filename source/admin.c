#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ecoquery.h"
#include "admin.h"
#include "utilityadmin.h"


/**
  *funzione sottomenu con le varie opzioni per la gestione degli admin 
  *return void
*/
void gestioneadmin(){
  int choose;
  printf("Gestione Admin:\n1) Imposta Admin\n2) Rimuovi Admin\n3) Visualizza Admin\n\n4) Torna Indietro\n\n");
  scanf("%d", &choose);
  switch(choose){
    case 1:
      impostaadmin();
      break;
    case 2:
      rimuoviadmin();
      break;
    case 3:
      visualizzadmin();
      break;
  }
}

/**
  *funzione sottomenu con le varie opzioni per la gestione dei bici
  *return void
*/
void gestionebici(){
  int choose;
  printf("\n\nGestione bici.\n");
  do{
    printf("1) Inserisci bici\n2) Visualizza bici\n3) Visualizza bici in uso\n\n4) Esci\n");
    scanf("%d",&choose);
    switch(choose){
      case 1:
        inserisciBici();
      break;
      case 2:
        visualizzaBici();
        break;
      case 3:
        visualizzaBiciUso();
    }
  }while(choose!=4);
}

/**
  *Funzione (funzionamento analogo alla stampa stazioni) per la stampa ordinata in tabella di tutti i feedback
  *return void
*/
void gestionefeedback(){
  FILE* feed=fopen("feedbacks.csv", "r");
  char buffer[1024];
  for(int i=0;i<143;i++){
    printf("-");
  }
  printf("\n");
  printf("|CODICE FISCALE:     |                    MESSAGGIO:                                | VOTO: |      DATA NOLEGGIO       |      DATA RECENSIONE     |\n");
  while(fgets(buffer, sizeof(buffer), feed)){
    char *token=malloc(sizeof(char)*100);
    for(int i=0;i<143;i++){
      printf("-");
    }
    printf("\n");
    token=tokenumr(1, buffer);
    printf("|%s", token);

    for(int i=0;i<20-strlen(token);i++){
      printf(" ");
    }
    token=tokenumr(3, buffer);
    printf("|%s", token);

    for(int i=0;i<62-strlen(token);i++){
      printf(" ");
    }
    token=tokenumr(2, buffer);
    printf("|%s", token);
    for(int i=0;i<7-strlen(token);i++){
      printf(" ");
    }
    token=tokenumr(4, buffer);
    printf("|%s",token);
    for(int i=0; i<26-strlen(token)-2;i++){
      printf(" ");
    }
    token=tokenumr(5, buffer);
    printf("|%s",token);
    for(int i=0; i<26-strlen(token)-2;i++){
      printf(" ");
    }
    printf("|\n");
  }
  fclose(feed);

  printf("\n\nInvia un carattere per continuare...: ");
  scanf("%s",buffer);
}


/**
  *Funzione sottomenu per la gestione delle segnalazioni
  *return void  
*/
void gestionesegnalazioni(){
  int choose;
  char buffer[1024];
  printf("\n\nGestione segnalazioni.\n");
  printf("\n\n1) Disabilita bici per guasto\n2) Visualizza segnalazioni\n3) Abilita bici\n\n4) Torna indietro\n");
  scanf("%d",&choose);
switch(choose){
  case 1:
    disabilita();
    break;
  case 2:
    visualizzasegn();
    break;
  case 3:
    abilita();
    break;
  }
}
/**
  *funzione per l'inserimento di una nuova stazione
  *@param nome  nome stazione
  *@param via   via stazione
  *param civico  civico stazione
  *@param citta  citta stazione
  *@param id  id stazione
  *return void
*/
void ins(char* nome,char*via,char*civico,char*citta,int id){
  FILE*file=fopen("stazioni.csv", "a");
  fprintf(file, "%s,Via %s %s %s,%d;\n",nome,via,civico, citta, id);
  fclose(file);
}


/**
  *funzione per l'inserimento dei vari dati della nuova stazione(indirizzo costruito)
  *return void
*/
void gestionestazioni(){
  int choose;
  int id=11;
  char *nome=malloc(sizeof(char)*30);
  char *via=malloc(sizeof(char)*30);
  char *civico=malloc(sizeof(char)*5);
  char *citta=malloc(sizeof(char)*30);
  printf("\n Aggiungi stazione.\n\nInserisci l'indirizzo (nome della via): ");
  scanf("%s",via);
  printf("\nAggiungi Civico: ");
  scanf("%s", civico);
  printf("\nAggiungi Citta\': ");
  scanf("%s", citta);
  printf("Inserisci il nome della stazione: ");
  scanf("%s", nome);
  FILE* file=fopen("stazioni.csv", "r+");
  char buffer[1024];
  while(fgets(buffer, sizeof(buffer), file)){
    id++;
  }
  ins(nome,via,civico,citta,id);
  fclose(file);
}


/**
  *funzione analoga a quella presente in pbici.c per il calcolo del numero di stazioni totale
  *return void
*/
int calcolastazioni(){
  FILE* file=fopen("stazioni.csv", "r");
  int i=11;
  char buffer[1024];
  while(fgets(buffer, sizeof(buffer), file)){
    i++;
  }
  return i;
}
/**
  *Funzione per la stampa ordinata in righe di tutte le transazioni per stazione
  *return void
*/
void gestionetrans(){
  FILE *file=fopen("transazione.csv","rb");
  printf("Visualizzazione transazioni stazione.");
  char buffer[1024];
  int i=11,n=0, st=calcolastazioni();
  do{
    while(fgets(buffer, sizeof(buffer), file)){
      char *token=malloc(sizeof(char)*100);
      token=tokenumr(7, buffer);
      int s=atoi(token);
      if(s==i){
        printf("\nTRANSAZIONE %d) %s\n", n, buffer);
        n++;
      }
    }
    fseek(file, 0, SEEK_SET);
    printf("\n\nTRANSAZIONI TOTALI PER LA STAZIONE %d: %d\n\n",i,n);
    i++;
    n=0;
  }while(i<st);

  
  fclose(file);
  int k;
  printf("\n\nInserisci un numero per continuare:\n");
  scanf("%d",&k);
}