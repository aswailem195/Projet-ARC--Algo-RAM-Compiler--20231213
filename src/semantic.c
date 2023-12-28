#include "../include/semantic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

char CTXT[32] = "GLOBAL";
int VLOCAL = 0; // Pour numéroter la variable globale.
int VGLOBAL = 10; // Pour numéroter l'adresse de la variable globale.

int ADR_PTR = 0; /* On donne le premier pointeur qui pointera vers le tas à l'adresse 0.
Cela signifie qu'il prendra la première adresse dans le tas, et ensuite on 
donnera la suivante en ajoutant la taille. */


/*utile pour apple de fonction */
char NOMFONAPPLE[32] = "";
int NB_VAR = 0;













/*________________________________paramitre_fonction ______________________________________*/
void semantic_PON(asa *p) {
  if (!p) {
    return;
  }

  p->ent.id->id.type = 'p';
  
  symbole *y =
      ts_rechercher_identificateur(TABLE_SYMBOLES, p->ent.id->id.nom, "GLOBAL");
  if (y) {
    p->ent.id->id.ctxt = "GLOBAL";

    p->codelen = 1;
    p->memadr = y->adr;

  } else {
    y = ts_rechercher_identificateur(TABLE_SYMBOLES, p->ent.id->id.nom, CTXT);
    if (y) {
      p->ent.id->id.ctxt = "locale";

    } else {
      printf("%s ", p->ent.id->id.nom);
      error_semantic("apple de variable non  declare");
    }
  }

  /*veriver le paramit on cher dans le sympol e de contexte*/

  contexte *c = ts_rechercher_contexte(TABLE_SYMBOLES, NOMFONAPPLE);
  if (c->liste_symbole == NULL) {
    error_semantic("parmaitre ");
  }
  int type = c->liste_symbole[0].type;
  printf("type : %d ", type);

  if (type != TYPE_PTR) {
    printf("type parmaitre de fonction %s typ1 :%c type2 %c :", NOMFONAPPLE,
           type, TYPE_PTR);
    error_semantic("parmaitre ");
  }

  NB_VAR++;
}
void semantic_INT(asa *p) {
  if (!p) {
    return;
  }

  p->ent.id->id.type = TYPE_ENTIER;
  symbole *y =ts_rechercher_identificateur(TABLE_SYMBOLES, p->ent.id->id.nom, "GLOBAL");
  if (y) {
    p->ent.id->id.ctxt = "GLOBAL";
    p->codelen = 1;
    p->memadr = y->adr;
    p->ent.id->id.adr = y->adr;

  } else {
    y = ts_rechercher_identificateur(TABLE_SYMBOLES, p->ent.id->id.nom, CTXT);
    if (y) {
      p->ent.id->id.ctxt = "locale";
      p->ent.id->id.adr = y->adr;

    } else {
      printf("param%s ", p->ent.id->id.nom);
      error_semantic("apple de variable non  declare");
    }
  }

  /*veriver le paramit on cher dans le sympol e de contexte*/

  contexte *c = ts_rechercher_contexte(TABLE_SYMBOLES, NOMFONAPPLE);
  if (c->liste_symbole == NULL) {
    error_semantic("parmaitre ");
  }

  /*copier le adre de applant et de lui meme*/
  p->ent.id->id.adr_app = c->liste_symbole[0].adr;
  int type = c->liste_symbole[0].type;
  printf("type : %d ", type);
  if (type != TYPE_ENTIER) {
    printf("type parmaitre de fonction %s typ1 :%c type2 %c :", NOMFONAPPLE,
           type, TYPE_ENTIER);
    error_semantic("parmaitre ");
  }
  NB_VAR++;
  p->codelen = (p->ent.id ? p->ent.id->codelen : 0) + 7;
}

void semantic_LIST_PARAM(asa *p, char *nom_F) {
  if (!p) {
    return;
  }
  semantic(p->list_var.var);
  semantic_LIST_PARAM(p->list_var.next, nom_F);

  p->codelen = (p->list_var.var ? p->list_var.var->codelen : 0) +
               (p->list_var.next ? p->list_decla.next->codelen : 0);
}

/*___________________________fonction_______________________________*/

