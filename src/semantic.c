#include "../include/semantic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

char CTXT[32] = "GLOBAL";
int VLOCAL = 0; 
int VGLOBAL = 5 ;


void  semantic_APPFONC(asa *p) {
    if (!p) {
    return;
  }
  // on cherche si le fonction deja decalrer 
  char *id = p->appfonc.ID->id.nom;
  symbole* y = ts_rechercher_identificateur(TABLE_SYMBOLES, id, "GLOBAL") ;
  if (!y){ 
    printf("fonction  %s\n",id ) ;
    error_semantic("fonction appler ne pas declarer \n ") ;
    return ;
  }
 

  //on donne la fonction l'adr dans le pile 

  //y->adr = VLOCAL ++ ;

//sementique suivant 
p->appfonc.ID->id.ctxt = "GLOBAL" ;
 semantic(p->appfonc.ID);
  //semantic(p->appfonc.PARAM) ;
// 

  p->codelen = (p->appfonc.ID? p->appfonc.ID->codelen : 0)+
  (p->appfonc.PARAM? p->appfonc.PARAM->codelen : 0)+3;


}



void semantic_RENVOYER(asa *p) {
  if (!p) {
    return;
  }

  semantic(p->renvoyer.INST);

  p->codelen = (p->renvoyer.INST ? p->renvoyer.INST->codelen : 0);
}

void semantic_STRUCT_TQ(asa *p) {
  if (!p) {
    return;
  }
  semantic(p->struct_tq.condition);
  semantic(p->struct_tq.inst);
  p->codelen = (p->struct_tq.condition ? p->struct_tq.condition->codelen : 0) +
               (p->struct_tq.inst ? p->struct_tq.inst->codelen : 0) + 2;
}

void semantic_STRUCT_SI(asa *p) {
  if (!p) {
    return;
  }
  semantic(p->struct_si.condition);
  semantic(p->struct_si.inst_si);
  semantic(p->struct_si.inst_si_non);

  p->codelen +=
      (p->struct_si.condition ? p->struct_si.condition->codelen : 0) +
      (p->struct_si.inst_si ? p->struct_si.inst_si->codelen : 0) +
      (p->struct_si.inst_si_non ? p->struct_si.inst_si_non->codelen : 0) + 2;
}

void semantic_DEC_FON(asa *p) {
  if (!p) {
    return;
  }
  char * id = p->dec_fon.ID->id.nom ;
  symbole* y = ts_ajouter_identificateur(TABLE_SYMBOLES, CTXT, id, 'f',
                            1);
  y->adr = VGLOBAL++ ;
  strcpy(CTXT, p->dec_fon.ID->id.nom);
  ts_ajouter_contexte(TABLE_SYMBOLES, CTXT);
  p->dec_fon.ID->id.ctxt = "GLOBAL" ;
  p->dec_fon.ID->id.type = "F" ;
  p->dec_fon.ID->memadr =y->adr ;


  //semantic(p->dec_fon.ID);
  semantic(p->dec_fon.PARAM);
  semantic(p->dec_fon.DECS);
  semantic(p->dec_fon.LIST_INST);

  p->codelen += (p->dec_fon.ID ? p->dec_fon.ID->codelen : 0) +
               (p->dec_fon.PARAM ? p->dec_fon.PARAM->codelen : 0) +
               (p->dec_fon.DECS ? p->dec_fon.DECS->codelen : 0) +
               (p->dec_fon.LIST_INST ? p->dec_fon.LIST_INST->codelen : 0) +6

      ;
}

void semantic_PARAM(asa *p) {
  if (!p) {
    return;
  }
  semantic(p->param.LIST_DECLA);
  p->codelen +=(p->param.LIST_DECLA ? p->param.LIST_DECLA->codelen : 0) ;
}

void semanticINST_LIRE(asa *p) {
  if (!p) {
    return;
  }

  // verification de ID
  p->codelen += 6;
  semantic(p->inst_lire.ID);
}

