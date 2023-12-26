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

   case typeINT:
    codeINT(p);
    break;
   case typeLIST_VAR:
    codeLIST_PARAM(p);
    break;

  case typeAPPFONC:
    codeAPPFONC(p);
    break;
  case typeLIS_DEC_FON:
    codeLIS_DEC_FON(p);
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

/*________________________________RENVOYER____________________________*/
void codeRENVOYER(asa *p) {
  /* on consider que a la fin de coden de inst le resulta rest dans acc */
  codegen(p->renvoyer.INST);
}

/*________________________________APPFONC____________________________*/

void codeINT(asa *p) {
 int adr = p->ent.id->id.adr ;
 int adr_app = p->ent.id->id.adr_app ;
 fprintf(exefile,"LOAD #%-9d ;CODELEN : %d  apple de fonction par valeur  \n", adr_app, ++CODELEN);
 fprintf(exefile,"ADD 2 ;CODELEN : %d   \n", ++CODELEN);
 fprintf(exefile,"STORE 1 ;CODELEN : %d  \n", ++CODELEN);
 fprintf(exefile,"LOAD #%-9d ;CODELEN : %d    \n", adr, ++CODELEN);
 fprintf(exefile,"ADD 2 ;CODELEN : %d   \n", ++CODELEN);
 fprintf(exefile,"LOAD @0 %-9d ;CODELEN : %d    \n", adr, ++CODELEN);
 fprintf(exefile,"STORE @1 ;CODELEN : %d  \n", ++CODELEN);




}

void codeLIST_PARAM(asa *p) { 
  codegen(p->list_var.var) ;
  codegen(p->list_var.next) ;
  
  
}

void codeLIS_DEC_FON(asa *p) {
  codegen(p->lis_dec_fon.dec_fon);
  codegen(p->lis_dec_fon.next);
}

void codeAPPFONC(asa *p) {


  codegen(p->appfonc.LIST_PARAM) ;
  /* on stock la valeur de instrction pour revien */
  CODELEN++;
  

  fprintf(exefile,
          "LOAD #%-9d ;CODELEN : %d APPLFON stock la valeur de instrction pour "
          "revien\n",
          CODELEN  + 4,
          CODELEN); // 3 pour inst suivant 1 apres 

  fprintf(exefile, "STORE %-9d ;CODELEN : %d \n", RAM_OS_EMPILER_ADR,
          ++CODELEN);

  /**/
  int adr = p->memadr;
  codegen(p->appfonc.ID);

  fprintf(exefile, "JUMP @0       ;CODELEN : %d FIN DE FON \n", ++CODELEN);
}


void codeDEC_FON(asa *p) {



  // c'est  le decla de fonction
  // fprintf(exefile, "INC %-9d ; DECLA_FON \n", RAM_OS_ADR_REG) ;

  /* */
  codegen(p->dec_fon.PARAM);
  /* */
  codegen(p->dec_fon.DECS);

    /* la case mem pour la fonction dans la pile, parmi les indices
   de début des instructions de la fonction
  */

  // lode de debut de inst de fonction
  CODELEN++;
  fprintf(exefile,
          "LOAD #%-9d ;CODELEN : %d  DECLA_FON debut inst de fonction  \n",
          CODELEN + 5 , CODELEN); // 5 instraction suivant +1
  
  fprintf(exefile,
          "STORE %-9d ; CODELEN : %d on le stock dans le sdr de fonc  \n",
          p->dec_fon.ID->memadr, ++CODELEN);

  /* stokeer le fin de fonction utile pour le jumb*/
  CODELEN++;
  fprintf(exefile, "LOAD #%-9d ;CODELEN : %d  \n", CODELEN + p->dec_fon.LIST_INST->codelen + 3 +1,
          CODELEN);
  
  fprintf(exefile, "STORE %-9d ;CODELEN : %d  \n", RAM_OS_EMPILER_ADR,
          ++CODELEN);
  fprintf(exefile,
          "JUMP @%-9d ;CODELEN : %d  jumb pour ne touch le ins de fonction "
          "qund dec\n",
          RAM_OS_EMPILER_ADR, ++CODELEN);
  /**/
  codegen(p->dec_fon.LIST_INST);

  fprintf(exefile, "JUMP @%-9d ;CODELEN : %d FIN DE FON \n", RAM_OS_EMPILER_ADR,
          ++CODELEN);
}