void semantic_APPFONC(asa *p) {
  if (!p) {
    return;
  }
  /* on cherche si le fonction deja decalrer */
  char *id = p->appfonc.ID->id.nom;
  strcpy(NOMFONAPPLE, id);
  contexte u ;


  symbole *y = ts_rechercher_identificateur(TABLE_SYMBOLES, id, "GLOBAL");
  if (!y) {
    printf("fonction  %s\n", id);
    error_semantic("fonction appler ne pas declarer \n ");
    return;
  }

 

  // sementique suivant
  p->appfonc.ID->id.ctxt = "GLOBAL";
  semantic(p->appfonc.ID);
  semantic_LIST_PARAM(p->appfonc.LIST_PARAM, id);

  p->codelen = (p->appfonc.ID ? p->appfonc.ID->codelen : 0) +
               (p->appfonc.LIST_PARAM ? p->appfonc.LIST_PARAM->codelen : 0) + 3;

  // semantic(p->appfonc.PARAM->param.)
}
void semantic_PARAM(asa *p) {
  if (!p) {
    return;
  }
  semantic(p->param.LIST_VAR);
  p->codelen += (p->param.LIST_VAR ? p->param.LIST_VAR->codelen : 0);
}
void semantic_LIS_DEC_FON(asa *p) {
  if (!p) {
    return;
  }
  semantic(p->lis_dec_fon.dec_fon);

  strcpy(CTXT, "GLOBAL");
  semantic(p->lis_dec_fon.next);
  p->codelen += (p->lis_dec_fon.dec_fon ? p->lis_dec_fon.dec_fon->codelen : 0) +
                (p->lis_dec_fon.next ? p->lis_dec_fon.next->codelen : 0);
}

void semantic_DEC_FON(asa *p) {
  if (!p) {
    return;
  }
  char *id = p->dec_fon.ID->id.nom;

  /* */ 
  if (ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT) != NULL) {
    printf("Tu essaies de déclarer %s qui est déjà déclaré \n",
           id);
    error_semantic("semantic_DEC_FON");
  }
  symbole *y = ts_ajouter_identificateur(TABLE_SYMBOLES, CTXT, id, 'f', 1);
  y->adr = VGLOBAL++;

  strcpy(CTXT, p->dec_fon.ID->id.nom);
  ts_ajouter_contexte(TABLE_SYMBOLES, CTXT);
  p->dec_fon.ID->id.ctxt = "GLOBAL";
  p->dec_fon.ID->id.type = TYPE_FCT;
  p->dec_fon.ID->memadr = y->adr;

  // semantic(p->dec_fon.ID);
  semantic(p->dec_fon.PARAM);
  semantic(p->dec_fon.DECS);
  semantic(p->dec_fon.LIST_INST);

  p->codelen += (p->dec_fon.ID ? p->dec_fon.ID->codelen : 0) +
                (p->dec_fon.PARAM ? p->dec_fon.PARAM->codelen : 0) +
                (p->dec_fon.DECS ? p->dec_fon.DECS->codelen : 0) +
                (p->dec_fon.LIST_INST ? p->dec_fon.LIST_INST->codelen : 0) + 6

      ;
}



/*_________________________________inistraction_______________________*/
void semantic_AFF(asa *p) {
  if (!p) {
    return;
  }

  /* on cherche si le id exist dans local ou pas;  sinon on recherche dans
  * global sinon on retuen error
   
   
   */

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

  
  p->decla_var.ID->id.ctxt = "locale";
  

  semantic(p->affect.id);
  semantic(p->affect.droit);
  p->codelen = (p->affect.id ? p->affect.id->codelen : 0) +
               (p->affect.droit ? p->affect.droit->codelen : 0) + 5;
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

  p->codelen += (p->prog.DECLA ? p->prog.DECLA->codelen :0 ) + (p->prog.INST ? p->prog.INST->codelen:0);
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




void semanticINST_LIRE(asa *p) {
  if (!p) {
    return;
  }

  p->codelen += 6;
  semantic(p->inst_lire.ID);
}

void semanticINST_ECRIRE(asa *p) {
  if (!p) {
    return;
  }

 

  semantic(p->inst_ecrire.EXP);
  p->codelen = (p->inst_ecrire.EXP ? p->inst_ecrire.EXP->codelen : 0) + 1;
}
void semantic_LIST_INST(asa *p) {
  if (!p) {
    return;
  }
semantic(p->list_inst.INST);
  semantic(p->list_inst.next);
  

  p->codelen = (p->list_inst.INST ? p->list_inst.INST->codelen : 0) +
               (p->list_inst.next ? p->list_inst.next->codelen : 0);
}
/*________________________________________INDEX______________________________________

*/
void semantic_INDICX_RECU(asa *p){
    if (!p) {
    return;
  }
  char *id = p->indicx_recu.id->id.nom ;
  symbole * y =ts_rechercher_identificateur(TABLE_SYMBOLES, id, "GLOBAL");
  if (y) {
    p->indicx_recu.id->id.ctxt= "GLOBAL";

    // on le donner la codelen et la adr
    p->codelen = 5;
    p->indicx_recu.id->memadr = y->adr;
    

  } else {
    y = ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT);
    if (y && (y->type == TYPE_PTR)) {
       p->indicx_recu.id->id.ctxt= "locale";

      // on le donner la codelen et la adr
      p->codelen =5;
      p->indicx_recu.id->memadr = y->adr;
      
      
  

    } else {
      printf("esseyer de alloer anans declare ou type deffirnt  \n");
      error_semantic(id);
    }
  }
  semantic(p->indicx_recu.exp) ;
  semantic(p->indicx_recu.id) ;
  semantic(p->indicx_recu.index) ;
  p->codelen += (p->indicx_recu.exp ? p->indicx_recu.exp->codelen : 0) +
               (p->indicx_recu.id? p->indicx_recu.id->codelen: 0)+
               (p->indicx_recu.index ? p->indicx_recu.index->codelen : 0);



}
void  semantic_INDICX_SORT(asa *p){
    if (!p) {
    return;
  }
    feuilleId  id = p->indicx_recu.id->id;
  symbole * y =ts_rechercher_identificateur(TABLE_SYMBOLES, id.nom, "GLOBAL");
  if (y) {
    id.ctxt= "GLOBAL";

    // on le donner la codelen et la adr
    p->codelen = 7;
    p->indicx_sort.id->memadr = y->adr;
    

  } else {
    y = ts_rechercher_identificateur(TABLE_SYMBOLES, id.nom, CTXT);
    if (y && (y->type == TYPE_PTR)) {
       p->indicx_sort.id->id.ctxt= "locale";

      // on le donner la codelen et la adr
      p->codelen =7;
      p->indicx_sort.id->memadr = y->adr;
      
      
  

    } else {
      printf("esseyer de alloer anans declare ou type deffirnt  \n");
      error_semantic(id.nom);
    }
  }
  semantic(p->indicx_sort.id) ;
  semantic(p->indicx_sort.index) ;
  p->codelen += (p->indicx_sort.id? p->indicx_sort.id->codelen : 0) +
               (p->indicx_sort.index ? p->indicx_sort.index->codelen : 0);
  

}



