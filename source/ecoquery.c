/*
Le funzioni contenute in questo file, cercano di emulare il comportamento di query sql, sono limitate in base agli obiettivi della query, per questo
bisognerà, man mano che si prosegue lo sviluppo dell'applicazione, modificare o inserire opportunamente di nuove, le "ecoquery".
Tuttavia sottofunzioni basilari per altre funzioni come toknum e printrecord, sono già state scritte. 
Non appena testato tutto anche il login sarà dipendente da questo file, in modo da ottimizzare anche quel processo.

Modalità di utilizzo:
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecoquery.h"
#include <time.h>
#define buffersize 1024


struct utente {
  char nome[30];
  char cognome[30];
  char email[45];
  char n_tel[10];
  char cv[20];
  char password[30];
  char admin[10];
  char saldo[50];
};

struct carta{
  char numero[20];
  char mese[2];
  char anno[2];
  char cvv[4];
  char cf[20];
};

char* printrecord(struct utente, int);
char* search(char*,int,int);

/**
  *Ricerca di un token di una stringa con separatore ","
  *@param n numero di volte che si deve iterare(n=n_campo)
  *@param buffer stringa su cui si deve cercare il token
  *@return token trovato o NULL
*/
char* tokenumr(int n, char *buffer) {
    char *tokenn=malloc(sizeof(char)*200);    
  char *buffertok=malloc(sizeof(char)*buffersize);
  strcpy(buffertok, buffer);
  for (int i = 0; i < n; i++) {
      tokenn = strsep(&buffertok, ",;"); 
  }
  if (tokenn != NULL) {
    return tokenn;
  }
  
  return "";
}          

/**
  *ricerca di un campo utente all'interno del file csv
  *@param parameter stringa di confronto univoca
  *@param typep n campo del parametro di confronto
  *@param returned n campo da restituire
  *@return stringa trovata
*/

char* searchutente(char *parameter, int typep, int returned){
  char* ritornante=malloc(sizeof(char)*200);
  ritornante=search(parameter, typep, returned);
      return ritornante;

  
}
/**
  *Ricerca di un token da una stringa per poi copiarlo in un determinato indirizzo di memoria pre-estistente
  *@param n numero di volte che si deve iterare(n=n_campo)
  *@param buffer stringa su cui si deve cercare il token
  *@param tokenp indirizzo di memoria in cui si deve copiare il token
  *return token trovato
*/
void toknum(int n, char *buffer, char *tokenp){
  char type;
  char *tokenn;
  for(int i=0;i<n;i++){
    char buffertok[buffersize];
    strcpy(buffertok, buffer);
    if(i==0){
      tokenn = strtok(buffertok, ",");
    }
    else{
      tokenn = strtok(NULL,",;");
    }

  }
  if(tokenn!=NULL){
    strcpy(tokenp, tokenn);
  }
}

/**
  *Ricerca tramite parametro e copia di ogni campo del record trovato nella struct utente
  *@param a stringa di confronto univoca
  *@param n n campo del parametro
  *@param ret campo da restituire
*/
char* search(char *a,int n , int ret){
  char* searchret=malloc(sizeof(char)*100);
  struct utente utente;
  char buffer[buffersize];
  char tokenp[100];
  char *campo=malloc(sizeof(char)*200);
  bool find=false;
  FILE *futente;
  futente = fopen("utente.csv", "r");
  if (futente == NULL) {
    printf("Errore nell'apertura del file");
  }
  while(fgets(buffer, sizeof(buffer), futente))
  {
    toknum(n, buffer, tokenp);
    if(strcmp(tokenp, a)==0){
      char buffer2[buffersize];
      strcpy(buffer2,buffer);
      toknum(1, buffer2, campo);
      strcpy(utente.email, campo);
      toknum(2,buffer,campo);
      strcpy(utente.password,campo);
      toknum(3,buffer,campo);
      strcpy(utente.nome,campo);
      toknum(4,buffer,campo);
      strcpy(utente.cognome, campo);
      toknum(5,buffer,campo);
      strcpy(utente.n_tel,campo);
      toknum(6,buffer,campo);
      strcpy(utente.cv,campo);
      toknum(7,buffer,campo);
      strcpy(utente.admin,campo);
      toknum(8,buffer,campo);
      strcpy(utente.saldo,campo);
      find=true;
       searchret=printrecord(utente, ret);
    }
}
  fclose(futente);
  return searchret;
}

/**
*Stampa del record indicato da ret
*@param utente struct record da stampare
*@param ret selettore campo da stampare
*return stringa campo
*/

char* printrecord(struct utente utente, int ret){
  char *prreturnante=malloc(sizeof(char)*200);
  switch(ret){
    case 1:
      //stampa email
      strcpy(prreturnante, utente.email);
      return prreturnante;
      break;
    case 2:
      //stampa pw
      strcpy(prreturnante, utente.password);
      return prreturnante;
      break;
    case 3:
      //stampa nome
      strcpy(prreturnante, utente.nome);
      return prreturnante;
      break;
    case 4:
      //stampa cognome
      strcpy(prreturnante, utente.cognome);
      return prreturnante;
      break;
    case 5:
      //stampa n_tel
      strcpy(prreturnante, utente.n_tel);
      return prreturnante;
      break;
    case 6:
      //stampa cv
      strcpy(prreturnante, utente.cv);
      return prreturnante;
      break;
    case 7:
      //stampa admin
      strcpy(prreturnante, utente.admin);
      return prreturnante;
      break;
    case 8:
    strcpy(prreturnante,utente.saldo);
    return prreturnante;
  }
  return prreturnante;
}

