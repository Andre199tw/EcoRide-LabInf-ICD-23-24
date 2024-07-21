#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ecoquery.h"
#include "admin.h"
#include "ecoascii.h"
/**
  *Funzione per impostare a 1 il campo admin di un utente
  *return void
*/
void impostaadmin(){
  char buffer[1024];
  FILE*file=fopen("utente.csv", "rb+");
  char *cf=malloc(sizeof(char)*16);
  printf("\n\nImposta Admin:\nInserisci il codice fiscale dell'utente da impostare come admin:\n(CAUTION: DO NOT WRITE \"agg\")\n");
  scanf("%s",cf);
  if(strcmp(cf,"agg")==0){
    print1();
    sleep (10);
    return;
  }
  while(fgets(buffer, sizeof(buffer), file)){
    char *token=malloc(sizeof(char)*100);
    token=tokenumr(6, buffer);
    if(strcasecmp(token,cf)==0){
      token=tokenumr(8, buffer);
      fseek(file, ftell(file)-strlen(token)-4, SEEK_SET);
      fprintf(file, "1");
      printf("\n\nL'utente %s è stato impostato come admin!\n\n",cf);
      sleep(1);
      fclose(file);
      return;
    }
  }
  printf("\n\nL'utente %s non è stato trovato!\n\n",cf);
  sleep(1);
  fclose(file);
}
/**
  *Funzione per la visualizzazione di tutti gli admin presenti
  *return void
*/
void visualizzadmin(){
  char buffer[1024];
  FILE*file=fopen("utente.csv", "rb+");
  while(fgets(buffer, sizeof(buffer), file)){
    if(strcmp(tokenumr(7, buffer), "1")==0){
      printf("%s", buffer);
    }
  }
  printf("\nInserisci un carattere per continuare...: ");
  scanf("%s",buffer);
  fclose(file);
}

/**
  *Funzione per impostare a 0 il campo admin di un utente e quindi rimuoverlo dalla lista admin
  *return void
*/
void rimuoviadmin(){
  char buffer[1024];
  FILE*file=fopen("utente.csv", "rb+");
  char *cf=malloc(sizeof(char)*16);
  printf("\n\nImposta Admin:\nInserisci il codice fiscale dell'utente da impostare come admin: \n");
  scanf("%s",cf);
  while(fgets(buffer, sizeof(buffer), file)){
    char *token=malloc(sizeof(char)*100);
    token=tokenumr(6, buffer);
    if(strcmp(token,cf)==0){
      token=tokenumr(8, buffer);
      fseek(file, ftell(file)-strlen(token)-4, SEEK_SET);
      fprintf(file, "0");
      printf("\n\nL'utente %s è stato rimosso dalla lista admin!\n\n",cf);
      fclose(file);
      return;
    }
  }
  printf("\n\nL'utente %s non è stato trovato!\n\n",cf);
  fclose(file);
}

//SEZIONE BICI
/**
  *Funzione per l'inserimento di una bici alla lista bici.csv
  *return void
*/
void inserisciBici(){
  FILE* file=fopen("bici.csv", "r+");
  char buffer[1024];
  int id=111;
  while(fgets(buffer, sizeof(buffer), file)){
    id++;
  }
  int ids;
  printf("\n\nInserisci l'ID della stazione dove depositare la bici:\n");
  scanf("%d",&ids);
  incrementa_stazione(ids);
  fprintf(file, "%d,0,0,%d;\n",id,ids);
  fclose(file);
}

void visualizzaBici(){
  FILE* file=fopen("bici.csv", "rb");
  char buffer[1024];
  while(fgets(buffer, sizeof(buffer), file)){
    printf("%s", buffer);
  }
  fclose(file);
}
/**
  *Funzione per visualizzare le bici col campo di utilizzo impostato a 1
  *return void
*/
void visualizzaBiciUso(){
  FILE* file=fopen("bici.csv", "r");
  char buffer[1024];
  char *uso=malloc(sizeof(char)*3);
  while(fgets(buffer, sizeof(buffer), file)){
    uso=tokenumr(3, buffer);
    if(atoi(uso)==1){
      printf("%s", buffer);
    }
  }
  fclose(file);
}

//SEGNALAZIONI
/**
  *Funzione per rendere non disponibile una bici, per guasti o per altro
  *return void
*/
void disabilita(){
  char*id=malloc(sizeof(char)*10);
  printf("Inserisci l'ID bici da disabilitare:\n");
  scanf("%s",id);
  FILE*file=fopen("bici.csv", "rb+");
  char buffer[1024];
  while(fgets(buffer, sizeof(buffer), file)){
    char *token=malloc(sizeof(char)*100);
    token=tokenumr(1, buffer);
    if(strcmp(token,id)==0){
      fseek(file,ftell(file)-strlen(buffer)+4,SEEK_SET);
      fprintf(file,"1");
      break;
    }
  }
  fclose(file);
  return;
}
/**
  *Funzione per rendere disponibile una bici precedentemente disabilitata
  *return void
*/
void abilita(){
  char*id=malloc(sizeof(char)*10);
  printf("Inserisci l'ID bici da abilitare:\n");
  scanf("%s",id);
  FILE*file=fopen("bici.csv", "rb+");
  char buffer[1024];
  while(fgets(buffer, sizeof(buffer), file)){
    char *token=malloc(sizeof(char)*100);
    token=tokenumr(1, buffer);
    if(strcmp(token,id)==0){
      fseek(file,ftell(file)-strlen(buffer)+4,SEEK_SET);
      fprintf(file,"0");
      break;
    }
  }
  fclose(file);
  return;
}
/**
  *Funzione per la visualizzazione ordinata in tabella delle segnalaizoni(analoga a quella della stampa stazioni)
  *return void
*/
void visualizzasegn(){
  FILE* fsegn=fopen("segnalazione.csv", "rb+");
  if(fsegn==NULL){
    printf("\n\nErrore nell'apertura del file!\n\n");
  }
  char buffer[1024];
  for(int i=0;i<130;i++)
  {
    printf("-");
  }
  printf("\n");
  printf("|ID TRANSAZIONE | CODICE FISCALE  | ID BICI|   DATA SEGNALAZIONE   |                    MESSAGGIO                                |\n");
  while(fgets(buffer, sizeof(buffer), fsegn)){
    char *token=malloc(sizeof(char)*300);
    for(int i=0;i<130;i++){
      printf("-");
    }
    printf("\n");
    token=tokenumr(1, buffer);
    printf("|%s", token);

    for(int i=0;i<15-strlen(token);i++){
      printf(" ");
    }
    token=tokenumr(2, buffer);
    printf("|%s", token);

    for(int i=0;i<18-strlen(token);i++){
      printf(" ");
    }
    token=tokenumr(3, buffer);
    printf("|%s", token);

    for(int i=0;i<9-strlen(token);i++){
      printf(" ");
    }
    token=tokenumr(4, buffer);
    printf("|%s",token);
    for(int i=0; i<23-strlen(token)-2;i++){
      printf(" ");
    }
    token=tokenumr(5, buffer);
    printf("|%s",token);
    for(int i=0; i<61-strlen(token)-2;i++){
      printf(" ");
    }
    printf("|\n");
  }
  fclose(fsegn);
  printf("\n\nInserisci un carattere per continuare...: ");
  scanf("%s",buffer);
}