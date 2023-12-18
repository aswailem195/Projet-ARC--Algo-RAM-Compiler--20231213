#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ts.h"
#include "asa.h"
#include "codegen.h"

void semantic(asa *p);
void semantic_NB(asa * p);
void semantic_OP(asa * p);


extern table_symb TABLE_SYMBOLES;

#endif
