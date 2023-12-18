%{
  #include <stdio.h>
  #include <ctype.h>
  #include <string.h>
  
  #include "../include/asa.h"
  #include "../include/ts.h"
  #include "semantic.h"
  #include "codegen.h"
  
  extern int yylex();
  static void print_file_error(char * s, char *errmsg);

  table_symb TABLE_SYMBOLES = NULL;
  struct asa * ARBRE_ABSTRAIT = NULL;

  void yyerror(const char * s);

  char srcname[64];
  char exename[64] = "a.out";
  FILE * exefile;
%}

%union{
  int nb;
  struct asa * tree;
  char id[32];
 };

%define parse.error verbose
%locations

%type <tree> PROGRAMME_ALGO PROGRAMME EXP AFFECT INST LIST_INST DECLA_VAR



%token <nb> NB
%token <id> ID
%token PROGRAMME DEBUT FIN VAR
%start PROGRAMME_ALGO



%right AFF
%left OU
%left ET
%precedence NON
%left '<' '>' EGAL SUPEGAL INFEGAL DIFF

%left '+' '-'
%left '*' '/' '%'



%%


PROGRAMME_ALGO : 
PROGRAMME '(' ')'  SEP
VAR DECLA_VAR SEP
DEBUT SEP
LIST_INST 
FIN SEP  { $$  = creer_noeudMAIN( $6,$10 ) ; ARBRE_ABSTRAIT = $$;  }
;

SEP: '\n' | SEP '\n'
;

//___________________________declaration _____________________

DECLA_VAR : ID  {$$  = creer_noeudDECLA_VAR( $1,NULL );}
|ID ',' DECLA_VAR {$$  = creer_noeudDECLA_VAR( $1,$3 );}
;
//___________________________inistraction _____________________

LIST_INST : INST {$$  = creer_noeudLIST_INST( $1,NULL );}
|INST LIST_INST   {$$  = creer_noeudLIST_INST( $1,$2 );}

;
INST : AFFECT  {$$ = creer_noeudINST($1) ;}
|EXP SEP {$$ = creer_noeudINST($1) ;}
;


//___________________________affictation _____________________
AFFECT: ID AFF EXP SEP     { $$ = creer_noeudAffic($1, $3); }
      | ID AFF AFFECT      { $$ = creer_noeudAffic($1, $3); }
      ;




//___________________________EXP_____________________
EXP : '(' EXP ')'            { $$ = $2; }
|NB                 { $$ = creer_feuilleNB(yyval.nb); }
|ID                     { $$ = creer_feuilleID($1); }

| EXP '+' EXP            { $$ = creer_noeudOP('+', $1, $3); }
| EXP '-' EXP            { $$ = creer_noeudOP('-', $1, $3); }
| EXP '*' EXP            { $$ = creer_noeudOP('*', $1, $3); }
| EXP '/' EXP            { $$ = creer_noeudOP('/', $1, $3); }
| EXP '%' EXP            { $$ = creer_noeudOP('%', $1, $3); }

/* Opérations de comparaisons booléennes,
   Plus délicates à traduire en RAM car il y a beaucoup de JUM[ZP]
*/

| EXP '<' EXP {$$ = creer_noeudOP('<',$1 ,$3);}

| EXP '>' EXP {$$ = creer_noeudOP('>',$1 ,$3);}

| EXP DIFF EXP {$$ = creer_noeudOP(DIFF,$1 ,$3);}

| EXP INFEGAL EXP {$$ = creer_noeudOP(INFEGAL,$1 ,$3);}

| EXP SUPEGAL EXP {$$ = creer_noeudOP(SUPEGAL,$1 ,$3);}

| EXP EGAL EXP {$$ = creer_noeudOP('=', $1 ,$3);}

| EXP OU EXP {$$ = creer_noeudOP('|',$1 ,$3);}

| EXP ET EXP {$$ = creer_noeudOP('&',$1 ,$3);}





;

%%

int main( int argc, char * argv[] ) {
  extern FILE *yyin;
  
  if (argc > 1){
    strcpy(srcname, argv[1]);
    if ( (yyin = fopen(srcname,"r"))==NULL ){
      char errmsg[256];
      sprintf(errmsg,"fichier \x1b[1m\x1b[33m' %s '\x1b[0m introuvable",srcname);
      print_file_error(argv[0],errmsg);
      exit(1);
    }
  }  else {
    print_file_error(argv[0],"aucun fichier en entree");
    exit(1);
  }
  if (argc == 3){
    strcpy(exename, argv[2]);
  }
  
  exefile = fopen(exename,"w");
  yyparse();

  //_____________________________la on modifier 

  int init = 128;
  int registre = 2;
  fprintf(exefile, "LOAD #%-7d ;\n", init);
  fprintf(exefile, "STORE @%-6d ;\n", registre);

  semantic(ARBRE_ABSTRAIT);


  

  print_asa_dot( ARBRE_ABSTRAIT);

  
  print_asa(ARBRE_ABSTRAIT);
  codegen(ARBRE_ABSTRAIT);






  fclose(yyin);
}



static void print_file_error(char * prog, char *errmsg){
  fprintf(stderr,
	  "\x1b[1m%s:\x1b[0m \x1b[31m\x1b[1merreur fatale:\x1b[0m %s\nechec de la compilation\n",
	  prog, errmsg);
}

void yyerror(const char * s)
{
  fprintf(stderr, "\x1b[1m%s:%d:%d:\x1b[0m %s\n", srcname, yylloc.first_line, yylloc.first_column, s);
  exit(0);
}
