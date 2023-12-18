#ifndef CODEGEN_H
#define CODEGEN_H

#include "asa.h"
#include "ram_os.h"

extern FILE * exefile;

void codegen(asa *p);

void codeNB(asa * p);
void codeOP(asa * p);
#endif
