#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "saldo.h"
#include "ecoquery.h"

/**
  *Funzione per la ricerca del saldo corrente di un utente
  *@param codice_fiscale :dato univoco per la ricerca dell'utente
  *return saldo corrente dell'utente
*/
char* searchs(char *codice_fiscale){
  FILE *file = fopen("utente.csv", "r");
  char *token;
  char *saldo=malloc(sizeof(char)*10);
    if (file == NULL) {
    printf("Errore nell' apertura del file!");
    return"";
  }
  char buffer [2048];
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    token=tokenumr(6, buffer);
    if (token != NULL && strcmp(token, codice_fiscale) == 0) {
    saldo = searchutente(token, 6, 8);
      float saldo_float = atof(saldo);
      printf("Saldo: %.2f\n", saldo_float);
      if (saldo != NULL) {
        return saldo;
        break;
      }
    }
  }
  return saldo;
  fclose(file);
}

/**
  *Funzione per il recuopero del saldo corrente di un utente, il calcolo del nuovo saldo confrontandolo con spesa e salvataggio su utente.csv come float convertito in stringa
  *@param cf :dato univoco per la ricerca dell'utente
  *@param spesa :spesa effettuata
*/
void modificasaldo(char *cf, char* spesa){
  FILE* msaldo=fopen("utente.csv", "r+");
  float nsaldo;
  if(msaldo==NULL){
    printf("Errore nell'apertura del file!");
  }
  char *token;
  char buffer[2048];
  while(fgets(buffer, sizeof(buffer), msaldo)){
    token=tokenumr(6, buffer);
    if(strcmp(token, cf)==0){
      char *saldo=malloc(sizeof(char)*10);
      saldo=searchutente(cf,6,8);
      float spesaint=atof(spesa);
      float saldoint=atof(saldo);
      nsaldo=saldoint-spesaint;
      char *nsaldostr=malloc(sizeof(char)*10);
      sprintf(nsaldostr, "%f", nsaldo);
      fseek(msaldo, ftell(msaldo)-strlen(saldo)-2, SEEK_SET);
      if(nsaldo>10){
        fprintf(msaldo, "%s;\n" , nsaldostr);
      }
      else{
        fprintf(msaldo, "0%s;\n" , nsaldostr);
        break;
      }
      break;
    }
  }
  fclose(msaldo);
}
