#include "../include/semantic.h"

#include <stdio.h>
#include <stdlib.h>

char CTXT[32] = "GLOBAL";
int SOMMETpile = 0;

void semantic_STRUCT_TQ(asa * p){
  if (!p) {
    return;
  }
  semantic(p->struct_tq.condition);
  semantic(p->struct_tq.inst);
  p->codelen += p->struct_tq.condition->codelen + p->struct_tq.inst->codelen + 2;
}

void semantic_STRUCT_SI(asa * p){
  if (!p) {
    return;
  }
  semantic(p->struct_si.condition);
  semantic(p->struct_si.inst_si);

  if (p->struct_si.inst_si_non){
    semantic(p->struct_si.inst_si_non);
    p->codelen += p->struct_si.inst_si_non->codelen;
  }
  p->codelen += p->struct_si.condition->codelen + p->struct_si.inst_si->codelen  +2;
}

void semantic_DEC_FON(asa * p){
  if (!p) {
    return;
  }
  printf("hhhhh %s",p->dec_fon.ID->id.nom) ;
  strcpy(CTXT ,p->dec_fon.ID->id.nom ) ; 
  ts_ajouter_contexte(TABLE_SYMBOLES, CTXT) ;
  semantic(p->dec_fon.ID);
  semantic(p->dec_fon.PARAM);
  semantic(p->dec_fon.DECS);
  semantic(p->dec_fon.LIST_INST);

  p->codelen += p->dec_fon.ID->codelen + p->dec_fon.PARAM->codelen + p->dec_fon.DECS->codelen + p->dec_fon.LIST_INST->codelen;

}

void semantic_PARAM(asa * p){
  if (!p) {
    return;
  }
  semantic(p->param.LIST_DECLA);
  p->codelen += p->param.LIST_DECLA->codelen;

}

void semanticINST_LIRE(asa *p) {
  if (!p) {
    return;
  }

  // verification de ID 

  p->codelen += 6;
  semantic(p->inst_lire.ID) ;
}

void semanticINST_ECRIRE(asa *p) {
  if (!p) {
    return;
  }

  // verification de ID 

  
  semantic(p->inst_ecrire.EXP) ;
  p->codelen = p->inst_ecrire.EXP->codelen + 1;
}
void semantic_LIST_INST(asa *p) {
  if (!p) {
    return;
  }

  if (p->list_inst.next) {
    semantic(p->list_inst.next);
    p->codelen += p->list_inst.next->codelen;
  }

  semantic(p->list_inst.INST);
  p->codelen += p->list_inst.INST->codelen;
}

void semantic_LIST_DECLA(asa *p) {
  if (!p) {
    return;
  }

  semantic(p->list_decla.DEC);

  if (p->list_decla.next) {
    semantic(p->list_decla.next);
  }
  p->codelen = (p->list_decla.next ? p->list_decla.next->codelen : 0) +
               (p->list_decla.DEC ? p->list_decla.DEC->codelen : 0)+1;
}

void semantic_DECS(asa *p) {
  if (!p) {
    return;
  }

  semantic(p->decs.DEC);

  if (p->decs.next) {
    semantic(p->decs.next);
  }

  p->codelen = (p->decs.DEC ? p->decs.DEC->codelen : 0) +
               (p->decs.next ? p->decs.next->codelen : 0);
}

void semantic_DECLA_VAR(asa *p) {
  if (!p) {
    return;
  }
  char *id = p->decla_var.ID->id.nom;

  if (ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT) != NULL) {
    printf("dans DECLA_VAR tu essayer de decla %s qui est deja declare\n", id);
  }
  ts_ajouter_contexte(TABLE_SYMBOLES, CTXT);

  // on agmunt et mit le place de vaiable dans le pile 
  symbole *y = ts_ajouter_identificateur(TABLE_SYMBOLES, CTXT, id, 'e', 1);
  y->adr = SOMMETpile;
  p->decla_var.ID->memadr =SOMMETpile++;

  if (p->decla_var.inst_mis) {
    semantic(p->decla_var.inst_mis);
  }
  if (p->decla_var.ID) {
    //semantic(p->decla_var.ID); on plus bisond parce on decla 
  }
  p->codelen = (p->decla_var.ID ? p->decla_var.ID->codelen : 0) +
               (p->decla_var.inst_mis ? p->decla_var.inst_mis->codelen : 0)+1;
}
void semantic_MAIN(asa *p) {
  if (!p) {
    return;
  }


  semantic(p->main.DEC);
  semantic(p->main.DEC_FN);
  semantic(p->main.PROG);
  p->codelen = (p->main.DEC ? p->main.DEC->codelen : 0) +(p->main.PROG ? p->main.PROG->codelen : 0)+
               (p->main.DEC_FN ? p->main.DEC_FN->codelen : 0)+4;// 1 STOP 3 pour init 
}