/*________________________________________declaration______________________________________

*/

void semantic_LIST_DECLA(asa *p) {
  if (!p) {
    return;
  }

  semantic(p->list_decla.DEC);

  if (p->list_decla.next) {
    semantic(p->list_decla.next);
  }
  p->codelen += (p->list_decla.next ? p->list_decla.next->codelen : 0) +
               (p->list_decla.DEC ? p->list_decla.DEC->codelen : 0);
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
void semantic_ALLOCATION(asa *p){
  if (!p) {
    return;
  } 
  char* id = p->allocation.id->id.nom ;
  
  /* On recherche la variable dans la portée globale.
   * Si elle n'est pas trouvée, on cherche dans la portée locale de la fonction.
   */

  symbole *y =
ts_rechercher_identificateur(TABLE_SYMBOLES, id, "GLOBAL");
  if (y) {
    p->id.ctxt = "GLOBAL";

    // on le donner la codelen et la adr
    p->codelen = 4;
    p->allocation.id->memadr = y->adr;
    y->size = p->allocation.taille->nb.val ;
    p->allocation.id->id.adr_PTR =ADR_PTR ;
      ADR_PTR +=  y->size;

  } else {
    y = ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT);
    if (y && (y->type == TYPE_PTR)) {
      p->allocation.id->id.ctxt = "locale";

      // on le donner la codelen et la adr
      p->codelen =4;
      p->allocation.id->memadr = y->adr;
      y->size = p->allocation.taille->nb.val ;
      p->allocation.id->id.adr_PTR =ADR_PTR ;
      ADR_PTR +=  y->size;

    } else {
      printf("esseyer de alloer anans declare ou type deffirnt  \n");
      error_semantic(id);
    }
  }
  semantic(p->allocation.id) ;
  semantic(p->allocation.taille) ;
  p->codelen += (p->allocation.taille? 0 : 0) +
               (p->allocation.id ? p->allocation.id->codelen : 0);


}

void semantic_DECLA_POIN(asa *p) {
  if (!p) {
    return;
  }

  char *id = p->decla_poin.id->id.nom;
  
  p->codelen = 2;
  symbole* y = ts_ajouter_identificateur(TABLE_SYMBOLES, CTXT, id, TYPE_PTR, 1);
  //si il global 
  if (strcmp(CTXT, "GLOBAL") == 0) {
    y->adr = VGLOBAL;
    p->decla_var.ID->memadr = VGLOBAL++;
    // mettre les informations dans la feuille de l'identifiant
    p->decla_var.ID->id.ctxt = "GLOBAL";
    p->decla_var.ID->id.type = TYPE_PTR;

  //si il local 
  } else {
    y->adr = VLOCAL;
    p->decla_var.ID->memadr = VLOCAL++;
    // mettre les informations dans la feuille de l'identifiant

    p->decla_var.ID->id.ctxt = "locale";
    p->decla_var.ID->id.type = TYPE_PTR;
  }

  if (p->decla_var.inst_mis) {
    semantic(p->decla_var.inst_mis);
  }

  p->codelen = 0 ;
}

