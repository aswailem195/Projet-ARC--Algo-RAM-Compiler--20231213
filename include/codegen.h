#ifndef CODEGEN_H
#define CODEGEN_H

#include "asa.h"
#include "ram_os.h"

extern FILE * exefile;

void codegen(asa *p);

void codeNB(asa * p);
void codeOP(asa * p);
void codeAFF(asa * p) ;
void codePROG(asa * p ) ;
void codeDECS(asa * p ) ;
void codeLIST_DECLA(asa * p ) ; 
void codeLIST_INST(asa * p ) ;
void codeDECLA_VAR(asa * p ) ;
void codeMAIN(asa *p ) ;
void codeIST_ECRIRE(asa *p ) ;
void codeINST_LIRE(asa *p) ;
void codeSTRUCT_SI(asa * p) ;
void codeSTRUCT_TQ(asa * p) ;

void codeID(asa * p) ;
#endif
