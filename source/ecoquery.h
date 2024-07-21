#ifndef ECOQUERY_H
#define ECOQUERY_H
char* searchutente(char*, int, int);
char* searchcarta(char*, int, int);
char* tokenumr(int n, char *buffer);
char* ecosearchtra(char*parametro, int n,int ret,int uso);
char* ecofindidSt(char*id_trans);
int verificaabb(char*cf);
void incrementa_stazione(int);
void segnalazione(char*,char*);
#endif