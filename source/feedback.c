#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "saldo.h"
#include "ecoquery.h"
#define MAX_CODICE_FISCALE 17
#define MAX_COMMENTO 100

/**
  *Funzione per l'ottenimento in input del commento e il suo conseguente salvataggio su feedbacks.csv
  *@param cf codice fiscale dell'utente
  *@return void
*/
void registraFeedback(char*cf) 
{
  FILE* filef = fopen("feedbacks.csv", "a");
  int voto,i=0;
  char commento[100];
    
  printf("\n\nChe voto daresti ad Ecoride da 1 a 5?: \n");
  scanf("%d", &voto);
  
  if(voto<1){
    voto=1;
  }
  else if(voto>5){
    voto=5;
  }
  //recupero dati
  char* data_noleggio=calloc(1,sizeof(char)*20);
  char*data_corrente=calloc(2,sizeof(char)*20);
  char*temp;
  data_noleggio=ecosearchtra(cf, 2, 4, 1);
  time_t tempo=time(NULL);
  struct tm *local = localtime(&tempo);
  strftime(data_corrente, sizeof(char)*20, "%H:%M:%S %d/%m/%Y",local);
  printf("\n\nVuoi lasciarci un commento? (Inserisci _/- al posto degli spazi): \n\n");
  printf("Inserisci un commento: ");
  scanf("%s", commento);
 fprintf(filef, "%s,%d,%s,%s,%s;\n", cf, voto, commento, data_noleggio, data_corrente);
 printf("Grazie per il tuo feedback!\n");
  fclose(filef);
  sleep(2);
  return;
 }