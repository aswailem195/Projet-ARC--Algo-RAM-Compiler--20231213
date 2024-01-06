#include "../include/asa.h"

#include <stdio.h>
#include <stdlib.h>

static const char str_type[][16] = {"NB", "OP"};
static const char line[36] = "-----------------------------------";

static char buffer[32];
static char TABULATION[256] = "";
static int indent = 0;

asa *creer_noeudRENVOYER(asa *p1) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeRENVOYER;
  p->renvoyer.INST = p1;
  return p;
}

asa *creer_feuilleNB(int val) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeNB;
  p->nb.val = val;
  return p;
}
asa *creer_feuilleID(char *nom) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL) {
    error_asa("echec allocation mémoire");
  }

  p->type = typeID;
  strcpy(p->id.nom, nom);

  return p;
}

asa *creer_noeudOP(int ope, asa *p1, asa *p2) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeOP;
  p->op.ope = ope;
  p->op.noeud[0] = p1;
  p->op.noeud[1] = p2;

  return p;
}
asa *creer_noeudINST(asa *p1) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeINST;
  p->inst.INST = p1;
  return p;
}
asa *creer_noeudLIST_INST(asa *p1, asa *p2) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeLIST_INST;
  p->list_inst.INST = p1;
  p->list_inst.next = p2;

  return p;
}

asa *creer_noeudDECLA_VAR(char *id, asa *p1) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeDECLA_VAR;
  p->decla_var.ID = creer_feuilleID(id);
  p->decla_var.inst_mis = p1;

  return p;
}

asa *creer_noeudAffic(char *id, asa *p1) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  if (p1 == NULL)
    error_asa("Erreur AFFICHER : ne peut pas afficher NULL");

  p->type = typeAFF;
  p->affect.droit = p1;
  p->affect.id = creer_feuilleID(id);

  return p;
}
asa *creer_noeudPROG(asa *p1, asa *p2) {

  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typePROG;
  p->prog.INST = p2;
  p->prog.DECLA = p1;

  return p;
}

asa *creer_noeudDECS(asa *p1, asa *p2) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeDECS;
  p->decs.DEC = p1;
  p->decs.next = p2;

  return p;
}
asa *creer_noeudLIST_DECLA(asa *p1, asa *p2) {

  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeLIST_DECLA;
  p->list_decla.DEC = p1;
  p->list_decla.next = p2;

  return p;
}
asa *creer_noeudDECLA_TAB(char *id, int value) {

  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeDECLA_TAB;
  p->decla_tab.id = creer_feuilleID(id);
  p->decla_tab.taille = creer_feuilleNB(value);

  return p;
}

asa *creer_noeudDECLA_POIN(char *id) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeDECLA_POIN;
  p->decla_poin.id = creer_feuilleID(id);

  return p;
}

asa *creer_noeudINST_ECRIRE(asa *p1) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeINST_ECRIRE;
  p->inst_ecrire.EXP = p1;

  return p;
}
asa *creer_noeudINST_LIRE(char *id) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeINST_LIRE;
  p->inst_lire.ID = creer_feuilleID(id);

  return p;
}

asa *creer_noeudSTRUCT_TQ(asa *p1, asa *p2) {

  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeSTRUCT_TQ;
  p->struct_tq.condition = p1;
  p->struct_tq.inst = p2;

  return p;
}
asa *creer_noeudSTRUCT_SI(asa *p1, asa *p2, asa *p3) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeSTRUCT_SI;
  p->struct_si.condition = p1;
  p->struct_si.inst_si = p2;
  p->struct_si.inst_si_non = p3;

  return p;
}

asa *creer_noeudMAIN(asa *p1, asa *p2, asa *p3) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeMAIN;
  p->main.DEC = p1;
  p->main.L_DEC_FN = p2;
  p->main.PROG = p3;

  return p;
}

asa *creer_noeudDEC_FON(char *id, asa *p2, asa *p3, asa *p4) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeDEC_FON;
  p->dec_fon.ID = creer_feuilleID(id);
  p->dec_fon.PARAM = p2;
  p->dec_fon.DECS = p3;
  p->dec_fon.LIST_INST = p4;

  return p;
}
asa *creer_noeudPARAM(asa *p1) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typePARAM;

  p->param.LIST_VAR = p1;

  return p;
}

