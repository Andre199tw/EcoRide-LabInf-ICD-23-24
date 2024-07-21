#include "addc.h"
#include "ecoquery.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct carta {
  char mese[20];
  char anno[20];
  char cvv[20];
  char numerocarta[30];
};
/**
*funzione per l'inserimento dei dati della carta nel file.csv
*@param cf codice univoco di ricerca (2° codice univoco)
*@param carta carta di credito (1°codice univoco)
*/
void inserisci_carta(struct carta *carta, char *cf) {
  FILE *fcarte;
  char buffer[100];
  int count=0;
  fcarte = fopen("carte.csv", "a");
  if (fcarte == NULL) {
    printf("Errore nell'apertura del file!");
  }
    while (fgets(buffer, sizeof(buffer), fcarte)) {
      count++;
  }
  fseek(fcarte, count, SEEK_SET);
  fprintf(fcarte, "%s,%s,%s,%s,%s;\n", carta->numerocarta, carta->mese,
          carta->anno, carta->cvv, cf);
  fseek(fcarte, count, SEEK_END);
  fclose(fcarte);
}
/**
*funzione che permette all'utente di inserire una carta di credito se non ne ha già una inserita
*@param cfcarta codice univoco di inserimento(2°codice univoco)
*/
void aggiungicarta(char *cfcarta) {
  struct carta primaria;
  char num[30], cv[30];
  char m[20], a[20];
  char *nver=malloc(sizeof(char)*100);
  // int count=0;
  printf("\n\nInserisci il numero della carta da collegare:\n");
  scanf("%s", num);
  printf("\n\nInserisci la scandenza della carta da collegare.\n\nInserisci il "
         "mese:\n");
  scanf("%s", m);
  printf("\nInserisci l'anno:\n");
  scanf("%s", a);
  printf("\n\nInserisci il cvv:\n");
  scanf("%s", cv);
  strcpy(primaria.numerocarta, num);
  strcpy(primaria.cvv, cv);
  strcpy(primaria.mese, m);
  strcpy(primaria.anno, a);
  nver=searchcarta(num, 1, 1);
  if(strlen(num)==16&&strlen(m)==2&&strlen(a)==2&&strlen(cv)==3){
    if(strcmp(nver,"nocarta")==0){
      inserisci_carta(&primaria, cfcarta);
    }
    else{
      printf("\n\nLa carta è già collegata!\n");
    }
  }
  else{
    printf("\n\nERRORE!\nDati della carta non validi!\n\n");
  }
  
}

struct data {
  char mese[4];
  char anno[4];
};
/**
*funzione che permette all'utente di inserire i nuovi dati di una carta
*@param parametro cf utente
*return void
*/
void modifica_carta(char *parametro) {
  int type = 5;
  char buffer[100];
  char tokenp[100];
  char newncarta[50];
  char *stringa=malloc(sizeof(char)*100);
  struct data data;
  struct carta ncarta;
  int counterrow = 0;
  char *nver=malloc(sizeof(char)*100);
  char confronto[30], newcvv[30];
  strcpy(confronto, parametro);
  FILE *carter;
  carter = fopen("carte.csv", "r+");
  if (carter == NULL) {
    printf("Errore nell'apertura del file!");
  }
  printf("\n\nInserisci il nuovo numero di carta:\n");
  scanf("%s", newncarta);
  printf("\n\nInserisci la scandenza della nuova carta.\nInserisci il mese:\n");
  scanf("%s", data.mese);
  printf("\n\nInserisci l'anno:\n");
  scanf("%s", data.anno);
  printf("\n\nInserisci il cvv:\n");
  scanf("%s", newcvv);
  strcpy(ncarta.numerocarta, newncarta);
  strcpy(ncarta.mese, data.mese);
  strcpy(ncarta.anno, data.anno);
  strcpy(ncarta.cvv,newcvv);
  if(strlen(newncarta)!=16){
    printf("\nERRORE: il numero di carta deve essere di 16 cifre!\n");
  }
  if(strlen(data.mese)!=2){
    printf("\nERRORE: il mese deve essere di 2 cifre!\n");
  }
  if(strlen(data.anno)!=2){
    printf("\nERRORE: l\'anno deve essere di 2 cifre!\n");
  }
  if(strlen(newcvv)!=3){
    printf("\nERRORE: il cvv deve essere di 3 cifre!\n");
  }
  //controlla che non ci sia una carta inserita nel csv uguale a quella inserita dall'utente
  nver=searchcarta(newncarta, 1, 1);
  //verifica che i vari dati inseriti siano validi secondo lo standard
  if(strlen(newncarta)==16&&strlen(data.mese)==2&&strlen(data.anno)==2&&strlen(newcvv)==3){
    if(strcmp(nver,newncarta)!=0){
      while (fgets(buffer, sizeof(buffer), carter)) {
        stringa = tokenumr(type, buffer);
        if(strcmp(stringa, parametro)==0){
          // Sovrascrive la riga con le nuove informazioni
          fseek(carter, ftell(carter)-(strlen(buffer)), SEEK_SET);
          fprintf(carter, "%s,%s,%s,%s,%s;\n", newncarta, data.mese, data.anno,newcvv,parametro);
          printf("\n\nCarta modificata con successo!\n");
          break; 
        }
        counterrow++;
      }
    }
    else{
      printf("\n\nERRORE: la carta è già collegata!\n");
    }
  }
  else{
    printf("\nDati non validi!");
  }
  fclose(carter);
}

/**
  *Funzione menu per le varie operazioni su tabella carta
  *@param cf codice fiscale dell'utente
  *@return void
*/
void paginacarta(char*cf){
  char *stringa;
  stringa=searchcarta(cf, 5, 1);
  
  int choose;
  do{
    printf("\n1)Aggiungi Carta\n2)Modifica carta\n\n3)Torna al menu principale\n\n");
    scanf("%d", &choose);
    switch(choose){
      case 1:
          if(strcasecmp(stringa,"nocarta")==0){
            aggiungicarta(cf);
          }
          else{
            printf("\n\nHai gia' una carta collegata!\n\n");
          }
        break;
      case 2:
        if(strcmp(stringa,"nocarta")!=0){
          modifica_carta(cf);
        }
        break;
    }
  }while(choose!=3);
}