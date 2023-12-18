#ifndef ASA_H
#define ASA_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define  MAX_SIZE_FIELD_NAME  12
#define  MAX_SIZE_FIELD_VAL   32
#define  TXT_RED    "\x1b[31m"
#define  TXT_GREEN  "\x1b[32m"
#define  TXT_BLUE   "\x1b[34m"
#define  TXT_BOLD   "\x1b[1m"
#define  TXT_NULL   "\x1b[0m"

#define TYPE_ENTIER  'e'
#define TYPE_TABLEAU 't'
#define TYPE_PTR     'p'
#define TYPE_FCT     'f'
//___________________type__________________
typedef enum {typeNB, typeOP, typeID,DECLA_VAR,typeAFF ,typeINST,typeLIST_INST,typeDECLA_VAR} typeNoeud;

typedef  enum {t_AFF ,t_EXP} t_INST ;


//___________________feuille__________________

typedef struct {
  int val;
} feuilleNb;

//L'identificateur
typedef struct {
  char nom[32];
} feuilleId;


//___________________noeud__________________
typedef struct {
  int ope;
  char * nom ;
  struct asa * noeud[2];
} noeudOp;
typedef struct {
  struct asa *id ;
  struct asa *droit ;
}noeuAFFECT ;

typedef struct 
{ 
   
  struct asa *INST ;
  
}noeudINST ;

typedef struct {
  struct asa *INST ;
  struct asa *next ;
}noeudLIST_INST ;


typedef struct {
  struct asa *DECLA ;
  struct asa *next ;
}cree_noeudDECLA_VAR ;





//_____________________asa_____________________
typedef struct asa{
  typeNoeud type;
  int memadr;
  int codelen;
  union {
    feuilleNb nb;
    noeudOp op;
    feuilleId id;
    noeuAFFECT affect ;
    noeudINST  inst;
    noeudLIST_INST  list_inst;
    cree_noeudDECLA_VAR decla_var ;
  };
} asa;





//__________________
asa * creer_feuilleNB( int value );
asa * creer_noeudOP( int ope, asa * p1, asa * p2 );
asa * creer_feuilleID(char* nom);

asa * creer_noeudAffic( char* id , asa * p1 );
asa * creer_noeudINST(asa* p1) ;
asa * creer_noeudLIST_INST(asa* p1 ,asa* p2) ;
asa * creer_noeudDECLA_VAR( char* id   ,asa* p1 );





//____________________
void free_asa(asa *p);


//__________________
void print_asa(asa * p);
void print_typeOP(asa *p);
void print_typeNB(asa *p);


void print_asa_dot_node(FILE *output, asa *p);
void print_asa_dot_edge(FILE *output, asa *parent, asa *child) ;
void print_asa_dot_recursive(FILE *output, asa *p);
int print_asa_dot( asa *p);

void error_asa(const char * s);

#endif