asa *creer_noeudAPPFONC(char *id, asa *p2) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeAPPFONC;

  p->appfonc.ID = creer_feuilleID(id);
  p->appfonc.LIST_PARAM = p2;

  return p;
}
asa *creer_noeudLIS_DEC_FON(asa *p1, asa *p2) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeLIS_DEC_FON;

  p->lis_dec_fon.dec_fon = p1;
  p->lis_dec_fon.next = p2;

  return p;
}

asa *creer_noeudLIST_VAR(asa *p1, asa *p2) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeL_PARM_APPL;

  p->l_param_appl.var = p1;
  p->l_param_appl.next = p2;

  return p;
}
asa *creer_noeudPARAM_APPL(char *id) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typePARAM_APPL;

  p->param_appl.id = creer_feuilleID(id);
  p->param_appl.id->id.type = TYPE_ENTIER;

  return p;
}
asa *creer_noeudPON(char *id) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typePON;

  p->pon.id = creer_feuilleID(id);
  p->pon.id->id.type = TYPE_PTR;

  return p;
}

asa *creer_noeudALLOCATION(char *id, asa *p2) {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeALLOCATION;
  p->allocation.taille = p2;
  p->allocation.id = creer_feuilleID(id);

  return p;
}

asa*  creer_noeudINDICX_SORT(char* id ,asa* p2 ){
    asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeINDICX_SORT;
  p->indicx_sort.index= p2;
  p->indicx_sort.id = creer_feuilleID(id);

  return p;

}
asa* creer_noeudINDICX_RECU(char* id ,asa* p2,asa* p3 ) {
    asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeINDICX_RECU;
  p->indicx_recu.index = p2;
  p->indicx_recu.exp =p3 ;

  p->indicx_recu.id= creer_feuilleID(id);

  return p;

}

//_________________________________free______________
void free_asa(asa *p) {
  if (!p)
    return;
  switch (p->type) {
  case typeOP:
    free_asa(p->op.noeud[0]);
    free_asa(p->op.noeud[1]);
    break;
  case typeNB:
  default:
    break;
  }
  free(p);
}

static void print_field(char *field_name, char *field_val, char *TABULATION,
                        char *escape_seq) {
  char buffer[128] = "";
  sprintf(buffer, "%s|%s%*s| ", TABULATION, field_name,
          MAX_SIZE_FIELD_NAME - (int)strlen(field_name), "");
  printf("%s%s%s" TXT_NULL "%*s\n", buffer, escape_seq, field_val,
         MAX_SIZE_FIELD_VAL - MAX_SIZE_FIELD_NAME - (int)strlen(field_val),
         "|");
}

void print_asa(asa *p) {
  int i;
  if (!p)
    return;
  for (i = 0; i < indent; i++) {
    TABULATION[i] = '\t';
  }
  TABULATION[i] = '\0';

  printf("%s%s\n", TABULATION, line);

  sprintf(buffer, "%p", p);
  print_field("  noeud", buffer, TABULATION, TXT_BLUE TXT_BOLD);

  sprintf(buffer, "%s", str_type[p->type]);
  print_field("  typeNoeud", buffer, TABULATION, "");

  printf("%s%s\n"
         "%s|%*s|%*s|\n",
         TABULATION, line, TABULATION, MAX_SIZE_FIELD_NAME, "",
         MAX_SIZE_FIELD_VAL - MAX_SIZE_FIELD_NAME, "");

  sprintf(buffer, "%d", p->memadr);
  print_field("adr mem", buffer, TABULATION, "");

  sprintf(buffer, "%d", p->codelen);
  print_field("taille code", buffer, TABULATION, "");

  switch (p->type) {
  case typeOP:
    print_typeOP(p);
    break;
  case typeNB:
    print_typeNB(p);
    break;
  default:
    break;
  }
}

void print_typeOP(asa *p) {
  sprintf(buffer, "'%c'", p->op.ope);
  print_field("operateur", buffer, TABULATION, "");

  sprintf(buffer, "%p", p->op.noeud[0]);
  print_field("ope gauche", buffer, TABULATION, TXT_GREEN);
  sprintf(buffer, "%p", p->op.noeud[1]);
  print_field("ope droite", buffer, TABULATION, TXT_GREEN);

  printf("%s%s\n", TABULATION, line);
  indent++;
  print_asa(p->op.noeud[0]);
  indent--;
  indent++;
  print_asa(p->op.noeud[1]);
  indent--;
}

