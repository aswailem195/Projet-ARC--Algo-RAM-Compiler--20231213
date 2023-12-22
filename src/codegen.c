#include "../include/codegen.h"
#include <stdio.h>

int CODELEN = 3;
int nb_VAR_Fonctio;
void codegen(asa *p) {

  if (!p)
    return;

  switch (p->type) {
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

  case typeAFF:
    codeAFF(p);
    break;

  default:
    break;
  }
}

//________________________________

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
  fprintf(
      exefile,
      "DEC %-9d ; FIN DECLA_VA on a decriment le indice de sommet de pile\n",
      RAM_OS_ADR_REG); // 3
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

  fprintf(exefile, "LOAD #%-8d ;codeID %s\n", adr, p->id.nom);
  fprintf(exefile, "ADD 2 ;\n");
  fprintf(exefile, "STORE 1 ;  \n");
  fprintf(exefile, "LOAD @1 ;  \n");
  CODELEN += 4;
}

void codeDECLA_VAR(asa *p) {
  // int adr = p->decla_var.ID->memadr ;
  // fprintf(exefile, "LOAD #%-8d ; %s\n", adr,p->id.nom);
  // fprintf(exefile, "ADD 2 ;\n");
  // fprintf(exefile, "STORE 1 ;  fincodeID\n");
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
    fprintf(exefile, "JUMZ %d ;\n",CODELEN+3-1+2);//3 les suit  1 le primier incide=0 dans RAM 2 inst suter  
    fprintf(exefile, "LOAD #0;\n");
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "LOAD #1;\n");
    fprintf(exefile, "STORE @%-6d ;\n", RAM_OS_ADR_REG);
    fprintf(exefile, "DEC %-9d ;\n", RAM_OS_ADR_REG);
    CODELEN += 7;

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