//inizio sezione query carta.csv!!


char* printcarta(struct carta carta, int ret){
    char *prreturnante=malloc(sizeof(char)*200);
    switch(ret){
      case 1:
        //stampa email
        strcpy(prreturnante, carta.numero);
        return prreturnante;
        break;
      case 2:
        //stampa pw
        strcpy(prreturnante, carta.mese);
        return prreturnante;
        break;
      case 3:
        //stampa nome
        strcpy(prreturnante, carta.anno);
        return prreturnante;
        break;
      case 4:
        //stampa cognome
        strcpy(prreturnante, carta.cvv);
        return prreturnante;
        break;
      case 5:
        //stampa n_tel
        strcpy(prreturnante, carta.cf);
        return prreturnante;
        break;
    }
    return prreturnante;
  }
  //int n: numero campo , buffer della riga

/**
  *funziona in modo analogo a search, ma per carta.csv
*/
char* searchcarta(char *parametro, int tipo, int ritorno){
  char* searchret=malloc(sizeof(char)*100);
    struct carta carta;
    char buffer[buffersize];
    char tokenp[100];
    char *campo=malloc(sizeof(char)*100);
    bool findc=false;
    char *stringa=malloc(sizeof(char)*100);
    FILE *carter;
    carter = fopen("carte.csv", "r");
    if (carter == NULL) {
      printf("Errore nell'apertura del file!");
    }
    while(fgets(buffer, sizeof(buffer), carter))
    {
      stringa=tokenumr(tipo, buffer);
      if(strcasecmp(stringa, parametro)==0){
        char buffer2[buffersize];
        strcpy(buffer2,buffer);
        toknum(1, buffer2, campo);
        strcpy(carta.numero, campo);
        findc=true;
         searchret=carta.numero;
      }
    }
    if(findc==true){
      searchret=printcarta(carta, ritorno);
      return searchret;
    }
    else{
      return "nocarta";
    }
  }

//inizio sezione query transazione.csv!
/**
*funziona in modo analogo a search, ma per transazione.csv
*@param parametro stringa univoca di confronto
*@param n numero di campo da cercare
*@param ret campo da restituire
*@param uso vincolo di utilizzo
*return stringa trovata
*/
char* ecosearchtra(char*parametro, int n,int ret,int uso){
  FILE *file;
  file=fopen("transazione.csv", "r");
  char buffer[buffersize];
  char a[100];
  char *token=malloc(sizeof(char)*20);
  while(fgets(buffer, sizeof(buffer), file)){
    token=tokenumr(n, buffer);
    strcpy(a,token);
    token=tokenumr(6, buffer);
    if(strcmp(a,parametro)==0&&atoi(token)==uso){
      char*dato=malloc(sizeof(char)*100);
      dato=tokenumr(ret, buffer);
      fclose(file);
      return dato;
    }
  }
  fclose(file);
  return"";
}

/**
*Ricerca stazione noleggio di una transazione a partire dall'id della transazione
*@param id id transazione
*@return stazione trovata
*/

char* ecofindidSt(char*id_trans){
  FILE*file=fopen("transazione.csv", "rb");
  char buffer[buffersize];
  char a[100];
  while(fgets(buffer, sizeof(buffer), file)){
    char*token=malloc(sizeof(char)*100);
    token=tokenumr(1, buffer);
    strcpy(a,token);
    token=tokenumr(6,buffer);
    if(strcmp(a,id_trans)==0&&atoi(token)==1){
      token=tokenumr(7, buffer);
      return token;
    }
    }
  fclose(file);
  return"";
}

/**
  *Funzione per l'acquisizione dell'input di segnalazione da parte dell'utente e salvataggio su segnalazioni.csv come stringa
  *@param cf :dato univoco per la ricerca dell'utente
  *@param id_trans :id transazione cui si riferisce la segnalazione
  *return void
*/
void segnalazione(char*cf,char*id_trans){
  FILE *files = fopen("segnalazione.csv", "a");
  char *descrizione=malloc(sizeof(char)*100);
  printf("\n\nPer inviare una segnalazione, inserisci una descrizione appropriata della problematica riscontrata (inserisci _/- al posto dello spazio):\n\n");
  scanf("%s",descrizione);
  //calcolo ora e data della segnalazione
  char *idbici=malloc(sizeof(char)*100);
  idbici=ecosearchtra(cf, 2, 3, 1);
  char *data_segnalazione=malloc(sizeof(char)*100);
  time_t tempoCorrente=time(NULL);
  struct tm *local = localtime(&tempoCorrente);
  strftime(data_segnalazione, sizeof(char)*100, "%H:%M:%S  %d/%m/%Y", local);
  fprintf(files, "%s,%s,%s,%s,%s;\n", id_trans,cf,idbici,data_segnalazione,descrizione);
  fclose(files);
  return;
}