/*_______________________________________TQ_______________________________________________________*/
void codeSTRUCT_TQ(asa *p) {
  int Buffer = CODELEN;
  codegen(p->struct_tq.condition);
  CODELEN++;
  fprintf(exefile, "JUMZ %d ; CODELEN : %d  STRUCT_TQ \n",
          CODELEN   + p->struct_tq.inst->codelen + 2, CODELEN);
  
  codegen(p->struct_tq.inst);
  fprintf(exefile, "JUMP %d ;CODELEN : %d  STRUCT TQ fin \n", Buffer+1,
          ++CODELEN);
}
/*_______________________________________si_______________________________________________________*/

void codeSTRUCT_SI(asa *p) {

  codegen(p->struct_si.condition);

  CODELEN++;
  fprintf(exefile, "JUMZ %d ; CODELEN : %d STRUCT_SI \n",
          CODELEN + p->struct_si.inst_si->codelen + 2, CODELEN);

  codegen(p->struct_si.inst_si);

  // ou on est + l'inst lui meme + ins de si  non -1 pource que on comencer par0

  int taill_inst =
      (p->struct_si.inst_si_non ? p->struct_si.inst_si_non->codelen : 0);
  // printf("code  %d   %d   %d\n",CODELEN ,taill_inst
  // ,p->struct_si.inst_si_non->codelen) ;
  CODELEN += 1;
  fprintf(exefile, "JUMP %d ; CODELEN : %d STRUCT_SI NON \n",
          CODELEN + taill_inst + 1, CODELEN);

  codegen(p->struct_si.inst_si_non);
}
/*_______________________________________lire_______________________________________________________*/

void codeINST_LIRE(asa *p) {

  // ID <- LIRE()
  codegen(
      p->inst_lire.ID); // raminer la address du  ID  et stocke dans adress 1
  fprintf(exefile, "READ ; CODELEN : %d  INST_LIRE\n", ++CODELEN);
  fprintf(exefile, "STORE @1 ; CODELEN : %d \n", ++CODELEN);
}

/*_______________________________________main
 * _______________________________________________________*/

void codeMAIN(asa *p) {

  int init = 32;
  fprintf(exefile, "LOAD #%-7d ;\n", init);
  fprintf(exefile, "STORE %-6d ; deput pile\n", RAM_OS_STK_REG);
  fprintf(exefile, "LOAD #%-7d ;\n", init+p->main.nb_valiable_local);
  fprintf(exefile, "STORE %-6d  ; sommet pile \n",RAM_OS_ADR_REG);


  if (p->main.DEC) {
    codegen(p->main.DEC);
  }
  if (p->main.L_DEC_FN) {
    codegen(p->main.L_DEC_FN);
  }
  codegen(p->main.PROG);
  fprintf(exefile, "STOP ; ");
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

  fprintf(exefile, "WRITE ; CODELEN : %d \n", ++CODELEN); //
}
/*_______________________________________id_______________________________________________________*/

void codeID(asa *p) {

  int adr = p->memadr; // on va modifirer apes
  // printf("fffff %s" ,p->id.ctxt) ;

  if (strcmp(p->id.ctxt, "locale") == 0) {
    fprintf(exefile, "LOAD #%-8d ; CODELEN : %d  codeID locale %s\n", adr,
            ++CODELEN, p->id.nom);
    fprintf(exefile, "ADD 2 ; CODELEN : %d\n", ++CODELEN);
    fprintf(exefile, "STORE 1 ; CODELEN : %d  \n", ++CODELEN);
    fprintf(exefile, "LOAD @1 ; CODELEN : %d \n", ++CODELEN);

  } else {
    fprintf(exefile, "LOAD %-8d ; CODELEN : %d codeID global  %s\n", p->memadr,
            ++CODELEN, p->id.nom);
  }
}
/*_______________________________________var_______________________________________________________*/

