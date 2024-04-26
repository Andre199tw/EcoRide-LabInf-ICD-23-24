#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include "libreria.h"
#include"libreria.c"
struct utenteee{
    char nome[30];
    char cognome[30];
    char email[30];
    char n_tel[10];
    char cv[15];
    char password[30];
    //bool admin;
};

void registrati(int c){
    char nome[30];
    printf("ciao%c", c);
}
//schermata di caricamento con load di db mappa

void main(){
    int choose;
    printf("Benvenuto in Eco Ride!");
    do{
        printf("Menu: 1-Login\n2-Registrati\n0-Esci");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            login();
            break;
        case 2:
            reg();
            break;
        
        default:
            break;
        }

    }while(choose!=0);

}