#ifndef TS_H
#define TS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_SIZE_MAX 32
#define MAX(X,Y) (X)>(Y)?(X):(Y)
#define MIN(X,Y) (X)<(Y)?(X):(Y)

#define TAB      "           "
#define CONTEXTE "| CONTEXTE |"
#define IDE  "ID"
#define ADR  "ADR"
#define TYPE "TYPE"
#define SIZE "SIZE"

#define BR  "\x1b[1m"
#define RB  "\x1b[0m"

#define MIN_SIZE 10

enum  { ENTIER=0, TABLEAU, POINTEUR, FONCTION};

typedef struct symbole{
  char id[ID_SIZE_MAX];
  int type; 
  int size;
  int adr;
  struct symbole *next;
} symbole;

typedef struct contexte{
  char name[ID_SIZE_MAX];
  symbole * liste_symbole;
  struct contexte * next;
} contexte;

typedef struct contexte * table_symb;

table_symb  ts_init_table(char * context);
contexte * ts_rechercher_contexte(table_symb table, char *context);
symbole * ts_rechercher_identificateur(table_symb table, char *id, char *context);
contexte * ts_ajouter_contexte(table_symb  table, char *context);
symbole * ts_ajouter_identificateur(table_symb  table, char *context, char *id,  int type, int size);

void ts_free_table(table_symb  table);
void print_context(contexte * context, int size);
void print_liste_symbole(symbole * symb, int size);
void ts_print(table_symb  table);

#endif