void codeDECLA_VAR(asa *p) {

  /*fprintf(exefile, "INC %-9d ; CODELEN : %d DECLA_VA\n", RAM_OS_ADR_REG,
          ++CODELEN); // 3*/

  if (p->decla_var.inst_mis) {
    codegen(p->decla_var.inst_mis);
    fprintf(exefile, "INC %-9d ; CODELEN : %d AFF\n", RAM_OS_ADR_REG, ++CODELEN);
  fprintf(exefile, "STORE @%-6d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
  
   codegen(p->affect.id);
  fprintf(exefile, "LOAD @%-7d ;CODELEN : %d\n", RAM_OS_ADR_REG,
          ++CODELEN); // resulta de droit
  fprintf(exefile, "DEC %-9d ;CODELEN : %d  AFF\n", RAM_OS_ADR_REG, ++CODELEN);
  fprintf(exefile, "STORE @1  ;CODELEN : %d \n", ++CODELEN);
  }
}
/*_______________________________________AFF_______________________________________________________*/

void codeAFF(asa *p) {

  codegen(p->affect.droit); // on considre que il mit la valuer dans ACC
  fprintf(exefile, "INC %-9d ; CODELEN : %d AFF\n", RAM_OS_ADR_REG, ++CODELEN);
  fprintf(exefile, "STORE @%-6d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

  codegen(p->affect.id);
  fprintf(exefile, "LOAD @%-7d ;CODELEN : %d\n", RAM_OS_ADR_REG,
          ++CODELEN); // resulta de droit
  fprintf(exefile, "DEC %-9d ;CODELEN : %d  AFF\n", RAM_OS_ADR_REG, ++CODELEN);
  fprintf(exefile, "STORE @1  ;CODELEN : %d \n", ++CODELEN);
}

/*_______________________________________EXP_______________________________________________________*/

void codeNB(asa *p) {
  // on stocke la valeur de l'entier dans l'ACC
  fprintf(exefile, "LOAD #%-7d ;CODELEN : %d codeNB\n", p->nb.val, ++CODELEN);
}

void codeOP(asa *p) {

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
    fprintf(exefile, "INC %-9d ; CODELEN : %d codeOP\n", RAM_OS_ADR_REG,
            ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d\n", RAM_OS_ADR_REG, ++CODELEN);

    codegen(p->op.noeud[0]);
    break;
  case '!':
    codegen(p->op.noeud[0]);
    fprintf(exefile, "INC %-9d ;CODELEN : %d  codeOP ! \n", RAM_OS_ADR_REG,
            ++CODELEN);
    fprintf(exefile, "JUMZ %d ; CODELEN : %d\n", CODELEN + 3 - 1 + 2,
            CODELEN); // 3 les suit  1 le primier incide=0 dans RAM 2 inst suter
    CODELEN++;
    fprintf(exefile, "LOAD #0;CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "JUMP %-6d ;CODELEN : %d \n", CODELEN + 4 + 2, CODELEN);
    CODELEN++;
    fprintf(exefile, "LOAD #1; CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d\n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    break;
  case '>':
    codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ;CODELEN : %d  codeOP > \n", RAM_OS_ADR_REG,
            ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    
    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    CODELEN++;
    fprintf(exefile, "JUMG %d ;CODELEN : %d \n", CODELEN + 3, CODELEN);

    fprintf(exefile, "LOAD #0;CODELEN : %d \n", ++CODELEN);
    CODELEN++;
    fprintf(exefile, "JUMP %-6d ;CODELEN : %d \n", CODELEN + 2, CODELEN);
    fprintf(exefile, "LOAD #1;CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ;CODELEN : %d\n", RAM_OS_ADR_REG, ++CODELEN);

    break;
  case '<':
    codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ;CODELEN : %d  codeOP < \n", RAM_OS_ADR_REG,
            ++CODELEN);
    fprintf(exefile, "STORE @%-6d ; CODELEN : %d \n", RAM_OS_ADR_REG,
            ++CODELEN);

    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ; CODELEN : %d\n", RAM_OS_ADR_REG, ++CODELEN);
    CODELEN++;
    fprintf(exefile, "JUML %d ; CODELEN : %d \n", CODELEN + 3, CODELEN);
    
    fprintf(exefile, "LOAD #0;CODELEN : %d \n", ++CODELEN);
    CODELEN++;
    fprintf(exefile, "JUMP %-6d ;CODELEN : %d \n", CODELEN + 2, CODELEN);
    
    fprintf(exefile, "LOAD #1;CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    break;
  case '=':
    codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ; CODELEN : %d codeOP = \n", RAM_OS_ADR_REG,
            ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    CODELEN++;
    fprintf(exefile, "JUMZ %d ;CODELEN : %d \n", CODELEN + 3, CODELEN);

    fprintf(exefile, "LOAD #0; CODELEN : %d \n", ++CODELEN);
    CODELEN++;
    fprintf(exefile, "JUMP %-6d ;CODELEN : %d \n", CODELEN + 2, CODELEN);

    fprintf(exefile, "LOAD #1; CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ; CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    break;

  case OP_INF_EG:
    codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ; CODELEN : %d codeOP < OP_INF_EG\n", RAM_OS_ADR_REG,
            ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "JUMG %d ;CODELEN : %d \n", CODELEN + 3, CODELEN);
    CODELEN++;
    fprintf(exefile, "LOAD #1;CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "JUMP %-6d ;CODELEN : %d \n", CODELEN + 2, CODELEN);
    CODELEN++;
    fprintf(exefile, "LOAD #0;CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    break;

  case OP_SUP_EG:
    codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ;CODELEN : %d codeOP OP_SUP_EG > \n", RAM_OS_ADR_REG,
            ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "JUML %d ;CODELEN : %d \n", CODELEN + 3, CODELEN);
    CODELEN++;
    fprintf(exefile, "LOAD #1;CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "JUMP %-6d ;CODELEN : %d \n", CODELEN + 2, CODELEN);
    CODELEN++;
    fprintf(exefile, "LOAD #0;CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d\n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    break;

  case OP_DIFF:
    codegen(p->op.noeud[1]);
    fprintf(exefile, "INC %-9d ;CODELEN : %d codeOP > \n", RAM_OS_ADR_REG,
            ++CODELEN);
    fprintf(exefile, "STORE @%-6d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    codegen(p->op.noeud[0]);
    fprintf(exefile, "SUB @%-8d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    CODELEN++;
    fprintf(exefile, "JUMZ %d ;CODELEN : %d \n", CODELEN + 3, CODELEN);

    fprintf(exefile, "LOAD #1;CODELEN : %d\n", ++CODELEN);
    CODELEN++;
    fprintf(exefile, "JUMP %-6d ; CODELEN : %d \n", CODELEN + 2, CODELEN);

    fprintf(exefile, "LOAD #0;CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "STORE @%-6d ; CODELEN : %d\n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ;CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    break;
  case '&':
    codegen(p->op.noeud[1]);
    fprintf(exefile, "JUMZ %d ;CODELEN : %d \n",
            CODELEN + 1 + p->op.noeud[0]->codelen + 3, CODELEN);
    CODELEN += 1;
    codegen(p->op.noeud[0]);
    fprintf(exefile, "JUMZ %d ;CODELEN : %d \n", CODELEN + 3, CODELEN);
    CODELEN++;
    fprintf(exefile, "LOAD #1;CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "JUMP %-6d ;CODELEN : %d\n", CODELEN + 2, CODELEN);
    CODELEN++;
    fprintf(exefile, "LOAD #0;CODELEN : %d \n", ++CODELEN);

    break;

  case '|':
    codegen(p->op.noeud[1]);
    fprintf(exefile, "JUMG %d ; CODELEN : %d \n",
            CODELEN + 1 + p->op.noeud[0]->codelen + 3, CODELEN);
    CODELEN += 1;
    codegen(p->op.noeud[0]);
    fprintf(exefile, "JUMG %d ;CODELEN : %d  \n", CODELEN + 3, CODELEN);
    CODELEN++;
    fprintf(exefile, "LOAD #0; CODELEN : %d \n", ++CODELEN);
    fprintf(exefile, "JUMP %-6d ; CODELEN : %d\n", CODELEN + 2, CODELEN);
    CODELEN++;
    fprintf(exefile, "LOAD #1; CODELEN : %d \n", ++CODELEN);

    break;

  default:
    break;
  }

  /*
   * On gère ensuite les opérateurs au cas par cas et on dépile
   */

  switch (p->op.ope) {
  case '+':

    fprintf(exefile, "ADD @%-8d ; CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ; CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    break;
  case '-':

    fprintf(exefile, "SUB @%-8d ; CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ; CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    break;
  case '*':
    fprintf(exefile, "MUL @%-8d ; CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ; CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    break;
  case '/':
    fprintf(exefile, "ADD @%-8d ; CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ; CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    break;
  case '%':
    fprintf(exefile, "MOD @%-8d ; CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);
    fprintf(exefile, "DEC %-9d ; CODELEN : %d \n", RAM_OS_ADR_REG, ++CODELEN);

    break;
  default:
    break;
  }
}
