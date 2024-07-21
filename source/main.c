#include <stdio.h>
#include "auth.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ecoquery.h"
#include "mappa.h"
#include "ecoascii.h"
#include "email.h"
#include<unistd.h>
#include "menupages.h"
#include "admin.h"
/**
  *Funzione si divide in 3 parti: login, menu utente, menu admin. La funzione si occupa di chiamare le funzioni per l'esecuzione dei vari menu. Questa continuerà finchè l'utente deciderà di uscire completamente dal programma, dopo aver effettuato il logout.
  *@return void
*/
int main(void) {
  int close;
  do{
  int choose;
  caricamento();
  sleep(1);
  char* cfu=malloc(sizeof(char)*20);
    bool log=false;
do{
  system("clear");
  printlogo();
  sleep(1);
  printf("\n\n\n\n\n");
  printwelcome();
  sleep(1);
  printf("\n\033[0;37m-1 Login \n-2 Registrati\n");
  printf("\nInserisci la tua scelta: ");
  scanf("%d", &choose);
  switch(choose){
    case 1:
        cfu=login();
        break;
    case 2:
        reg();
        break;
    }
  }while(strcmp(cfu,"")==0);

  char*admin=malloc(sizeof(char)*10);
    //ricerca a partire dal codice fiscale, se l'utente sia o meno un admin
  admin=searchutente(cfu, 6, 7);
  printf("\n\nadmin:%s\n\n", admin);
  if(atoi(admin)==0){
    aperturamappa();
    //MENU PRINCIPALE
    do{
      system("clear");
      printlogo();
      printmenu();
      printf("\n\n\n\n\033[0;34m-1 Scegli Bici\n-2 Opzioni Abbonamento\n-3 Opzioni Pagamento\n-4 Apri Mappa\n-5 Logout\n\n");
      printf("Inserisci la tua scelta: ");
      scanf("%d", &choose);
      switch(choose){
        case 1:
          pagina_bici(cfu);
          break;
        case 2:
          paginaabbonamento(cfu);
          break;
        case 3:
          paginacarta(cfu);
          break;
        case 4:
          aperturamappa();
          break;
        case 5:
          break;
      }
    }while(choose!=5);
    system("clear");
  }
  else if(atoi(admin)==1){
    //MENU ADMIN
    int choosea;
    do{
      system("clear");
      printadmin();
      printf("\n\n\n\033[0;31m1)Gestione Admin\n2)Gestione Bici\n3)Gestione Feedback\n4)Gestione Segnalazioni\n5)Aggiungi Stazioni\n6)Analitiche Transazioni-Stazione\n7)Logout\n\n");
      scanf("%d", &choosea);
      switch(choosea){
        case 1:
          gestioneadmin();
          break;
        case 2:
          gestionebici();
          break;
        case 3:
          gestionefeedback();
           break;
        case 4:
          gestionesegnalazioni();
          break;
        case 5:
           gestionestazioni();
           break;
        case 6:
          gestionetrans();
          break;
      }


    }while(choosea!=7);
  }
  
    printf("\n\nIntende chiudere da Ecoride? (1=si, 0=no)\n");
    scanf("%d",&close);
    
  }while(close!=1);
  system("clear");
  printf("\nChiusura di EcoRide in corso...\n\n\nArrivederci!");
}
