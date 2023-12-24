#include "../include/codegen.h"
#include <stdio.h>

char CTXTC[32] = "GLOBAL";

int CODELEN = 3;
int nb_VAR_Fonctio;
void codegen(asa *p) {

  if (!p)
    return;

  switch (p->type) {

  case typeRENVOYER:
    codeRENVOYER(p);
    break;

  case typeAPPFONC:
    codeAPPFONC(p);
    break;

  case typeDEC_FON:
    codeDEC_FON(p);
    break;


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
  case typeID:
    printf("%d", p->type);
    codeID(p);

    break;
  case typeINST_ECRIRE:
    codeIST_ECRIRE(p);
    break;
  case typeOP:

    codeOP(p);
    break;
  case typeNB:
    codeNB(p);
    break;
  case typeINST_LIRE:
    codeINST_LIRE(p);
    break;
  case typeMAIN:

    codeMAIN(p);
    break;

  case typeLIST_INST:
    codeLIST_INST(p);
    break;
  case typeSTRUCT_SI:
    codeSTRUCT_SI(p);
    break;
  case typeSTRUCT_TQ:
   codeSTRUCT_TQ(p);
    break;
  

  case typeAFF:
    codeAFF(p);
    break;

  default:
    break;
  }
}

//________________________________
void codeRENVOYER(asa * p) {
 /* on consider que a la fin de coden de inst le resulta rest dans acc */
  codegen(p->renvoyer.INST) ;
}

void codeAPPFONC(asa * p){
  /* on stock la valeur de instrction pour revien */ 

  fprintf(exefile, "LOAD #%-9d ; APPLFON stock la valeur de instrction pour revien\n", CODELEN + p->codelen+2-1) ;//3 pour inst suivant 1 apres le 3 - indic comence a 0 
  fprintf(exefile, "STORE %-9d ; \n", RAM_OS_EMPILER_ADR) ;
  

  /**/
  int adr = p->memadr; 
  codegen(p->appfonc.ID) ;

  fprintf(exefile, "JUMP @0       ; FIN DE FON \n" ) ;


}
void codeDEC_FON(asa * p){
  
  /* la case mem pour la fonction dans la pile, parmi les indices
   de début des instructions de la fonction 
  */


  // lode de debut de inst de fonction 
  fprintf(exefile, "LOAD #%-9d ; DECLA_FON debut inst de fonction  \n", CODELEN+6-1) ;//6 instraction suivant 
  fprintf(exefile, "STORE %-9d ; on le stock dans le sdr de fonc  \n", p->dec_fon.ID->memadr) ;

 /* stokeer le fin de fonction utile pour le jumb*/
  fprintf(exefile, "LOAD #%-9d ;  \n", CODELEN+p->codelen+1-1) ;
  fprintf(exefile, "STORE %-9d ;  \n", RAM_OS_EMPILER_ADR) ;
  fprintf(exefile, "JUMP @%-9d ; jumb pour ne touch le ins de fonction qund dec\n", RAM_OS_EMPILER_ADR) ;

  CODELEN+= 5;

  // c'est  le decla de fonction  
  //fprintf(exefile, "INC %-9d ; DECLA_FON \n", RAM_OS_ADR_REG) ;


  /* */
  codegen(p->dec_fon.PARAM);
  /* */ 
  codegen(p->dec_fon.DECS) ;
  /**/
  codegen(p->dec_fon.LIST_INST) ; 


  fprintf(exefile, "JUMP @%-9d ; FIN DE FON \n", RAM_OS_EMPILER_ADR) ;
  






}
void codeSTRUCT_TQ(asa *p) {
  int Buffer = CODELEN ;
  codegen(p->struct_tq.condition) ;
  fprintf(exefile, "JUMZ %d ;  STRUCT_TQ \n",CODELEN+1-1+p->struct_tq.inst->codelen+2);
  CODELEN++ ;
  codegen(p->struct_tq.inst) ;
  fprintf(exefile, "JUMP %d ;  STRUCT TQ fin \n",Buffer);
  CODELEN++;




}

void codeSTRUCT_SI(asa * p){ 
  
  codegen(p->struct_si.condition);
  fprintf(exefile, "JUMZ %d ;  STRUCT_SI \n",CODELEN+1-1+p->struct_si.inst_si->codelen+2);
  CODELEN++ ;
  codegen(p->struct_si.inst_si) ;
  fprintf(exefile, "JUMP %d ;  STRUCT_SI NON \n",CODELEN+1-1+p->struct_si.inst_si_non->codelen);
  CODELEN += 1;
  codegen(p->struct_si.inst_si_non) ;


  
}

void codeINST_LIRE(asa *p) {

  // ID <- LIRE()
  codegen(
      p->inst_lire.ID); // raminer la address du  ID  et stocke dans adress 1
  fprintf(exefile, "READ ;  INST_LIRE\n");
  fprintf(exefile, "STORE @1 ; \n");
  CODELEN += 2;
}

