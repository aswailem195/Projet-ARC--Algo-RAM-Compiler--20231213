#include "ts.h"

static const char str_type[][ID_SIZE_MAX] =  {"ENTIER","TABLEAU","POINTEUR","FONCTION"};
static const char str_field[][ID_SIZE_MAX] = {IDE,TYPE,ADR,SIZE};

/*
 * FUNCTION: ts_init_table
 * -----------------------
 * initialise et retourne une table de symbole contenant le contexte 
 * par default DEFAULT_CONTEXT
 * 
 *
 * return:
 *        un pointeur vers la table de symbole
 */
table_symb ts_init_table(char *context_name){
  table_symb table = NULL;
  if ( (table = calloc(sizeof(contexte),1)) == NULL ){
    fprintf(stderr,"[ts_init_table]  impossible d'initialiser la table de symbole\n");
    exit(1);
  }
  
  strcpy(table->name,context_name);
  table->liste_symbole = NULL;
  table->next = NULL;

  return table;
}
/*
 * FUNCTION: ts_ajouter_contexte
 * -----------------------------
 * ajoute le contexte `context_name` à la table de symbole. Emet un avertissement si
 * le contexte est déjà présent
 *
 * param:
 *        `table`: table de symbole
 *        `context_name`: chaine de char
 *
 * return:
 *        un pointeur vers le nouveau contexte
 */
contexte * ts_ajouter_contexte(table_symb  table, char *context_name){
  if (table == NULL){
    fprintf(stderr,"[Erreur ts_ajouter_contexte] la table n'est pas initialisee\n");
    exit(1);
  }
  contexte * context = table;
  // On cherche si le contexte existe deja dans la table
  while ( context->next != NULL )
    if ( strcmp(context->name, context_name)==0 )
      break;
    else
      context = context->next;

  // S'il existe on souleve un avertissement
  if ( strcmp(context->name, context_name)==0 ){
    fprintf(stderr,"[warning ts_ajouter_contexte] contexte `%s` deja present\n", context_name);
    return context;
  }

  // sinon on cree le contexte et on l'initialise
  context->next = calloc(sizeof(contexte),1);
  context = context->next;
  strcpy(context->name,context_name);
  context->liste_symbole = NULL;
  context->next = NULL;
  return context;
}

/*
 * FUNCTION: ts_rechercher_contexte
 * -----------------------------
 * recherche le contexte `context_name` dans la table de symbole et renvoie le pointeur 
 * correspond, NULL si absent
 *
 * param:
 *        `table`: table de symbole
 *        `context_name`: chaine de char
 *
 * return:
 *        un pointeur vers le  contexte
 */
contexte * ts_rechercher_contexte(table_symb table, char *context_name){
  if (table == NULL){
    fprintf(stderr,"[Erreur ts_ajouter_contexte] la table n'est pas initialisee\n");
    exit(1);
  }
  contexte * context = table;
  // On cherche si le contexte existe deja dans la table
  while ( context != NULL )
    if ( strcmp(context->name, context_name)==0 )
      return context;
    else
      context = context->next;
  return NULL;
}

/*
 * FUNCTION: ts_rechercher_identificateur
 * --------------------------------------
 * recherche l'identificateur `id` dans la table de symbole du contexte 'context'
 * et renvoie le pointeur  correspond, NULL si absent
 *
 * param:
 *        `table`: table de symbole
 *        `id`: un identificateur 
 *        `context`: un contexte sous forme de char *r
 *
 * return:
 *        un pointeur vers le  contexte
 */
symbole * ts_rechercher_identificateur(table_symb table, char *id, char *context_name){
  if (table == NULL){
    fprintf(stderr,"[Erreur ts_ajouter_identificateur] la table n'est pas initialisee\n");
    exit(1);
  }
  contexte * context = ts_rechercher_contexte(table, context_name);
  if ( context == NULL ){
    fprintf(stderr,"[Erreur ts_ajouter_identificateur] contexte `%s` n'est pas déclaré\n", context_name);
    exit(1);
  }

  //La liste est vide l'identificateur n'existe pas 
  if (context->liste_symbole == NULL) return NULL;

  //La liste n'est pas vide on parcours
  symbole * symb = context->liste_symbole;
  while (symb != NULL){
    // Si on trouve l'identificateur on le renvoie
    if (strcmp(symb->id, id) == 0) return symb;
    symb = symb->next;
  }
  return NULL;
}

/*
 * FUNCTION: ts_ajouter_symbole
 * ----------------------------
 * ajoute le symbole `id` dans le contexte `contexte` si celui-ci existe déjà, un warning est affiché
 * 
 * param:
 *        `table` : un table de symbole
 *        `id` : le symbole a ajouter
 *        `context`: le contexte dans lequel il doit être ajouté
 *        `size`: la taille de la donnée en nombre de cas mémoire
 *
 * return:
 *        un pointeur vers le symbole ajouté
 */
