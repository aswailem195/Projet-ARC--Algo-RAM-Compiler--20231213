#include "../include/semantic.h"

void semantic(asa *p){
  if(!p) return;
  switch (p->type){
  case typeNB:
    semantic_NB(p);
    break;
  case typeOP:
    semantic_OP(p);
    break;
  default:
    break;
  }
}



void semantic_NB(asa * p)
{
  p->codelen = 1;
}




void semantic_OP(asa * p)
{
  switch (p->op.ope){
  case '+':  // operateur binaire associatif a gauche (+ - * / % )
  case '-':
  case '*':
  case '/':
  case '%':
    semantic(p->op.noeud[0]);
    semantic(p->op.noeud[1]);
    break;
  }
}
