#include "asa.h"

void yyerror(const char *s);
int yylineno=0;

int main(){
  asa *p1 = creer_feuilleNB(12);
  asa *p2 = creer_feuilleNB(5);
  asa *p3 = creer_feuilleNB(0);
  asa *p4 = creer_noeudOP('+', p1,p2);
  asa *p5 = creer_noeudOP('*', p4, p3);
  
  print_asa(p5);
  free_asa(p5);
  return 0;
}