void semantic_DECLA_VAR(asa *p) {

  /*ici on declar just le variable de type int */
  if (!p) {
    return;
  }

  /* on cherche si l'identifiant est déjà déclaré ou non */
  char *id = p->decla_var.ID->id.nom;
  //ou port global 
  if (ts_rechercher_identificateur(TABLE_SYMBOLES, id, "GLOBAL") != NULL) {
    printf("Tu essaies de déclarer %s qui est déjà déclaré dans port global \n",id);
    error_semantic("DECLA_VAR");
  }

  if (ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXT) != NULL) {
    printf("Tu essaies de déclarer %s qui est déjà déclaré dans DECLA_VAR\n",
           id);
    error_semantic("DECLA_VAR");
  }


  /* on incrémente et attribue l'emplacement de la variable dans la pile*/

  symbole *y =ts_ajouter_identificateur(TABLE_SYMBOLES, CTXT, id, TYPE_ENTIER, 1);

  //si il global 
  if (strcmp(CTXT, "GLOBAL") == 0) {
    y->adr = VGLOBAL;
    p->decla_var.ID->memadr = VGLOBAL++;
    // mettre les informations dans la feuille de l'identifiant
    p->decla_var.ID->id.ctxt = "GLOBAL";
    p->decla_var.ID->id.type = TYPE_ENTIER;

  //si il local 
  } else {
    y->adr = VLOCAL;
    p->decla_var.ID->memadr = VLOCAL++;
    // mettre les informations dans la feuille de l'identifiant

    p->decla_var.ID->id.ctxt = "locale";
    p->decla_var.ID->id.type = TYPE_ENTIER;
  }

  if (p->decla_var.inst_mis) {
    semantic(p->decla_var.inst_mis);
  }

/*
  if (p->decla_var.ID) {
    // semantic(p->decla_var.ID); pas nécessaire car c'est une déclaration
  } */
  semantic(p->decla_var.ID);
  semantic(p->decla_var.inst_mis);

  p->codelen +=
      (p->decla_var.ID ? p->decla_var.ID->codelen : 0) +
      (p->decla_var.inst_mis ? p->decla_var.inst_mis->codelen + 5 : 0) ;
}
/*________________________________________main____________________________________*/


void semantic_MAIN(asa *p) {
  if (!p) {
    return;
  }

  semantic(p->main.DEC);

  semantic(p->main.L_DEC_FN);
  semantic(p->main.PROG);
  p->main.nb_valiable_local = VLOCAL - 1;

  p->codelen = (p->main.DEC ? p->main.DEC->codelen : 0) +
               (p->main.PROG ? p->main.PROG->codelen : 0) +
               (p->main.L_DEC_FN ? p->main.L_DEC_FN->codelen : 0) +
               7; // 1 STOP et 4 pour init
}



/*______________________________________________ID_________________________________________________*/

void semantic_ID(asa *p) {
  if (!p) {
    return;
  }

  /* On recherche la variable dans la portée globale.
   * Si elle n'est pas trouvée, on cherche dans la portée locale de la fonction.
   */

  symbole *y =
      ts_rechercher_identificateur(TABLE_SYMBOLES, p->id.nom, "GLOBAL");
  if (y) {
    p->id.ctxt = "GLOBAL";

    // on le donner la codelen et la adr
    p->codelen = 1;
    p->memadr = y->adr;

  } else {
    y = ts_rechercher_identificateur(TABLE_SYMBOLES, p->id.nom, CTXT);
    if (y) {
      p->id.ctxt = "locale";

      // on le donner la codelen et la adr
      p->codelen = 4;
      p->memadr = y->adr;
    } else {
      printf("apple de variable anans declare\n");
      error_semantic(p->id.nom);
    }
  }
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

  case M_UN:

    semantic(p->op.noeud[0]);
    semantic(p->op.noeud[1]);
    p->codelen = (p->op.noeud[0] ? p->op.noeud[0]->codelen : 0) +
                 (p->op.noeud[1] ? p->op.noeud[1]->codelen : 0) + 3;

    break;
  }
}

int error_semantic(const char *s) {
  fprintf(stderr, TXT_BOLD TXT_RED "[erreur SEM]" TXT_NULL " %s", s);
  exit(1);
  return -1;
}

void semantic(asa *p) {
  if (!p) {
    return;
  }

  switch (p->type) {


case typeINDICX_RECU:
    semantic_INDICX_RECU(p);
    break;
  case typeINDICX_SORT:
    semantic_INDICX_SORT(p);
    break;

  case typeALLOCATION:
    semantic_ALLOCATION(p);
    break;

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
  case typeLIS_DEC_FON:
    semantic_LIS_DEC_FON(p);
    break;

  case typeINT:
    semantic_INT(p);
    break;
  case typePON:
    semantic_PON(p);
    break;

  default:
    break;
  }
}
