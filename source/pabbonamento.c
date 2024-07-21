#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ecoquery.h"
#include <time.h>
#include"menupages.h"
#include "saldo.h"
#include "ecoquery.h"
#define buffersize 1024

struct abb{
  char cf[20];
  char tipo[30];
  char data[50];
  char scadenza[50];
  char carta[50];
};

/**
*funzione per permettere all'utente di visualizzare il proprio abbonamento col suo saldo account
*@param cf codice fiscale
*@param saldo saldo account
*/
void visabbonamento(char*cf, char*saldo){
  FILE* file=fopen("abbonamento.csv", "r");
  if(file==NULL){
    printf("Errore apertura fikle!");
  }
  char buffer[buffersize];
  while(fgets(buffer, sizeof(buffer), file)){
    char *token;
    token=tokenumr(1, buffer);
    if(strcmp(token,cf)==0){
      token=tokenumr(1, buffer);
      printf("Codice Fiscale: %s\n", token);
      token=tokenumr(2, buffer);
      printf("Tipo Abbonamento: %s\n", token);
      token=tokenumr(3, buffer);
      printf("Data inizio: %s\n", token);
      token=tokenumr(4, buffer);
      printf("Data Fine: %s\n", token);
      token=tokenumr(5, buffer);
      printf("Carta: %s\n", token);
    
    }
      
  }
  fclose(file);
}
/**
*funzione per il calcolo della differenza di tempo tra la data corrente e quella impostata
*@param scadenza: data di cui calcolare la differenza
*return: 0 se l'abbonamento è scaduto, 1 se non è scaduto
*/
int cov(char*scadenza){
  time_t t = time(NULL);//tempo reale
  struct tm tm = *localtime(&t);//calcolo tempo reale
  //prendere scadenza e fare un toknum di / IMPORTANTE CONTARE SOLO DATA E NON ORARIO
  char* token=malloc(sizeof(char)*20);
  token=strtok(scadenza,"/");
  int d=atoi(token);
  token=strtok(NULL,"/");
  int m=atoi(token);
  token=strtok(NULL, "/");
  int y=atoi(token);
  printf("La scadenza è: %d/%d/%d.\n", d,m,y);
  //formattazione struct tm tenendo conto dell'anno unix
  struct tm tm_scadenzat = {
    .tm_year = y-1900,
    .tm_mon = m-1, 
    .tm_mday = d,
    .tm_hour = tm.tm_hour,
    .tm_min = tm.tm_min,
    .tm_sec = tm.tm_sec
  };
  time_t scad=mktime(&tm_scadenzat);
  long diffs=difftime(scad,t);
  double da=(double)diffs/86400;
  if(da>0){
    int giorni=(int)da;
    printf("\nScadenza abbonamento tra %d giorni.\n", giorni);
    return 1;
  }
  else if(da<1){
    printf("\nAbbonamento scaduto!\n");
    return 0;
  }
  else{
    return 0;
  }
}
/**
*funzione per verificare che l'utente sia o meno abbonato al servizio
*@param cf: codice fiscale dell'utente dato univoco
*return void
*/
int verificaabb(char*cf){
  FILE* file=fopen("abbonamento.csv", "r");
  char buffer[buffersize];
  bool find=false;
  int scadenza;
  while(fgets(buffer, sizeof(buffer), file)){
    char *token;
    token=tokenumr(1, buffer);
    if(strcmp(token,cf)==0){
      token=tokenumr(4, buffer);//estrae stringa scadenza
      scadenza=cov(token);
      if(scadenza==1){
        find=true;
      }
    }
  }
  if(find==true){
    return 1;
  }
  else{
    return 0;
  }
}
/**
*Funzione per la scelta del tipo di abbonamento da effettuare, il recupero dati utente, l'impostazione della data corrente e di scadenza e l'inserimento dei dati in abbonamento.csv
*@param cf: codice fiscale dell'utente
*@param carta: carta dell'utente
*/
void rinnovo(char*cf, char*carta){
  struct abb abbonamento;
  char data[22];
  char *s=searchs(cf);
    printf("\nScegli il tipo di abbonamento:\n\n1.Abbonamento mensile €17,99\n2.Abbonamento settimanale €5,00\n\n");
    int choose;
    strcpy(abbonamento.carta, carta);
    scanf("%d", &choose);
    if(choose==1&& atof(s)>=18){
      FILE* file=fopen("abbonamento.csv", "a");
      //RINNOVA ABBONAMENTO MENSILE
      strcpy(abbonamento.cf, cf);
      strcpy(abbonamento.tipo, "Mensile");
      time_t tempoCorrente=time(NULL);
      struct tm *local = localtime(&tempoCorrente);
      //strftime converte in stringa l'ora(%H:%M:%S)e la data(%d/%m/%Y)
      strftime(data, sizeof(char)*100, "%H:%M:%S  %d/%m/%Y", local);
      strcpy(abbonamento.data, data);
      printf("Data abbonamento: %s", abbonamento.data);
      //calcolo data scadenza
      local->tm_mday += 31;
      if(local->tm_mday>31){
        local->tm_mday-=31;
        local->tm_mon++;
      }
      if(local->tm_mon>11){
        local->tm_mon-=11;
        local->tm_year++;
      }
      strftime(abbonamento.scadenza, sizeof(char)*50, "%d/%m/%Y", local);
      printf("\n\nScadenza: %s\n\n", abbonamento.scadenza);
      fprintf(file, "%s,%s,%s,%s,%s\n", abbonamento.cf,abbonamento.tipo,abbonamento.data,abbonamento.scadenza,abbonamento.carta);
      fclose(file);
      modificasaldo(cf, "17.99");
      return;
    }
    else if(choose==2&&atof(s)>=5){
      FILE* file=fopen("abbonamento.csv", "a");
      //RINNOVA ABBONAMENTO SETTIMANALE
      strcpy(abbonamento.cf, cf);
      strcpy(abbonamento.tipo, "Settimanale");
      time_t tempoCorrente=time(NULL);
      struct tm *local = localtime(&tempoCorrente);
      strftime(data, sizeof(char)*100, "%H:%M:%S  %d/%m/%Y", local);
      strcpy(abbonamento.data, data);
      printf("Data abbonamento: %s", abbonamento.data);
      //calcolo data scadenza
      local->tm_mday += 7;
      if(local->tm_mday>31){
        local->tm_mday-=31;
        local->tm_mon++;
      }
      if(local->tm_mon>11){
        local->tm_mon-=11;
        local->tm_year++;
      }
      strftime(abbonamento.scadenza, sizeof(char)*50, "%d/%m/%Y", local);
      printf("\n\nscadenza: %s\n\n", abbonamento.scadenza);
      fprintf(file, "%s,%s,%s,%s,%s\n", abbonamento.cf,abbonamento.tipo,abbonamento.data,abbonamento.scadenza, abbonamento.carta);
      fclose(file);
      modificasaldo(cf, "05.00");
      return;
    
  }
  else{
    printf("Saldo insufficente!\n");
    return;
  }
}
/**
  *Funzione menu abbonamento
  *@param cf: codice fiscale
  *return void
*/
void paginaabbonamento(char *cf){
  int choose;
  char *carta=malloc(sizeof(char)*50);
  carta=searchcarta(cf, 5, 1);
  char *saldo=malloc(sizeof(char)*50);
  do{
    printf("1) Visualizza abbonamento\n2) Rinnova Abbonamento\n\n0) Esci\n");
    scanf("%d", &choose);
    switch(choose){
      case 1:
        saldo=searchs(cf);
        visabbonamento(cf, saldo);
        break;
      case 2:
        if(verificaabb(cf)!=1&& strcmp(carta,"nocarta")!=0){
          rinnovo(cf, carta);
        }
        else{
          printf("\n\nSei gia abbonato oppure controlla di aver inserito una carta di credito!\n\n");
          break;
        }
        break;
      case 3:
        break;
    }
  }while(choose!=0);
  return;
}