void print_typeNB(asa *p) {
  sprintf(buffer, "%d", p->nb.val);
  print_field("val", buffer, TABULATION, "");
  printf("%s%s\n", TABULATION, line);
}

void error_asa(const char *s) {
  fprintf(stderr, TXT_BOLD TXT_RED "[erreur ASA]" TXT_NULL " %s", s);
  exit(1);
}

//___________________________PRINT ASA dot _____________________

void print_asa_dot_node(FILE *output, asa *p) {
  if (p == NULL) {
    return;
  }
  fprintf(output, "node%p [label=\"", p);
  switch (p->type) {
  case typeNB:
    fprintf(output, "NB\\n%d \n tailcode:%d adr:%d \\n", p->nb.val, p->codelen,
            p->memadr);
    break;
  case typeID:

    fprintf(output,
            "ID\\n%s\n tailcode:%d  \n adr:%d ctxt :%s\n type : (%d) \n adr_PTR :%d \\n",
            p->id.nom, p->codelen, p->memadr, p->id.ctxt, p->id.type,p->id.adr_PTR);
    break;

  case typeOP:
    fprintf(output, "OP\\n%c \n tailcode:%d adr:%d \\n", p->op.ope, p->codelen,
            p->memadr);
    break;

  case typeAFF:
    fprintf(output, "AFF\n tailcode:%d \n adr:%d \\n", p->codelen, p->memadr);
    break;
  case typeLIST_INST:
    fprintf(output, "LIST_INST\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;
  case typeINST:
    fprintf(output, "INST\n tailcode:%d \n adr:%d \\n", p->codelen, p->memadr);
    break;
  case typeDECLA_VAR:
    fprintf(output, "DECLA_VAR\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;
  case typePROG:
    fprintf(output, "PROG\n tailcode:%d \n adr:%d \\n", p->codelen, p->memadr);
    break;
  case typeDECS:
    fprintf(output, "DECS\n tailcode:%d \n adr:%d \\n", p->codelen, p->memadr);
    break;

  case typeLIST_DECLA:
    fprintf(output, "LIST_DECLA\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;
  case typeDECLA_TAB:
    fprintf(output, "DECLA_TAB\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;
  case typeDECLA_POIN:
    fprintf(output, "DECLA_POIN @\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;

  case typeINST_ECRIRE:
    fprintf(output, "INST_ECRIRE\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;

  case typeINST_LIRE:
    fprintf(output, "INST_LIRE\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;
  case typeSTRUCT_TQ:
    fprintf(output, "STRUCT_TQ\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;
  case typeSTRUCT_SI:
    fprintf(output, "STRUCT_SI\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;
  case typeMAIN:
    fprintf(output, "MAIN\n tailcode:%d \n nb_val_ :%d \\n", p->codelen,
            p->main.nb_valiable_local);
    break;

  case typeDEC_FON:
    fprintf(output, "DEC_FON\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;
  case typePARAM:
    fprintf(output, "PARAM\n tailcode:%d \n adr:%d \\n", p->codelen, p->memadr);
    break;

  case typeRENVOYER:
    fprintf(output, "RENVOYER\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;

  case typeAPPFONC:
    fprintf(output, "APPFONC\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;
  case typePARAM_APPL:
    fprintf(output, "PARAM_APPL\n tailcode:%d \n adr:%d \\n", p->codelen, p->memadr);
    break;
  case typeL_PARM_APPL:
    fprintf(output, "L_PARM_APPL\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;
  case typePON:
    fprintf(output, "PON\n tailcode:%d \n adr:%d \\n", p->codelen, p->memadr);
    break;
  case typeALLOCATION:
    fprintf(output, "ALLOCATIO\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;

  case typeLIS_DEC_FON:
    fprintf(output, "LIS_DEC_FON\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;

  case typeINDICX_RECU:
    fprintf(output, "INDICX_RECU\n tailcode:%d \n ID[nb]<-EXP \\n", p->codelen
            );
    break;
  case typeINDICX_SORT:
    fprintf(output, "INDICX_SORT\n tailcode:%d \n adr:%d \\n", p->codelen,
            p->memadr);
    break;
  //__________________________________________________________________________________
  default:
    fprintf(output, "UNKNOWN");
  }
  fprintf(output, "\", shape=box];\n");
}

void print_asa_dot_edge(FILE *output, asa *parent, asa *child) {

  if (child) {
    fprintf(output, "node%p -> node%p;\n", parent, child);
  }
}

void print_asa_dot_recursive(FILE *output, asa *p) {
  if (p == NULL) {
    return;
  }

  print_asa_dot_node(output, p);

  switch (p->type) {

  case typeOP:
    print_asa_dot_edge(output, p, p->op.noeud[0]);
    print_asa_dot_recursive(output, p->op.noeud[0]);

    print_asa_dot_edge(output, p, p->op.noeud[1]);
    print_asa_dot_recursive(output, p->op.noeud[1]);
    break;

  case typeAFF:
    print_asa_dot_edge(output, p, p->affect.id);
    print_asa_dot_recursive(output, p->affect.id);

    print_asa_dot_edge(output, p, p->affect.droit);

    print_asa_dot_recursive(output, p->affect.droit);
    break;
  case typeINST:
    print_asa_dot_edge(output, p, p->inst.INST);

    print_asa_dot_recursive(output, p->inst.INST);

    break;
  case typeLIST_INST:
    print_asa_dot_edge(output, p, p->list_inst.INST);

    print_asa_dot_recursive(output, p->list_inst.INST);

    print_asa_dot_edge(output, p, p->list_inst.next);
    print_asa_dot_recursive(output, p->list_inst.next);
    break;

  case typeDECLA_VAR:

    print_asa_dot_edge(output, p, p->decla_var.ID);
    print_asa_dot_recursive(output, p->decla_var.ID);

    print_asa_dot_edge(output, p, p->decla_var.inst_mis);
    print_asa_dot_recursive(output, p->decla_var.inst_mis);

    break;
  case typePROG:

    print_asa_dot_edge(output, p, p->prog.DECLA);
    print_asa_dot_recursive(output, p->prog.DECLA);

    print_asa_dot_edge(output, p, p->prog.INST);

    print_asa_dot_recursive(output, p->prog.INST);
    break;
  case typeDECS:

    print_asa_dot_edge(output, p, p->decs.DEC);
    print_asa_dot_recursive(output, p->decs.DEC);

    print_asa_dot_edge(output, p, p->decs.next);
    print_asa_dot_recursive(output, p->decs.next);
    break;
  case typeLIST_DECLA:

    print_asa_dot_edge(output, p, p->list_decla.DEC);
    print_asa_dot_recursive(output, p->list_decla.DEC);

    print_asa_dot_edge(output, p, p->list_decla.next);
    print_asa_dot_recursive(output, p->list_decla.next);
    break;
  case typeDECLA_TAB:

    print_asa_dot_edge(output, p, p->decla_tab.id);
    print_asa_dot_recursive(output, p->decla_tab.id);

    print_asa_dot_edge(output, p, p->decla_tab.taille);
    print_asa_dot_recursive(output, p->decla_tab.taille);
    break;

  case typeDECLA_POIN:

    print_asa_dot_edge(output, p, p->decla_poin.id);
    print_asa_dot_recursive(output, p->decla_poin.id);

    break;

  case typeINST_ECRIRE:

    print_asa_dot_edge(output, p, p->inst_ecrire.EXP);
    print_asa_dot_recursive(output, p->inst_ecrire.EXP);

    break;
  case typeINST_LIRE:

    print_asa_dot_edge(output, p, p->inst_lire.ID);
    print_asa_dot_recursive(output, p->inst_lire.ID);

    break;
  case typeSTRUCT_TQ:

    print_asa_dot_edge(output, p, p->struct_tq.condition);
    print_asa_dot_recursive(output, p->struct_tq.condition);

    print_asa_dot_edge(output, p, p->struct_tq.inst);
    print_asa_dot_recursive(output, p->struct_tq.inst);
    break;
  case typeSTRUCT_SI:

    print_asa_dot_edge(output, p, p->struct_si.condition);
    print_asa_dot_recursive(output, p->struct_si.condition);

    print_asa_dot_edge(output, p, p->struct_si.inst_si);
    print_asa_dot_recursive(output, p->struct_si.inst_si);

    print_asa_dot_edge(output, p, p->struct_si.inst_si_non);
    print_asa_dot_recursive(output, p->struct_si.inst_si_non);
    break;
  case typeMAIN:

    print_asa_dot_edge(output, p, p->main.DEC);
    print_asa_dot_recursive(output, p->main.DEC);

    print_asa_dot_edge(output, p, p->main.L_DEC_FN);
    print_asa_dot_recursive(output, p->main.L_DEC_FN);

    print_asa_dot_edge(output, p, p->main.PROG);

    print_asa_dot_recursive(output, p->main.PROG);
    break;

  case typeDEC_FON:

    print_asa_dot_edge(output, p, p->dec_fon.ID);
    print_asa_dot_recursive(output, p->dec_fon.ID);

    print_asa_dot_edge(output, p, p->dec_fon.PARAM);
    print_asa_dot_recursive(output, p->dec_fon.PARAM);

    print_asa_dot_edge(output, p, p->dec_fon.DECS);
    print_asa_dot_recursive(output, p->dec_fon.DECS);

    print_asa_dot_edge(output, p, p->dec_fon.LIST_INST);
    print_asa_dot_recursive(output, p->dec_fon.LIST_INST);
    break;

  case typePARAM:
    print_asa_dot_edge(output, p, p->param.LIST_VAR);
    print_asa_dot_recursive(output, p->param.LIST_VAR);
    break;

  case typeRENVOYER:
    print_asa_dot_edge(output, p, p->renvoyer.INST);
    print_asa_dot_recursive(output, p->renvoyer.INST);
    break;
  case typeAPPFONC:
    print_asa_dot_edge(output, p, p->appfonc.ID);
    print_asa_dot_recursive(output, p->appfonc.ID);

    print_asa_dot_edge(output, p, p->appfonc.LIST_PARAM);

    print_asa_dot_recursive(output, p->appfonc.LIST_PARAM);
    break;
  case typeLIS_DEC_FON:
    print_asa_dot_edge(output, p, p->lis_dec_fon.dec_fon);
    print_asa_dot_recursive(output, p->lis_dec_fon.dec_fon);

    print_asa_dot_edge(output, p, p->lis_dec_fon.next);

    print_asa_dot_recursive(output, p->lis_dec_fon.next);
    break;
  case typeL_PARM_APPL:
    print_asa_dot_edge(output, p, p->l_param_appl.var);
    print_asa_dot_recursive(output, p->l_param_appl.var);

    print_asa_dot_edge(output, p, p->l_param_appl.next);

    print_asa_dot_recursive(output, p->l_param_appl.next);
    break;
  case typePARAM_APPL:
    print_asa_dot_edge(output, p, p->param_appl.id);
    print_asa_dot_recursive(output, p->param_appl.id);

    break;
  case typePON:
    print_asa_dot_edge(output, p, p->pon.id);
    print_asa_dot_recursive(output, p->pon.id);

    break;
  case typeALLOCATION:
    print_asa_dot_edge(output, p, p->allocation.id);
    print_asa_dot_recursive(output, p->allocation.id);

    print_asa_dot_edge(output, p, p->allocation.taille);
    print_asa_dot_recursive(output, p->allocation.taille);

    break;
  case typeINDICX_RECU:
    print_asa_dot_edge(output, p, p->indicx_recu.id);
    print_asa_dot_recursive(output, p->indicx_recu.id);

    print_asa_dot_edge(output, p, p->indicx_recu.index);
    print_asa_dot_recursive(output, p->indicx_recu.index);
    print_asa_dot_edge(output, p, p->indicx_recu.exp);
    print_asa_dot_recursive(output, p->indicx_recu.exp);

    break;
  case typeINDICX_SORT:
    print_asa_dot_edge(output, p, p->indicx_sort.id);
    print_asa_dot_recursive(output, p->indicx_sort.id);

    print_asa_dot_edge(output, p, p->indicx_sort.index);
    print_asa_dot_recursive(output, p->indicx_sort.index);

    break;

  default:
    break;
  }
}

int print_asa_dot(asa *p) {
  FILE *output_file = fopen("./out/output.dot", "w");
  if (output_file == NULL) {
    perror("Error opening output file");
    return 1; // Indicate failure
  }

  fprintf(output_file, "digraph ASA {\n");
  print_asa_dot_recursive(output_file, p);
  fprintf(output_file, "}\n");

  fclose(output_file);

  int result = system("dot -Tpng ./out/output.dot -o ./out/asa.png");
  if (result != 0) {
    fprintf(stderr, "Error generating PNG image\n");
    return 1; // Indicate failure
  }

  return 0; // Indicate success
}