void semanticINST_ECRIRE(asa *p) {
  if (!p) {
    return;
  }

  // verification de ID

  semantic(p->inst_ecrire.EXP);
  p->codelen = (p->inst_ecrire.EXP ? p->inst_ecrire.EXP->codelen :0 ) + 1;
}
void semantic_LIST_INST(asa *p) {
  if (!p) {
    return;
  }

  semantic(p->list_inst.next);
  semantic(p->list_inst.INST);

  p->codelen = (p->list_inst.INST ? p->list_inst.INST->codelen : 0) +
               (p->list_inst.next ? p->list_inst.next->codelen : 0);
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
               (p->list_decla.DEC ? p->list_decla.DEC->codelen : 0) + 1;
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

    // on cherche si l'identifiant est déjà déclaré ou non
    char *id = p->decla_var.ID->id.nom;
    if (ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT) != NULL) {
        printf("Tu essaies de déclarer %s qui est déjà déclaré dans DECLA_VAR\n", id);
        error_semantic("DECLA_VAR");
    }

    ts_ajouter_contexte(TABLE_SYMBOLES, CTXT);

    // on incrémente et attribue l'emplacement de la variable dans la pile
    symbole *y = ts_ajouter_identificateur(TABLE_SYMBOLES, CTXT, id, TYPE_ENTIER, 1);
    if (strcmp(CTXT, "GLOBAL") == 0) { 
      y->adr = VGLOBAL;
        p->decla_var.ID->memadr = VGLOBAL++;
        // mettre les informations dans la feuille de l'identifiant
      p->decla_var.ID->id.ctxt = "GLOBAL";
      p->decla_var.ID->id.type = "e";
        
    } else {
      y->adr = VLOCAL;
        p->decla_var.ID->memadr = VLOCAL++;
        // mettre les informations dans la feuille de l'identifiant
      
      p->decla_var.ID->id.ctxt = "locale";
      p->decla_var.ID->id.type = "e";
        
    }

    

    if (p->decla_var.inst_mis) {
        semantic(p->decla_var.inst_mis);
    }

    if (p->decla_var.ID) {
        // semantic(p->decla_var.ID); pas nécessaire car c'est une déclaration
    }

    p->codelen = (p->decla_var.ID ? p->decla_var.ID->codelen : 0) +
                  (p->decla_var.inst_mis ? p->decla_var.inst_mis->codelen : 0) + 1;
}
void semantic_MAIN(asa *p) {
  if (!p) {
    return;
  }

  semantic(p->main.DEC);
  semantic(p->main.DEC_FN);

  semantic(p->main.PROG);
  p->codelen = (p->main.DEC ? p->main.DEC->codelen : 0) +
               (p->main.PROG ? p->main.PROG->codelen : 0) +
               (p->main.DEC_FN ? p->main.DEC_FN->codelen : 0) +
               4; // 1 STOP et 3 pour init
}

void semantic_AFF(asa *p) {
  if (!p) {
    return;
  }

  // on cherche si le id exist dans local ou pas;  sinon on recherche dans global
  // sinon on retuen error

  char *id = p->affect.id->id.nom;
  symbole *y = ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT);
  if (!y) {
    y = ts_rechercher_identificateur(TABLE_SYMBOLES, id, "GLOBAL");
    p->affect.id->id.ctxt = "GLOBAL";
    if (!y) {

      printf("id de AFF n'exist pas \n  ");
      error_semantic(id);
      return;
    }
  }

  // p->affect.id->memadr = y->adr ;
  p->decla_var.ID->id.ctxt = "locale";
  //strcpy(p->decla_var.ID->id.type, y->type) ;

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
  if (!p) {
    return;
  }

  // char *id = p->id.nom;
  // if (ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT))
symbole * y = ts_rechercher_identificateur(TABLE_SYMBOLES,p->id.nom , "GLOBAL") ;
 if ( y ){
  p->id.ctxt ="GLOBAL" ;
  //strcpy(p->id.ctxt ,"GLOBAL") ;
  p->codelen = 1; 
  p->memadr = y->adr ;
    

 }else {
  symbole * y = ts_rechercher_identificateur(TABLE_SYMBOLES,p->id.nom ,CTXT) ;
  p->id.ctxt ="locale" ;
  
  //strcpy(p->id.ctxt ,"locale") ;
  p->codelen = 4;
  p->memadr = y->adr ;
 }


  
  // char *id = p->id.nom;

  /*
    symbole *y = ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT);
    if (!y) {
      y = ts_rechercher_identificateur(TABLE_SYMBOLES, id, "GLOBAL");
      if (!y) {

       printf("id  exist pas \n  ");
        return;
      }
    }

    p->memadr = y->adr;

    */
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
  case OP_DIFF:
    semantic(p->op.noeud[0]);
    semantic(p->op.noeud[1]);
    p->codelen = (p->op.noeud[0] ? p->op.noeud[0]->codelen : 0) +
                 (p->op.noeud[1] ? p->op.noeud[1]->codelen : 0) + 9;

    break;
  case '!':

    semantic(p->op.noeud[0]);
    p->codelen = (p->op.noeud[0] ? p->op.noeud[0]->codelen : 0) +
                 (p->op.noeud[1] ? p->op.noeud[1]->codelen : 0) + 7;

    break;
  case '&':
  case '|':

    semantic(p->op.noeud[0]);
    semantic(p->op.noeud[1]);
    p->codelen = (p->op.noeud[0] ? p->op.noeud[0]->codelen : 0) +
                 (p->op.noeud[1] ? p->op.noeud[1]->codelen : 0) + 5;

    break;
  }
}



void error_semantic(const char *s) {
  fprintf(stderr, TXT_BOLD TXT_RED "[erreur SEM]" TXT_NULL " %s", s);
  exit(1);
}

void semantic(asa *p) {
  if (!p) {
    return;
  }

  switch (p->type) {

  case typeRENVOYER:
    semantic_RENVOYER(p);
    break;

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
  case typeAPPFONC:
    semantic_APPFONC(p);
    break;
  default:
    break;
  }
}
