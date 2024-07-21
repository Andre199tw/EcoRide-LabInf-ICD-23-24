#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include<cjson/cJSON.h>
#include <curl/curl.h>
#include "ecoquery.h"
#include "email.h"
/**
*Funzione per leggere tutto il contenuto del file html e convertirlo in stringa
*@param file: puntatore a file
*@return stringa contenente il contenuto
*/
char * readFileContent(char*file) {
  FILE *fp = fopen(file, "r");
  if (!fp) {
    printf("Errore nell'apertura del file html!\n");
    return NULL;
  }

  fseek(fp, 0, SEEK_END);
  long fileSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *fileContent = (char *) malloc(fileSize + 1);
  if (!fileContent) {
    printf("Errore nell'allocazione della memoria per il contenuto del file!\n");
    fclose(fp);
    return NULL;
  }

  fread(fileContent, fileSize, 1, fp);
  fileContent[fileSize] = '\0';

  fclose(fp);
  return fileContent;
}


/**
*Funzione per la composizione dei vari parametri per la compilazione del messaggio e il conseguente invio tramite api brevo
*@param payloadJSON stringa contenente il contenuto del file json per l'impostazione dei parametri api
*/
void inviaEmail(char*payloadJSON) {
  CURL *curl;
  struct curl_slist *headerList = NULL;
  curl = curl_easy_init();
  if (!curl) {
    printf("Errore nell'inizializzazione di CURL!\n");
    return;
  }

  char *apiKey = "";
  char *url = "https://api.brevo.com/v3/smtp/email";

  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);


  headerList = curl_slist_append(headerList, "accept: application/json");
  headerList = curl_slist_append(headerList, "api-key: ");
  headerList = curl_slist_append(headerList, "Content-Type: application/json");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);

  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadJSON);

  CURLcode res = curl_easy_perform(curl);
}

/**
*Funzione per la creazione tramite cJSON del file json per l'impostazione dei parametri api
*@param to_email email del destinatario 
*@param to_name nome del destinatario
*@param c codice univoco per la verifica da inviare al destinatario
*/

void create_complex_json(char *to_email, const char *to_name, int c)
{
    const char *mittente_email = "ecoride.2024@gmail.com";
    const char *mittente_name = "EcoRide";
    const char *soggetto = "codice di verifica";
    const char *html_content = "EcoRide Codice di verifica";
  char code[20];
  sprintf(code, "%d", c);

  
  char*newmess=malloc(sizeof(char)*1024);
  char *a=readFileContent("ecohtml1.html");
  strcpy(newmess, a);
  char *b=readFileContent("emaileco.html");


  //compone tutto il file html, contenente il codice di verifica, in una stringa
  sprintf(newmess,"%s%s%s", a, code,b);

    // Creazione del root object
    cJSON *root = cJSON_CreateObject();

    // Creazione dell'oggetto sender
    cJSON *sender = cJSON_CreateObject();
    cJSON_AddStringToObject(sender, "email", mittente_email);
    cJSON_AddStringToObject(sender, "name", mittente_name);
    cJSON_AddItemToObject(root, "sender", sender);

    // Aggiunta del subject e htmlContent
    cJSON_AddStringToObject(root, "subject", soggetto);
    cJSON_AddStringToObject(root, "htmlContent", newmess);

    // Creazione dell'array messageVersions
    cJSON *message_versions = cJSON_CreateArray();
    cJSON_AddItemToObject(root, "messageVersions", message_versions);

    // Creazione di un oggetto per una singola versione del messaggio
    cJSON *message_version_1 = cJSON_CreateObject();
    cJSON_AddItemToArray(message_versions, message_version_1);

    // Creazione dell'array to
    cJSON *to_array = cJSON_CreateArray();
    cJSON_AddItemToObject(message_version_1, "to", to_array);

    // Creazione dell'oggetto destinatario
    cJSON *to = cJSON_CreateObject();
    cJSON_AddStringToObject(to, "email", to_email);
    cJSON_AddStringToObject(to, "name", to_name);
    cJSON_AddItemToArray(to_array, to);

    // Aggiunta di htmlContent e subject alla versione del messaggio
    cJSON_AddStringToObject(message_version_1, "htmlContent", newmess);
    cJSON_AddStringToObject(message_version_1, "subject", html_content);

    // Convertire l'oggetto JSON in una stringa
    char *json_string = cJSON_Print(root);
    if (json_string == NULL) {
        fprintf(stderr, "Conversione File JSON non riuscita.\n");
        return;
    }

    if(json_string!=NULL){
      inviaEmail(json_string);
    }
    // Libera la memoria
    cJSON_Delete(root);
    free(json_string);
}
/**
  *Funzione chiamante coi vari parametri per la creazione del file json per l'impostazione dei parametri api
*/
void verifica_email(char*email, char *nome, int code){
  create_complex_json(email, nome, code);
}