void codeMAIN(asa *p) {
  if (p->main.DEC) {
    codegen(p->main.DEC);
  }
  if (p->main.DEC_FN) {
    codegen(p->main.DEC_FN);
  }
  codegen(p->main.PROG);
}
void codePROG(asa *p) {
  codegen(p->prog.DECLA);
  codegen(p->prog.INST);
  
}

void codeDECS(asa *p) {
  codegen(p->decs.DEC);
  if (p->decs.next) {
    codegen(p->decs.next);
  }
}
void codeLIST_DECLA(asa *p) {
  codegen(p->list_decla.DEC);
  if (p->list_decla.next) {
    codegen(p->list_decla.next);
  }
  /*fprintf(
      exefile,
      "DEC %-9d ; FIN DECLA_VA on a decriment le indice de sommet de pile\n",
      RAM_OS_ADR_REG); // 3*/
  CODELEN += 1;
}
void codeLIST_INST(asa *p) {

  codegen(p->list_inst.INST);
  if (p->list_inst.next) {
    codegen(p->list_inst.next);
  }
}

void codeIST_ECRIRE(asa *p) {

  if (p->inst_ecrire.EXP != NULL) {
    codegen(p->inst_ecrire.EXP);
  }

  fprintf(exefile, "WRITE ; \n"); //
  CODELEN += 1;
}

void codeID(asa *p) {

  int adr = p->memadr; // on va modifirer apes
  //printf("fffff %s" ,p->id.ctxt) ;

if (strcmp(p->id.ctxt, "locale") == 0) {
    fprintf(exefile, "LOAD #%-8d ;codeID %s\n", adr, p->id.nom);
    fprintf(exefile, "ADD 2 ;\n");
    fprintf(exefile, "STORE 1 ;  \n");
    fprintf(exefile, "LOAD @1 ;  \n");
    CODELEN += 4;
} else {
    fprintf(exefile, "LOAD %-8d ;codeID %s\n", p->memadr, p->id.nom);
    CODELEN += 1;
}
}

void codeDECLA_VAR(asa *p) {
  // int adr = p->decla_var.ID->memadr ;
  // fprintf(exefile, "LOAD #%-8d ; %s\n", adr,p->id.nom);
  // fprintf(exefile, "ADD 2 ;\n");
  // fprintf(exefile, "STORE 1 ;  fincodeID\n");


  // decla variable ce alloer de espace dans le pile 
  fprintf(exefile, "INC %-9d ; DECLA_VA\n", RAM_OS_ADR_REG); // 3
  CODELEN += 1;
  // codegen(p->decla_var.ID);

  // fprintf(exefile, "INC %-9d ;\n", RAM_OS_STK_REG);

  /*
  if (p->decla_var.inst_mis) {
    codegen(p->decla_var.inst_mis);
  }
  */
}

void codeAFF(asa *p) {
  // int adr = p->affect.id->memadr;
  //  adr += 32 ;  //ici cest la valeur
  // printf ("id ho : %d  %s",p->affect.id->memadr ,p->affect.id->id.nom ) ;

  codegen(p->affect.droit); // on considre que il mit la valuer dans ACC
  fprintf(exefile, "INC %-9d ; AFF\n", RAM_OS_ADR_REG);
  fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
  CODELEN += 2;
  codegen(p->affect.id);
  fprintf(exefile, "LOAD @%-7d ;\n", RAM_OS_ADR_REG); // resulta de droit
  fprintf(exefile, "STORE @1  ; \n");
  CODELEN += 2;
}

void codeNB(asa *p) {
  // on stocke la valeur de l'entier dans l'ACC
  fprintf(exefile, "LOAD #%-7d ; codeNB\n", p->nb.val);
  CODELEN += 1;
}

