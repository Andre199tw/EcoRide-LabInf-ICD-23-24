#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include "libreria.h"


struct utente{
    char nome[30];
    char cognome[30];
    char email[30];
    char n_tel[10];
    char cv[15];
    char password[30];
    bool admin;
};


void reg(){
    struct utente utente1;
    char nome [30];
    printf("\ninserisci nome");
    scanf("%s",utente1.nome);
    printf("inserisci cognome");
    scanf("%s",utente1.cognome);
    printf("inserisci email");
    scanf("%s",utente1.email);
    printf("inserisci numero di telefono");
    scanf("%s",utente1.n_tel);
    printf("inserisci codice fiscale");
    scanf("%s",utente1.cv);
    printf("inserisci password");
    scanf("%s",utente1.password);
    utente1.admin=1;
};
void login(){
    char email[30], password[30];
    printf("inserisci email");
    scanf("%s",email);
    printf("inserisci password");
    scanf("%s",password);
    //verifica(email,password);
};
/*int verifica(char email, char password){
    //dopo apertura file
}*/
