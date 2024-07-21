#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include<unistd.h>
#include"ecoascii.h"

/**
  *Funzione per la lettura del file fino a un determinato carattere e effettua la stampa a video. Le altre funzioni di print sono analoghe.
  *return void
*/
void printlogo(){
  char buffer [2048];
  FILE*asciif;
  asciif=fopen("logo.txt","r");
  while(strcmp(fgets(buffer, sizeof(buffer), asciif), "n")<0){
    if(buffer[0]=='a'){
      break;
    }
    printf("\033[0;32m %s", buffer);
    
  }
}

void printadmin(){
    char buffer[2048];
    FILE*asciif;
    asciif=fopen("logo.txt","r");
    //il ciclo for "conta" le righe da saltare prima della stampa del menu
    for(int i=0;i<48;i++){
      fgets(buffer, sizeof(buffer), asciif);
    }
    //il while strcmp serve a controllare se la "sezione" del file è finita
    while(fgets(buffer, sizeof(buffer), asciif)){
      if(atoi(buffer)==1){
        return;
      }
        printf("\033[0;31m %s", buffer);
    }
  fclose(asciif);
  }



void printmenu(){
  char buffer[2048];
  FILE*asciif;
  asciif=fopen("logo.txt","r");
  //il ciclo for "conta" le righe da saltare prima della stampa del menu
  for(int i=0;i<26;i++){
    fgets(buffer, sizeof(buffer), asciif);
  }
  //il while strcmp serve a controllare se la "sezione" del file è finita
  while(strcmp(fgets(buffer, sizeof(buffer), asciif),"n")>0){
    if(strcmp(buffer, "n")==0){
      return;
    }
      printf("\033[0;32m %s", buffer);
  }
}


void printwelcome(){
  char buffer[2048];
    FILE*asciif;
    asciif=fopen("logo.txt","r");
    //il ciclo for "conta" le righe da saltare prima della stampa del menu
    for(int i=0;i<36;i++){
      fgets(buffer, sizeof(buffer), asciif);
    }
    //il while strcmp serve a controllare se la "sezione" del file è finita
    while(strcmp(fgets(buffer, sizeof(buffer), asciif), "n")>0){
      if(strcmp(buffer,"n")==0){
        return;
      }
        printf("\033[0;32m %s", buffer);
    }
}

/**
*creazione e avanzamento barra di caricamento
*return void
*/
void stampaBarraCaricamento(float percentuale) {
  int numCaratteri = (int)(percentuale * 100); 
  char barra[101]; // 100 caratteri per la barra + 1 per il terminatore nullo

  // Riempi la barra con '#'
  for (int i = 0; i < numCaratteri; i++) {
    barra[i] = '#';
  }

  // Riempi il resto della barra con spazi
  for (int i = numCaratteri; i < 101; i++) {
    barra[i] = ' ';
  }

  barra[100] = '\0'; // Aggiunge il terminatore nullo

  printf("\b[%-51s] %.2f%%\n", barra, percentuale*100);
}

/**
  *Funzione per la temporizzazione del caricamento.
*/
void caricamento(){
  for (float i = 0.0; i <= 1.0; i += 0.02) {
    system("clear");
  stampaBarraCaricamento(i);
  usleep(100000); // Regola la velocità di caricamento (microsecondi)
  }
}

void print1(){
  char buffer[2048];
      FILE*asciif;
      asciif=fopen("logo.txt","r");
      //il ciclo for "conta" le righe da saltare prima della stampa del menu
      for(int i=0;i<58;i++){
        fgets(buffer, sizeof(buffer), asciif);
      }
      //il while strcmp serve a controllare se la "sezione" del file è finita
      while(fgets(buffer, sizeof(buffer), asciif)){
        if(strcmp(buffer,"n")==0){
          return;
        }
          printf("\033[0;32m %s", buffer);
      }
}
