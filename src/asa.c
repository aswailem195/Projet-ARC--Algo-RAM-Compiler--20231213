#include "../include/asa.h"

#include <stdio.h>
#include <stdlib.h>

static const char str_type[][16] = {"NB", "OP"};
static const char line[36] = "-----------------------------------";

static char buffer[32];
static char TABULATION[256] = "";
static int indent = 0;

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
  p->decla_var.DECLA = creer_feuilleID(id);
  p->decla_var.next = p1;

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
asa * creer_noeudMAIN( asa* p1 ,asa* p2 ){

  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeMAIN;
  p->main.INST= p2;
  p->main.DECLA = p1;

  return p;

}

asa * creer_noeudDECS(asa* p1 ,asa* p2) {
   asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeDECS;
  p->decs.DEC= p1;
  p->decs.next = p2;

  return p;
}
asa * creer_noeudLIST_DECLA(asa* p1 ,asa* p2) {

  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeLIST_DECLA;
  p->list_decla.DEC= p1;
  p->list_decla.next = p2;

  return p;
}
asa * creer_noeudDECLA_TAB( char* id  ,int value ){

  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    error_asa("echec allocation mémoire");

  p->type = typeDECLA_TAB;
  p->decla_tab.id= creer_feuilleID(id);
  p->decla_tab.taille = creer_feuilleNB(value);

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
  fprintf(output, "node%p [label=\"", p);
  switch (p->type) {
  case typeNB:
    fprintf(output, "NB\\n%d", p->nb.val);
    break;
  case typeID:
    fprintf(output, "ID\\n%s", p->id.nom);
    break;

  case typeOP:
    fprintf(output, "OP\\n%c", p->op.ope);
    break;

  case typeAFF:
    fprintf(output, "AFF\\n");
    break;
  case typeLIST_INST:
    fprintf(output, "LIST_INST\\n");
    break;
  case typeINST:
    fprintf(output, "INST\\n");
    break;
  case typeDECLA_VAR :
    fprintf(output, "DECLA_VAR\\n");
    break;
  case typeMAIN :
    fprintf(output, "MAIN\\n");
    break;
  case typeDECS:
    fprintf(output, "DECS\\n");
    break;

  case typeLIST_DECLA:
    fprintf(output, "LIST_DECLA\\n");
    break;
  case typeDECLA_TAB:
    fprintf(output, "DECLA_TAB\\n");
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
    
    print_asa_dot_edge(output, p, p->decla_var.DECLA);
    print_asa_dot_recursive(output, p->decla_var.DECLA);

    print_asa_dot_edge(output, p, p->decla_var.next);
    print_asa_dot_recursive(output, p->decla_var.next);

    break;
  case typeMAIN:
    
    print_asa_dot_edge(output, p, p->main.DECLA);
    print_asa_dot_recursive(output, p->main.DECLA);

    print_asa_dot_edge(output, p, p->main.INST);
    print_asa_dot_recursive(output, p->main.INST);
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
