#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include <time.h>
#include "menupages.h"
#include "ecoquery.h"
#include "ecoascii.h"
#include "saldo.h"
#include <unistd.h>
/**
*Verifica se l'utente abbia una transazione aperta
*@param cf parametro univoco di ricerca
*@return 1 se l'utente ha una transazione aperta, 0 altrimenti
*/
int verificatrans(char* cf){
  FILE* ftrans=fopen("transazione.csv", "r");
  char buffer[100];
  char *token=malloc(sizeof(char)*100);
  char* token2=malloc(sizeof(char)*100);
  if(ftrans==NULL){
    printf("impossibile aprire file transazioni\n");
  }
  while(fgets(buffer, sizeof(buffer), ftrans)){
    token2=tokenumr(6,buffer);
    strcpy(token,token2);
    token2=tokenumr(2,buffer);
    if(strcmp(token2,cf)==0&&atoi(token)==1){
      fclose(ftrans);
      return 1;
      break;
    }
  }
  fclose(ftrans);
  return 0;
}
/**
*Funzione per il calcolo delle stazioni presenti nel file csv
*/
int calcolastazione(){
  FILE* fsta=fopen("stazioni.csv", "r");
  char buffer[1024];
  int st=11;
  while(fgets(buffer, sizeof(buffer), fsta)){
    st++;
  }
  return st;
}
/**
*crea una tabella con tutte le stazione e le relative bici disponibili
*/
void stampastazioni(){
  FILE* fstazioni=fopen("stazioni.csv", "r");
  char buffer[100];
  for(int i=0;i<69;i++){
    printf("\033[0;33m-");
  }
  printf("\n");
  printf("|Stazioni:      |       Indirizzo:         | Disponibilità: | Codice: |\n");
  while(fgets(buffer, sizeof(buffer), fstazioni)){
    char *token=malloc(sizeof(char)*100);
    for(int i=0;i<69;i++){
      printf("-");
    }
    printf("\n");
    token=tokenumr(1, buffer);
    printf("|%s", token);
    //calcola la differenza tra i caratteri massimi e quelli utilizzati per la stampa del campo, riempie lo spazio vuoto con spazi
    for(int i=0;i<15-strlen(token);i++){
      printf(" ");
    }
    token=tokenumr(2, buffer);
    printf("|%s", token);
    
    for(int i=0;i<25-strlen(token);i++){
      printf(" ");
    }
    token=tokenumr(3, buffer);
    printf("|%s", token);
    for(int i=0;i<20-strlen(token);i++){
      printf(" ");
    }
    token=tokenumr(4, buffer);
    printf("|%s",token);
    for(int i=0; i<5-strlen(token)-2;i++){
      printf(" ");
    }
    printf("\033[0;33m|\n");
  }
  fclose(fstazioni);
}

/**
*Funzione per decrementare la disponibilità delle bici in una determinata stazione
*@param codice stazione di cui decrementare la disponibilità
*return void
*/

void decrementa_stazione(int codice){
  FILE* fstazioni=fopen("stazioni.csv", "r+");
  char buffer[100];
  while(fgets(buffer, sizeof(buffer), fstazioni)){
    char *token=malloc(sizeof(char)*200);
    token=tokenumr(4, buffer);

    if(atoi(token)==codice){
      token=tokenumr(3,buffer);
      int nd=atoi(token);
      int disp=nd-1;
      char *dispstr=malloc(sizeof(char)*10);
      if(disp<10){
        sprintf(dispstr,"0%d",disp);
      }
      else{
        sprintf(dispstr,"%d",disp);
      }
      //posizionamento del cursore del file all'inizio del campo disponibilita'
      fseek(fstazioni,ftell(fstazioni)-7, SEEK_SET);
      fprintf(fstazioni,"%s",dispstr);
      fclose(fstazioni);
      return;
    }
  }
}


/**
  *funzione per aprire una transazione impostando lo stato di utilizzo della bici a 1
  *@param cf dato univoco per la ricerca
  *@param idbici id della bici da noleggiare
  *@param ids id stazione da cui si effettua il noleggio
*/


