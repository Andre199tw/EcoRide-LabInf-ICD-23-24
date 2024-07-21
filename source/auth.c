#include "auth.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "email.h"
#include "ecoquery.h"
#define buffersize 1024
//#include <random>


/**
* Struct che rapresenta un utente
*/
struct utente {
  char nome[30];
  char cognome[30];
  char email[45];
  char n_tel[20];
  char cv[20];
  char password[40];
  bool admin;
  float saldo;
};

/**
    *Genera un numero di 5 cifre casuali
    *@return numero casuale di 5 cifre
*/
int randoma(){
    srand(time(NULL));
    int n1,n2;
    n1=rand()%100;
    n2=rand()%100;
    int n=n1*100+n2;
    int nn=n+10000;
    return nn;
}
/**
    *inserimento dati nel file csv
    *@param struct utente
    *@return void
*/
void insrecord(struct utente *utente) {
      FILE *futente;
    char buffer[buffersize];
    int count=0;
    int code = randoma();
    int codicever;
    verifica_email(utente->email, utente->nome,code);
    do{
        printf("\nInserisci il codice di verifica inviato per email:\n");
        scanf("%d", &codicever);
        if(codicever==code){
            printf("\n\nVerifica Completata!!\nRegistrazione completata!\n\n");
        }
        else{
            printf("\n\nCodice errato, inseriscilo nuovamente:\n\n");
        }
    }while(codicever!=code);
    printf("\n\nVerifica Completata!\n");
    futente = fopen("utente.csv", "a");
    if (futente == NULL) {
    printf("Errore nell'apertura del file!");
    }
    while(fgets(buffer, sizeof(buffer), futente)){
        count++;
    }
        fseek(futente, count, SEEK_SET);
    fprintf(futente, "%s,%s,%s,%s,%s,%s,%d,%f;\n",utente->email, utente->password,utente->nome, utente->cognome, utente->n_tel,  utente->cv, utente->admin, utente->saldo);
        fclose(futente);
}
/**
    *Verifica che l'utente sia presente nel database
    *@param email: email dell'utente
    *@param password: password dell'utente
    *@return valore booleano: true se l'utente è presente, false se non è presente
*/
int verifica(char *email, char *password){
    FILE *futente;
      futente = fopen("utente.csv", "r");
    char buffer [buffersize];
    char *token;
    bool e=false;
    bool p=false;
      if (futente == NULL) {
        printf("Errore nell'apertura del file!");
          return 2;
      }
    
    while(fgets(buffer, sizeof(buffer), futente))
    {
            token = strtok(buffer, ",");
            if(token==NULL){
                printf("\n\n !!ERROR: TOKEN(email) IS NULL!!\n\n");
            }
            if(strcmp(email, token)==0){
                e=true;
            }

            token = strtok(NULL,",");
            if(token==NULL){
                printf("\n\n !!ERROR:TOKEN(email) IS NULL!!\n\n");
            }
            if(strcmp(token, password)==0){
                p=true;
            }
    }
    if(e==true && p==true){
        printf("\n\nUtente Trovato!\n");
        return 1;
    }
    else{
        printf("\n\nAttenzione! Utente non trovato!\n");
        return 0;
    }
}

/**
    *Inserimento dei dati nella struct
    *@return cf o NULL
*/

void reg() {
  struct utente utente;
  char nome[30];
  char *emailver=malloc(sizeof(char)*100);
  char *cfver=malloc(sizeof(char)*100);
  printf("\n\n\033[0;35mATTENZIONE!\nGentile utente, desideriamo informarla circa le finalità e le modalità del trattamento dei suoi dati,\nche effettueremo ai sensi del Regolamento Europeo n. 679/2016 cd. GDPR, relativo alla protezione e alla libera circolazione\ndei dati delle persone fisiche.\nContinuando con la registrazione, accetta quanto previsto dal suddetto GDPR.\033[0;35m\n\n");
  printf("\n\033[0;37mInserisci nome:\n");
  scanf("%s", utente.nome);
  printf("Inserisci cognome:\n");
  scanf("%s", utente.cognome);
  printf("Inserisci email:\n");
  scanf("%s", utente.email);
  printf("Inserisci numero di telefono:\n");
  scanf("%s", utente.n_tel);
  printf("Inserisci codice fiscale:\n");
  scanf("%s", utente.cv);
  printf("Inserisci password:\n");
  scanf("%s", utente.password);
  utente.admin = 0;
    //imposta un saldo d'esempio per ogni utente
    utente.saldo=50;
    //chiama funzione per verificare che l'utente non sia già registrato
  emailver=searchutente(utente.email, 1, 1);
  cfver=searchutente(utente.cv, 6, 6);
  if(strcmp(emailver,utente.email)!=0 && strcasecmp(cfver,utente.cv)!=0){
    insrecord(&utente);
  }
  else{
      printf("\n\nAttenzione! Utente gia\' registrato!\nProcedere con il login.\n\n");
  }
};

/**
    *Inserimento dati utente
    @return cf o NULL
*/

char* login() {
  char email[45], password[40];
  char *cf=malloc(sizeof(char)*20);
  printf("Inserisci email:\n");
  scanf("%s", email);
  printf("Inserisci password:\n");
  scanf("%s", password);
    //chiama funzione per verificare che l'utente sia presente nel file csv
    int res;
    res=verifica(email, password);
    //recupera il cf dell'utente(PK)
    sleep(1);
        cf=searchutente(email,1,6);
    
    if(res==1){
        int codice=randoma();
        int codice_verifica;
        verifica_email(email, "nome", codice);
        printf("\n\nInserisci il codice di verifica inviato per email:\n");
        scanf(" %d", &codice_verifica);
        if(codice==codice_verifica){
            printf("\n\nLogin avvenuto con successo!\n\n");
            return cf;
        }
        else {
            return "";
        }
    }
    else{
        sleep(3);
        return "";
    }
}