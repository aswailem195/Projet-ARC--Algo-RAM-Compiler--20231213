#include "../include/semantic.h"
#include <stdio.h>
#include <stdlib.h>

char CTXTgl[32] = "GLOBAL";
char CTXTmain[32] = "proge" ;




void semantic_AFF(asa *p) {
    if (!p) {
        return;
    }

    semantic(p->affect.id);
    semantic(p->affect.droit);
    p->codelen = p->affect.id->codelen + p->affect.droit->codelen;
}

void semantic_INST(asa *p) {
    if (!p) {
        return;
    }

    semantic(p->inst.INST);
    p->codelen = p->inst.INST->codelen;
}

void semantic_LIST_INST(asa *p) {
    if (!p) {
        return;
    }

    if (p->list_inst.next) {
        semantic(p->list_inst.next);
    }

    semantic(p->list_inst.INST);
    p->codelen = p->list_inst.INST->codelen;
}

void semantic_MAIN(asa *p) {
    if (!p) {
        return;
    }

    semantic(p->main.DECLA);
    semantic(p->main.INST);
    p->codelen = p->main.DECLA->codelen+p->main.INST->codelen;
   
}

void semantic_LIST_DECLA(asa *p) {
    if (!p) {
        return;
    }

    semantic(p->list_decla.DEC);

    if (p->list_decla.next) {
        semantic(p->list_decla.next);
    }

    p->codelen = 5;
}

void semantic_DECS(asa *p) {
    if (!p) {
        return;
    }

    semantic(p->decs.DEC);

    if (p->decs.next) {
        semantic(p->decs.next); 
        p->codelen =p->decs.next->codelen ;

    }

    p->codelen += p->decs.DEC->codelen;
;
}

void semantic_DECLA_TAB(asa *p) {
    if (!p) {
        return;
    }
    char* id = p->decla_tab.id->id.nom;

    semantic(p->decla_tab.id);
    semantic(p->decla_tab.taille);
    p->codelen = p->decla_tab.id->codelen+p->decla_tab.taille->codelen;
    ts_ajouter_identificateur(TABLE_SYMBOLES, CTXTmain, id,  't', 1 ) ;
}

void semantic_DECLA_POIN(asa *p) {
    if (!p) {
        return;
    }

    char *id = p->decla_poin.id->id.nom;
    semantic(p->decla_poin.id);
    p->codelen = 2;
    ts_ajouter_identificateur(TABLE_SYMBOLES, CTXTmain, id,  'p', 1 ) ;
}

void semantic_DECLA_VAR(asa *p) {
    if (!p) {
        return;
    }

    semantic(p->decla_var.DECLA);
    char *id =p->decla_var.DECLA->id.nom ;

    if (p->decla_var.next) {
        semantic(p->decla_var.next);
    }


    // Adjust this line based on your actual requirements
    p->codelen += (p->decla_var.DECLA ? p->decla_var.DECLA->codelen : 0) +
                  (p->decla_var.next ? p->decla_var.next->codelen : 0) + 2;



    // ajouter le ID in ts 
  
    /*  if( (ts_rechercher_identificateur(TABLE_SYMBOLES, id, CTXTgl))) {
      printf("error id deja ajouter ");
      return ;

    }
    TABLE_SYMBOLES->liste_symbole= malloc(sizeof(symbole)) ;*/

     ts_ajouter_contexte(TABLE_SYMBOLES, CTXTmain);
     ts_ajouter_identificateur(TABLE_SYMBOLES, CTXTmain, id,  'e', 1 ) ;
}

void semantic_ID(asa *p) {
    if (p) {
        p->codelen = 1;
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
    }
}

void semantic(asa *p) {
    if (!p) {
        return;
    }

    switch (p->type) {
    case typeAFF:
        semantic_AFF(p);
        break;
    case typeINST:
        semantic_INST(p);
        break;
    case typeLIST_INST:
        semantic_LIST_INST(p);
        break;
    case typeMAIN:
        semantic_MAIN(p);
        break;
    case typeLIST_DECLA:
        semantic_LIST_DECLA(p);
        break;
    case typeDECS:
        semantic_DECS(p);
        break;
    case typeDECLA_TAB:
        semantic_DECLA_TAB(p);
        break;
    case typeDECLA_POIN:
        semantic_DECLA_POIN(p);
        break;
    case typeNB:
        semantic_NB(p);
        break;
    case typeOP:
        semantic_OP(p);
        break;
    case typeID:
        semantic_ID(p);
        break;
    case typeDECLA_VAR:
        semantic_DECLA_VAR(p);
        break;
    default:
        break;
    }
}