void open_transazione(char* cf , int idbici, int ids){
  idbici=idbici+110;
  FILE* ftrans=fopen("transazione.csv", "r+");
  int id_s=0;
  char buffer[1024];
  //calcola quante transazioni sono state effettuate
  while(fgets(buffer, sizeof(buffer), ftrans)){
    id_s++;
  }
  char *idstr=malloc(sizeof(char)*10);
  sprintf(idstr,"%d",id_s);
  char *data=malloc(sizeof(char)*30);
  char *scadenza=malloc(sizeof(char)*30);
  //calcola la data e ora corrente
  time_t tempoCorrente=time(NULL);
  struct tm *local = localtime(&tempoCorrente);
  //converte la data e ora corrente in stringa
  strftime(data, sizeof(char)*100, "%H:%M:%S  %d/%m/%Y", local);
  printf("Data abbonamento: %s", data);
  //calcola la data di scadenza dell'abbonamento(data corrente + n giorni)
  local->tm_hour += 3;
  if(local->tm_mday>31){
    local->tm_mday-=31;
    local->tm_mon++;
  }
  if(local->tm_mon>11){
    local->tm_mon-=11;
    local->tm_year++;
  }
  if(local->tm_hour>23){
    local->tm_hour-=23;
    local->tm_mday++;
  }
  strftime(scadenza, sizeof(char)*100, "%H:%M:%S  %d/%m/%Y", local);
  sprintf(idstr,"%d",id_s);
  //stampa su transazione.csv i vari dati della transazione
  fprintf(ftrans,"%s,%s,%d,%s,%s,1,%d,  ;\n",idstr,cf,idbici,data,scadenza,ids);
  printf("\nTransazione effettuata con successo!\n");
  printf("Id Transazione:%s\nId Bici: %d\nData Noleggio: %s\nData Scadenza: %s\n\nRiporta la bici in una stazione per non incorrere in una sanzione!\nGrazie per aver scelto EcoRide\n", idstr, idbici, data,scadenza);
 
  sleep(7);
  fclose(ftrans);
  return;
}

/**
*funzione per chiudere una transazione impostando lo stato di utilizzo della bici a 0
*@param cf dato univoco per la ricerca
*@param codice id stazione dove si vuole depositare la bici
*return void
*/
void close_transazione(char *cf,int codice){
  FILE* ftrans=fopen("transazione.csv", "r+");
  char buffer[1024];
  while(fgets(buffer, sizeof(buffer), ftrans)){
    char*token=malloc(sizeof(char)*100);
    token=tokenumr(2, buffer);
    char*idsn=tokenumr(7,buffer);
    char*tokenstato=malloc(sizeof(char)*100);
    tokenstato=tokenumr(6, buffer);
    if(strcmp(token,cf)==0&&atoi(tokenstato)==1){
      fseek(ftrans, ftell(ftrans)-9, SEEK_SET);
      fprintf(ftrans,"0,%s,%d;\n", idsn, codice);
    }
  }
  fclose(ftrans);
  return;
}

/**
*funzione per incrementare la disponibilità di una bici rendendola disponibile
*@param cf codice univoco di ricerca
*@param codice id stazione dove si vuole depositare la bici
*return void
*/
void incrementa_bici(char* cf,int codice){
  FILE* fbici=fopen("bici.csv", "r+");
  char buffer[1024];
  char*token=malloc(sizeof(char)*100);
  char*idstaz=malloc(sizeof(char)*100);
  char*idbici=malloc(sizeof(char)*100);
  //cerca la bici nel file bici.csv
  idbici=ecosearchtra(cf, 2, 3, 1);
  while(fgets(buffer, sizeof(buffer), fbici)){
    token=tokenumr(1, buffer);
    idstaz=tokenumr(4, buffer);
    if(strcmp(token,idbici)==0){
      fseek(fbici, ftell(fbici)-strlen(idstaz)-4, SEEK_SET);
      fprintf(fbici,"0,%d",codice);
    }
  }
  fclose(fbici);
  return;
}

/**
*funzione per la ricerca di una bici disponibile in una determinata stazione
*@param cf codice univoco di ricerca
*@param stazioneint id stazione di cui si vuole ricercare la bici
*return void
*/
void opbici(char* cf, int stazioneint){
  FILE*fbici=fopen("bici.csv","rb+");
  if(fbici==NULL){
    printf("errore nell'apertura del file");
  }
  char buffer[1024];
  int id=1;
  //conversione stazioneint in stringa
  char *stazionestr=malloc(sizeof(char)*10);
  sprintf(stazionestr,"%d",stazioneint);
  while(fgets(buffer,sizeof(buffer), fbici)){
    char *token=malloc(sizeof(char)*10);
    token=tokenumr(4, buffer);
    char *tokendisp=malloc(sizeof(char)*5);
    tokendisp=tokenumr(3, buffer);
    char *tokenguasto=malloc(sizeof(char)*5);
    tokenguasto=tokenumr(2, buffer);
    //verifica se la riga estrapolata abbia i campi stazione e disponibilita' idonei e che la bici non sia guasta
    if(atoi(token)==stazioneint&&atoi(tokendisp)==0&&atoi(tokenguasto)==0){
      printf("\n\nHai 3h di bici libere, vuoi prenotarla?\n1) Si\n2) No\n");
      int choose;
      scanf("%d", &choose);
      if(choose==1){
        open_transazione(cf, id,stazioneint);
        decrementa_stazione(stazioneint);
        //impostazione cursore all'inizio del campo disponibilità e imposta il valore a 1(non disponibile)
        fseek(fbici, ftell(fbici)-6, SEEK_SET);
        fprintf(fbici, "1");
        fclose(fbici);
        break;
      }
      else{
        break;
      }
    }
    id++;
  }
  
  return;
}


