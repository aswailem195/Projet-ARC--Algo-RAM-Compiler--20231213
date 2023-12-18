#include "../include/codegen.h"

void codegen(asa *p)
{  

  if(!p) return;


  switch (p->type){
  case typeNB:
    codeNB(p);
    break;
  case typeOP:
    codeOP(p);
  default:
    break;
  }
}



void codeNB(asa * p){
  //on stocke la valeur de l'entier dans l'ACC
  fprintf(exefile,"LOAD #%-7d ;\n", p->nb.val);
}




void codeOP(asa * p){
  /*
   * On commence par générer le code des noeuds dans l'ordre de l'associativité
   */
  switch (p->op.ope){
    /*
     * Operateurs associatifs à gauche, on génère d'abord la partie droite
     * on l'empile et on génère la partie gauche
     */
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':    
    codegen(p->op.noeud[1]); 
    fprintf(exefile,"INC %-9d ;\n", RAM_OS_STK_REG);
    fprintf(exefile,"STORE @%-6d ;\n", RAM_OS_STK_REG);  // Ici on empile
    codegen(p->op.noeud[0]);
    break;
  default:
    break;
  }

  /*
   * On gère ensuite les opérateurs au cas par cas et on dépile
   */

  switch (p->op.ope){
  case '+':
    fprintf(exefile,"ADD @%-8d ;\nDEC %-9d ;\n", RAM_OS_STK_REG, RAM_OS_STK_REG);
    break;
  case '-':
    fprintf(exefile,"SUB @%-8d ;\nDEC %-9d ;\n", RAM_OS_STK_REG, RAM_OS_STK_REG);
    break;
  case '*':
    fprintf(exefile,"MUL @%-8d ;\nDEC %-9d ;\n", RAM_OS_STK_REG, RAM_OS_STK_REG);
    break;
  case '/':
    fprintf(exefile,"DIV @%-8d ;\nDEC %-9d ;\n", RAM_OS_STK_REG, RAM_OS_STK_REG);
    break;
  case '%':
    fprintf(exefile,"MOD @%-8d ;\nDEC %-9d ;\n", RAM_OS_STK_REG, RAM_OS_STK_REG);
    break;
  default:
    break;
  }  
}