void semantic_AFF(asa *p) {
  if (!p) {
    return;
  }

  char *id = p->affect.id->id.nom;
  symbole* y = ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT) ;
  if (!y ) {
    printf("id de AFF exist pas \n  ");
    return;
  }
  //p->affect.id->memadr = y->adr ;

  semantic(p->affect.id);
  semantic(p->affect.droit);
  p->codelen = (p->affect.id ? p->affect.id->codelen : 0) +
               (p->affect.droit ? p->affect.droit->codelen : 0) + 4;
}

void semantic_INST(asa *p) {
  if (!p) {
    return;
  }

  semantic(p->inst.INST);
  p->codelen = p->inst.INST->codelen;
}

void semantic_PROG(asa *p) {
  if (!p) {
    return;
  }

  strcpy(CTXT, "prog");
  SOMMETpile = 0 ;
  ts_ajouter_contexte(TABLE_SYMBOLES, CTXT);
  semantic(p->prog.DECLA);
  semantic(p->prog.INST);
  p->codelen = p->prog.DECLA->codelen + p->prog.INST->codelen;
}

void semantic_DECLA_TAB(asa *p) {
  if (!p) {
    return;
  }
  char *id = p->decla_tab.id->id.nom;

  semantic(p->decla_tab.id);
  semantic(p->decla_tab.taille);
  p->codelen = p->decla_tab.id->codelen + p->decla_tab.taille->codelen;
  ts_ajouter_identificateur(TABLE_SYMBOLES, CTXT, id, 't', 1);
}

void semantic_DECLA_POIN(asa *p) {
  if (!p) {
    return;
  }

  char *id = p->decla_poin.id->id.nom;
  semantic(p->decla_poin.id);
  p->codelen = 2;
  ts_ajouter_identificateur(TABLE_SYMBOLES, CTXT, id, 'p', 1);
}

void semantic_ID(asa *p) {

  //char *id = p->id.nom;
  //if (ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT))
    if (p) {
      p->codelen = 4;
    }
    char *id = p->id.nom;
  symbole* y = ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT) ;
  if (!y ) {
    printf("id de AFF exist pas \n  ");
    return;
  }
  p->memadr = y->adr ;
}

void semantic_NB(asa *p) {
  if (p) {
    p->codelen = 1;
  }
}

void semantic_OP(asa *p) {
  if (!p) {
    return;
  }

  switch (p->op.ope) {
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
    semantic(p->op.noeud[0]);
    semantic(p->op.noeud[1]);
    p->codelen = (p->op.noeud[0] ? p->op.noeud[0]->codelen : 0) +
                 (p->op.noeud[1] ? p->op.noeud[1]->codelen : 0) + 4;
  
    break;
  case '<':
  case '>':
  case '=':
  case OP_INF_EG:
  case OP_SUP_EG:
  case OP_DIFF :
    semantic(p->op.noeud[0]);
    semantic(p->op.noeud[1]);
    p->codelen = (p->op.noeud[0] ? p->op.noeud[0]->codelen : 0) +
                 (p->op.noeud[1] ? p->op.noeud[1]->codelen : 0) + 4;
  
    break;
  case '!' :
    
    semantic(p->op.noeud[0]);
    p->codelen = (p->op.noeud[0] ? p->op.noeud[0]->codelen : 0) +
                 (p->op.noeud[1] ? p->op.noeud[1]->codelen : 0) + 7;
  
    break;
  



  }
}



void semantic(asa *p) {
  if (!p) {
    return;
  }

  switch (p->type) {

  case typePROG:
    semantic_PROG(p);
    break;
  case typeMAIN:
    semantic_MAIN(p);
    break;
  case typeDECS:
    semantic_DECS(p);
    break;
  case typeLIST_DECLA:
    semantic_LIST_DECLA(p);
    break;
  case typeINST:
    semantic_INST(p);
    break;
  case typeLIST_INST:
    semantic_LIST_INST(p);
    break;
  
  case typeAFF:
    semantic_AFF(p);
    break;
  
  case typeDECLA_TAB:
    semantic_DECLA_TAB(p);
    break;
  case typeDECLA_POIN:
    semantic_DECLA_POIN(p);
    break;
  case typeDECLA_VAR:
    semantic_DECLA_VAR(p);
    break;
  case typeID:
    semantic_ID(p);
    break;
  case typeNB:
    semantic_NB(p);
    break;
  case typeOP:
    semantic_OP(p);
    break;
  case typeINST_LIRE:
    semanticINST_LIRE(p);
    break;
  case typeINST_ECRIRE:
    semanticINST_ECRIRE(p);
    break;


  case typeSTRUCT_TQ:
    semantic_STRUCT_TQ(p);
    break;
  case typeSTRUCT_SI:
    semantic_STRUCT_SI(p);
    break;
  case typeDEC_FON:
    semantic_DEC_FON(p);
  
    break;


  case typePARAM:
    semantic_PARAM(p);
    break;
  default:
    break;
  }
}