symbole * ts_ajouter_identificateur(table_symb  table, char *context_name, char *id,  int type, int size){
  // On recherche le contexte et s'il n'existe pas on le cree
  contexte * context = ts_rechercher_contexte(table, context_name);
  if (context == NULL) context = ts_ajouter_contexte(table, context_name);

  // La liste de symbole est vide
  if (context->liste_symbole == NULL){
    symbole * symb = (context->liste_symbole = calloc(sizeof(symbole), 1));
    strcpy(symb->id, id);
    symb->type = type;
    symb->size = 1;
    symb->next = NULL;
    return symb;
  }

  // La liste de symbole n'est pas vide on recherche le symbole et
  // s'il n'y est pas on l'ajoute
  symbole * prev=NULL, * symb = context->liste_symbole;
  while (symb != NULL){
    prev = symb;
    if (strcmp(symb->id, id) == 0){
      fprintf(stderr,"\x1b[31m[Warning ts_ajouter_symbole]\x1b[0m symbole \x1b[32m%s\x1b[0m deja presente dans le contexte \x1b[32m%s\x1b[0m\n", id, context_name);
      return symb;
    }
    symb = symb->next;
  }

  symb = prev;
  symb = (symb->next = calloc(sizeof(symbole), 1));
  strcpy(symb->id, id);
  symb->type = type;
  symb->size = 1;
  symb->next = NULL;
  
  return symb;
}


/*
 * FUNCTION: ts_print
 * ------------------
 *
 * affiche la table de symbole `table`

 * param:
 *       'table' la table de symbole
 *
 */

void print_context(contexte * context, int size){
  char buffer[256]="";
  char line[256]="";

  int taille = MIN(MIN_SIZE, size)*4;
  int center_l = taille+strlen(context->name)/2+2;
  int center_r = taille-strlen(context->name)/2+1;
  sprintf(buffer, CONTEXTE "%*s%*s|", center_l, context->name , center_r, "");

  for (int i=0; i<strlen(buffer); i++)line[i]='-';
  
  printf(BR "%s\n%s\n%s\n" RB, line,buffer, line);
}

void print_liste_symbole(symbole * symb, int size){
  char buffer[256]="", temp[256]=TAB;
  char line[256]="-";
  int taille = MIN(MIN_SIZE, size);
  

  for (int i=0; i<4; i++){
    int center_l = taille+strlen(str_field[i])/2;
    int center_r = taille-strlen(str_field[i])/2;
    sprintf(temp, BR "%*s" RB "%*s|", center_l, str_field[i] , center_r, "");
    strcat(buffer,temp);
  }
  
  //On retranche 4*(strlen(BR)+strlen(RB)) pour prendre en compte les ANSI Escape Sequences 
  for (int i=0; i<strlen(buffer)-4*(strlen(BR)+strlen(RB)); i++)line[i+1]='-';

 
  printf("%s|%s\n", TAB, buffer);
  
  while (symb != NULL){
    int center_l = taille+strlen(symb->id)/2;
    int center_r = taille-strlen(symb->id)/2;
    int type;
    switch (symb->type){
    case 'e':
      type = ENTIER;
      break;
    case 't':
      type = TABLEAU;
      break;
    case 'p':
      type = POINTEUR;
      break;
    case 'f':
      type = FONCTION;
      break;
    default:
      break;
    }
    buffer[0] = '\0';
    sprintf(temp,"%*s%*s|", center_l, symb->id, center_r, ""); strcat(buffer,temp);
    sprintf(temp,"%*s%*s|", 2*taille-1, str_type[type],1 ,""); strcat(buffer,temp);
    sprintf(temp,"%*d%*s|", 2*taille-1, symb->adr,1 ,""); strcat(buffer,temp);
    sprintf(temp,"%*d%*s|", 2*taille-1, symb->size,1 ,""); strcat(buffer,temp);
    printf(TAB "%s\n%s|%s\n", line, TAB, buffer);
    symb = symb->next;
    }

  printf(TAB "%s\n", line);
}

void ts_print(table_symb  table){
  if (table == NULL) return;

  // on recherche le plus long contexte
  contexte * context = table;
  int  max_id_size = 0;
  while (context != NULL){
    max_id_size = MAX( (max_id_size), strlen(context->name) );
    // on recherche l'id le plus long
    symbole * symb = context->liste_symbole;
    while ( symb != NULL ){
      max_id_size = MAX( (max_id_size), strlen(symb->id) );
      symb = symb->next;
    }
    context = context->next;
  }

  context = table;
  while (context != NULL){
    print_context(context, max_id_size);
    symbole * symb = context->liste_symbole;
    print_liste_symbole(symb, max_id_size);
  
    context = context->next;
  }
}

/*
 * FUNCTION: ts_free_table
 * -----------------------
 *
 * libere la mémoire de la table de symbole

 * param:
 *       'table' la table de symbole
 *
 */
void ts_free_table(table_symb  table){
  if (table == NULL) return;

  symbole * current, *next; 
  table_symb  t = table, next_t;

  while ( t != NULL ){
    current = t->liste_symbole;
    while (current != NULL){
      next = current->next;
      free(current);
      current = next;
    }
    next_t = t->next;
    free(t);
    t = next_t;
  }
}