void codeOP(asa *p) {

  // printf("const char *restrict format, ...%d", p->type);
  /*
   * On commence par générer le code des noeuds dans l'ordre de l'associativité
   */

  switch (p->op.ope) {
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
    fprintf(exefile, "INC %-9d ; codeOP\n", RAM_OS_ADR_REG);
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    CODELEN += 2;
    codegen(p->op.noeud[0]);
    break;
  case '!':
    codegen(p->op.noeud[0]);
    fprintf(exefile, "INC %-9d ;  codeOP ! \n", RAM_OS_ADR_REG);
    fprintf(exefile, "JUMZ %d ;\n",
            CODELEN + 3 - 1 +
                2); // 3 les suit  1 le primier incide=0 dans RAM 2 inst suter
    fprintf(exefile, "LOAD #0;\n");
    fprintf(exefile, "JUMP %-6d ;\n", CODELEN +4 + 2-1);
    fprintf(exefile, "LOAD #1;\n");
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "DEC %-9d ;\n", RAM_OS_ADR_REG);
    CODELEN += 7;

    break;
  case '>':
    codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ; codeOP > \n", RAM_OS_ADR_REG);
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    CODELEN +=2;
    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "JUMG %d ;\n", CODELEN +2 + 3-1 );
    fprintf(exefile, "LOAD #0;\n");
    fprintf(exefile, "JUMP %-6d ;\n", CODELEN +4 + 2-1);
    fprintf(exefile, "LOAD #1;\n");
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "DEC %-9d ;\n", RAM_OS_ADR_REG);
    CODELEN +=7;
    break;
    case '<':
    codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ; codeOP > \n", RAM_OS_ADR_REG);
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    CODELEN +=2;
    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "JUML %d ;\n", CODELEN +2 + 3-1 );
    fprintf(exefile, "LOAD #0;\n");
    fprintf(exefile, "JUMP %-6d ;\n", CODELEN +4 + 2-1);
    fprintf(exefile, "LOAD #1;\n");
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "DEC %-9d ;\n", RAM_OS_ADR_REG);
    CODELEN +=7;
    break;
    case '=':
    codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ; codeOP > \n", RAM_OS_ADR_REG);
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    CODELEN +=2;
    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "JUMZ %d ;\n", CODELEN +2 + 3-1 );
    fprintf(exefile, "LOAD #0;\n");
    fprintf(exefile, "JUMP %-6d ;\n", CODELEN +4 + 2-1);
    fprintf(exefile, "LOAD #1;\n");
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "DEC %-9d ;\n", RAM_OS_ADR_REG);
    CODELEN +=7;
    break;


    case OP_INF_EG:
     codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ; codeOP > \n", RAM_OS_ADR_REG);
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    CODELEN +=2;
    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "JUMG %d ;\n", CODELEN +2 + 3-1 );
    fprintf(exefile, "LOAD #1;\n");
    fprintf(exefile, "JUMP %-6d ;\n", CODELEN +4 + 2-1);
    fprintf(exefile, "LOAD #0;\n");
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "DEC %-9d ;\n", RAM_OS_ADR_REG);
    CODELEN +=7;
    break;


    case OP_SUP_EG:
     codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ; codeOP > \n", RAM_OS_ADR_REG);
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    CODELEN +=2;
    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "JUML %d ;\n", CODELEN +2 + 3-1 );
    fprintf(exefile, "LOAD #1;\n");
    fprintf(exefile, "JUMP %-6d ;\n", CODELEN +4 + 2-1);
    fprintf(exefile, "LOAD #0;\n");
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "DEC %-9d ;\n", RAM_OS_ADR_REG);
    CODELEN +=7;
    break;

    case OP_DIFF :
    codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ; codeOP > \n", RAM_OS_ADR_REG);
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    CODELEN +=2;
    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "JUMZ %d ;\n", CODELEN +2 + 3-1 );
    fprintf(exefile, "LOAD #1;\n");
    fprintf(exefile, "JUMP %-6d ;\n", CODELEN +4 + 2-1);
    fprintf(exefile, "LOAD #0;\n");
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "DEC %-9d ;\n", RAM_OS_ADR_REG);
    CODELEN +=7;
    break;
     case '&' :
    codegen(p->op.noeud[1]);
    fprintf(exefile, "JUMZ %d ;\n", CODELEN +1+p->op.noeud[0]->codelen + 4-1 );
    CODELEN +=1;
    codegen(p->op.noeud[0]);
    fprintf(exefile, "JUMZ %d ;\n", CODELEN +1 + 3-1 );
    fprintf(exefile, "LOAD #1;\n");
    fprintf(exefile, "JUMP %-6d ;\n", CODELEN +3 + 2-1);
    fprintf(exefile, "LOAD #0;\n");

    break;

     case '|' :
    codegen(p->op.noeud[1]);
    fprintf(exefile, "JUMG %d ;\n", CODELEN +1+p->op.noeud[0]->codelen + 4-1 );
    CODELEN +=1;
    codegen(p->op.noeud[0]);
    fprintf(exefile, "JUMG %d ;\n", CODELEN +1 + 3-1 );
    fprintf(exefile, "LOAD #0;\n");
    fprintf(exefile, "JUMP %-6d ;\n", CODELEN +3 + 2-1);
    fprintf(exefile, "LOAD #1;\n");

    break;








  default:
    break;
  }

  /*
   * On gère ensuite les opérateurs au cas par cas et on dépile
   */

  switch (p->op.ope) {
  case '+':
    fprintf(exefile, "ADD @%-8d ;\nDEC %-9d ;\n", RAM_OS_ADR_REG,
            RAM_OS_ADR_REG);
    CODELEN += 2;
    break;
  case '-':
    fprintf(exefile, "SUB @%-8d ;\nDEC %-9d ;\n", RAM_OS_ADR_REG,
            RAM_OS_ADR_REG);
    CODELEN += 2;
    break;
  case '*':
    fprintf(exefile, "MUL @%-8d ;\nDEC %-9d ;\n", RAM_OS_ADR_REG,
            RAM_OS_ADR_REG);
    CODELEN += 2;
    break;
  case '/':
    fprintf(exefile, "DIV @%-8d ;\nDEC %-9d ;\n", RAM_OS_ADR_REG,
            RAM_OS_ADR_REG);
    CODELEN += 2;
    break;
  case '%':
    fprintf(exefile, "MOD @%-8d ;\nDEC %-9d ;\n", RAM_OS_ADR_REG,
            RAM_OS_ADR_REG);
    CODELEN += 2;
    break;
  default:
    break;
  }
}
