#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <curl/curl.h>
#include "mappa.h"
/**
  *attraverso i comandi terminali, si apre una pagina html con la mappa
  *@return void
*/
void aperturamappa(){
  int a=system("xdg-open 'https://ecoride.altervista.org/index.html'");
  if(a==0){
    printf("Mappa avviata!\n\n");
  }
  else{
    system("START https://ecoride.altervista.org/index.html");
  }
}