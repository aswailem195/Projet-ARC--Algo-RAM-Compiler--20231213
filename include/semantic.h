#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ts.h"
#include "asa.h"
#include "codegen.h"


extern table_symb TABLE_SYMBOLES;




void semantic(asa *p);
void semantic_NB(asa * p);
void semantic_OP(asa * p);



void semantic_ID(asa * p) ;
void semantic_DECLA_POIN(asa * p);
void semantic_DECLA_TAB(asa * p) ;
void semantic_DECS(asa * p) ;
void semantic_LIST_DECLA(asa * p) ;
void semantic_MAIN(asa * p) ;
void semantic_LIST_INST(asa * p) ;
void semantic_INST(asa * p) ;
void semantic_AFF(asa * p) ;
void semanticINST_LIRE(asa *p) ;
void semantic_DECLA_VAR(asa * p) ;


void semantic_STRUCT_TQ(asa * p);
void semantic_STRUCT_SI(asa * p);
void semantic_DEC_FON(asa * p);
void semantic_LIS_DEC_FON(asa *p);
void semantic_PARAM(asa * p);
void semantic_RENVOYER(asa * p) ;

void  semantic_PARAM_APPL(asa *p) ;
void semantic_L_PARM_APPL(asa *p,char *nom_F) ;
void semantic_ALLOCATION(asa *p) ;








int  error_semantic(const char *s) ;
void rechercher_identificateur( char* id , char * text ) ;




#endif