/**
  *Funzione per incrementare la disponibilità delle bici in una determinata stazione
  *@param codice stazione di cui incrementare la disponibilità
  *return void
*/
void incrementa_stazione(int codice){
  FILE* fstazioni=fopen("stazioni.csv", "rb+");
  char buffer[100];
  char *tokenstaz=malloc(sizeof(char)*200);
  while(fgets(buffer, sizeof(buffer), fstazioni)){
    tokenstaz=tokenumr(4, buffer);

    if(atoi(tokenstaz)==codice){
      tokenstaz=tokenumr(3,buffer);
      int nd;
      nd=atoi(tokenstaz);
      int disp=nd+1;
      char *dispstr=malloc(sizeof(char)*10);
      if(disp<10){
        sprintf(dispstr,"0%d",disp);
      }
      else{
        sprintf(dispstr,"%d",disp);
      }
      //posiziona il cursore del file all'inizio del campo disponibilita' e incrementa di uno
      fseek(fstazioni,ftell(fstazioni)-7, SEEK_SET);
      fprintf(fstazioni,"%s",dispstr);
      fclose(fstazioni);
      return;
    }
  }
  fclose(fstazioni);
  return;
}

/**
*funzione menu per l'utente con una bici in uso
*@param cf codice univoco di ricerca
*return void
*/
void restituzione(char *cf){
  printf("\n\nHai una bici in uso\n1)Restituisci la bici\n2)Invia una segnalazione\n");
  int choose;
  int codice;
  scanf("%d", &choose);
  if(choose==1){
    printf("\nInserisci l'id della stazione in cui stai depositando la bici:\n");
    int st=calcolastazione();
    scanf("%d", &codice);
    if(codice<11||codice>st){
      printf("\nCodice stazione non valido\n");
      return;
    }
    caricamento();
    incrementa_bici(cf,codice);
    sleep(2);
    close_transazione(cf,codice);
    sleep(2);
    incrementa_stazione(codice);
    registraFeedback(cf);
    printf("\n\nGrazie per aver scelto EcoRide\n");
    sleep(4);
    
  }
  else if(choose==2){
    segnalazione(cf,"1");
    printf("\n\nsegnalazione inviata con successo!\n");
    return;
  }
  //restituzione codice
}
/**
  *funzione per verificare che almeno una bici sia disponibile in una determinata stazione
  *@param codice stazione di cui verificare la disponibilità
  *return void
*/
int verifica_disp_stazione(int codice){
  FILE* fstazioni=fopen("stazioni.csv", "r");
  char buffer[100];
  while(fgets(buffer, sizeof(buffer), fstazioni)){
    char *token=malloc(sizeof(char)*200);
    token=tokenumr(4, buffer);
    if(atoi(token)==codice){
      token=tokenumr(3,buffer);
      if(atoi(token)>0){
        return 0;
      }
      else{
        return 1;
      }
    }
  }
  return -1;
}


/**
  *funzione menu per l'utente che andrà a noleggiare una bici
  *@param cf codice univoco di ricerca
*/
void noleggio(char* cf){
  stampastazioni();
  int codice;
  int st=calcolastazione();
  printf("\n\nInserisci il codice della stazione:\n");
  scanf("%d", &codice);
  if(codice>10&&codice<st){
    if(verifica_disp_stazione(codice)==0){
      opbici(cf, codice);
      return;
    }
    else{
      printf("\n\nNon ci sono bici disponibili in questa stazione!\n");
      return;
    }
  }
  else{
    printf("\n\nCodice stazione non valido!\n\n");
  }
}

/**
  *funzione menu bici, se l'utente ha un abbonamento e non ha una bici in uso potrà noleggiarne una
  *@param cf codice univoco di ricerca
  *return void
*/
void pagina_bici(char* cf){
  int vbici;
  int choose;
  vbici=verificatrans(cf);
  int vabb=verificaabb(cf);
  if(vbici==1){
    restituzione(cf);
    return;
  }
  else if(vbici==0&&vabb==1){
    noleggio(cf);
    return;
  }
  else{
    printf("\n\nNon hai ancora un abbonamento!\n\nAttivane subito uno!\n\nReindirizzamento in corso...\n");
    sleep(3);
  }
  return;
}  