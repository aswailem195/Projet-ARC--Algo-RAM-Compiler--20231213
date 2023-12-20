#include "../include/codegen.h"

void codegen(asa *p)
{  

  if(!p) return;


  switch (p->type){
  case typePROG:
    codePROG(p);
    break;
  case typeDECS:
    codeDECS(p);
    break;
  case typeLIST_DECLA:
    codeLIST_DECLA(p);
    break;
  case typeDECLA_VAR:
    codeDECLA_VAR(p);
    break;
  
  case typeLIST_INST:
    codeLIST_INST(p);
    break;

  case typeNB:
    codeNB(p);
    break;
  case typeOP:
    codeOP(p);
  case typeAFF : 
     codeAFF(p) ;

  case typeID :
      codeID(p) ;
  

  default:
    break;
  }
}


//________________________________

void codePROG(asa * p ) {
  codegen(p->prog.DECLA) ;
  codegen(p->prog.INST) ;

}

void codeDECS(asa * p ) { 
  codegen(p->decs.DEC); 
  codegen(p->decs.next) ;


}
void codeLIST_DECLA(asa * p ) {
  codegen(p->list_decla.DEC) ;
  codegen(p->list_decla.next) ;
}
void codeLIST_INST(asa * p ) {
  codegen(p->list_inst.INST) ;
  codegen(p->list_inst.next) ;
}




void codeID(asa * p){ 
  p->affect.id->memadr = 0 ;
  int adr = p->affect.id->memadr ;
  //adr += 32 ;  //ici cest la valeur
  fprintf(exefile,"LOAD #%-8d ;\n", adr );
  fprintf(exefile,"ADD 5 ;\n" ); //
  fprintf(exefile, "STORE 1 ;\n" ) ;
  
  


}

void codeDECLA_VAR(asa * p ){
  
}

void codeAFF(asa * p){  
  int adr = p->affect.id->memadr ;
  //adr += 32 ;  //ici cest la valeur
  codeID(p->affect.id) ;
  codeNB(p->affect.droit) ;
  fprintf(exefile,"STORE @1  ;\n");

  

  





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
