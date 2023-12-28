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
  char CTXTglo[32] = "GLOBAL";



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

%type <tree> PROGRAMME_ALGO PROGRAMME EXP AFFECT INST LIST_INST DECLA_VAR LIST_DECLA DECS DECLA_TAB DECLA_POIN
%type <tree> INST_ECRIRE INST_LIRE INST_RENVOYER
%type <tree> STRUCT_TQ STRUCT_SI 
%type <tree> LIS_DEC_FON DEC_FON PROG PARAM APPFONC LIST_VAR  PON  INT PARAM_F
%type <tree>  ALLOCATION  INDICX_RECU INDICX_SORT

%token <nb> NB VRAI FAUX  
%token <id> ID
%token PROGRAMME DEBUT FIN VAR ECRIRE LIRE NON  
%start PROGRAMME_ALGO
%token TQ FAIRE FTQ SI ALORS SINON FSI RENVOYER
%token  ALGO

%token  ALLOUER


%right AFF
%left OU
%left ET
%precedence NON
%left '<' '>' EGAL SUPEGAL INFEGAL DIFF

%left '+' '-'
%left '*' '/' '%'



%%




/*_____________________ main  PROGRAMME_ALGO ___________________________________________*/

PROGRAMME_ALGO : DECS
                 LIS_DEC_FON
                 PROG   {$$ = creer_noeudMAIN( $1 ,$2 , $3 ); ARBRE_ABSTRAIT=$$; }
;
/*____________________pointor__________________________________*/

ALLOCATION :
ALLOUER '(' ID ',' EXP ')'           {$$ = creer_noeudALLOCATION($3 ,$5 );}       
; 

/*_______________________________indexation de tableau___________________________*/
//comme T[i] <- 5  consider comme id 
INDICX_RECU :ID'[' EXP']' AFF INDICX_RECU    {$$ = creer_noeudINDICX_RECU($1 ,$3,$6 );}
|ID'[' EXP']' AFF EXP               {$$ = creer_noeudINDICX_RECU($1 ,$3,$6  );}  
|ID'[' EXP']' AFF INST_LIRE         {$$ = creer_noeudINDICX_RECU($1 ,$3,$6  );}  
;

//comme  +T[i]+5  consider comme EXP 
INDICX_SORT :ID'[' EXP']'        {$$ = creer_noeudINDICX_SORT($1 ,$3 );}
;


/*_____________________ fonction ____________________________________________*/
LIS_DEC_FON : DEC_FON SEP  LIS_DEC_FON  {$$ = creer_noeudLIS_DEC_FON($1 ,$3 );}
|DEC_FON SEP                            {$$ = creer_noeudLIS_DEC_FON($1 ,NULL );}
|%empty   {$$ =NULL ;}
;

DEC_FON:ALGO ID '(' PARAM_F ')' SEP 
      DECS 
      DEBUT SEP
      LIST_INST 
      FIN     {$$ = creer_noeudDEC_FON($2, $4, $7 , $10 );}
;



/* pour le declar   */
PARAM_F :LIST_DECLA       { $$ = $1;}
|%empty                   {$$= NULL ;}
;


/* pour lappele   */
PARAM : LIST_VAR     {$$ = $1;}
|%empty                 {$$ = NULL ;}
;
LIST_VAR :INT ','LIST_VAR   {$$ = creer_noeudLIST_VAR( $1 ,$3 );}
|PON ','LIST_VAR            {$$ = creer_noeudLIST_VAR( $1 ,$3 );}
|INT                            {$$ = creer_noeudLIST_VAR( $1 ,NULL );}
|PON                         {$$ = creer_noeudLIST_VAR( $1 ,NULL );}               
;


INT : ID                 {$$ = creer_noeudINT( $1);}
;
PON : '@' ID              {$$ = creer_noeudPON( $2 );}
;





/*_____________________ PROG____________________________________________*/
PROG :
PROGRAMME '(' ')'  SEP
DECS
DEBUT SEP
LIST_INST 
FIN    {$$ = creer_noeudPROG( $5 ,$8 );}
;
SEP: '\n' | SEP '\n'  

;


INST_RENVOYER: RENVOYER EXP  {$$ = creer_noeudRENVOYER($2);}
;

/*___________________________TQ _____________________*/
STRUCT_TQ : TQ EXP FAIRE SEP LIST_INST  FTQ  {$$ = creer_noeudSTRUCT_TQ($2,$5);}
;
/*___________________________si _____________________*/
STRUCT_SI: 
  SI EXP ALORS SEP 
      LIST_INST
  SINON SEP 
      LIST_INST
  FSI   {$$ = creer_noeudSTRUCT_SI($2, $5, $8);}
| SI EXP ALORS SEP
    LIST_INST 
  FSI  {$$ = creer_noeudSTRUCT_SI($2, $5, NULL);}
;

/*___________________________LIRE _____________________*/
INST_LIRE : ID AFF LIRE '(' ')' {$$ = creer_noeudINST_LIRE($1);}
;
/*___________________________ECRIRE _____________________*/

INST_ECRIRE :ECRIRE '(' EXP ')' {$$ = creer_noeudINST_ECRIRE($3);}
;

/*___________________________declaration _____________________*/

DECS : VAR LIST_DECLA SEP    {$$ = creer_noeudDECS($2,NULL);}
    | VAR LIST_DECLA SEP DECS {$$ = creer_noeudDECS($2,$4);}
    |%empty                    {$$= NULL;}
    ; 

LIST_DECLA : DECLA_VAR     {$$ = creer_noeudLIST_DECLA($1,NULL);}
|DECLA_TAB                  {$$ = creer_noeudLIST_DECLA($1,NULL);}
|DECLA_POIN                 {$$ = creer_noeudLIST_DECLA($1,NULL);}
|DECLA_VAR ',' LIST_DECLA {$$ = creer_noeudLIST_DECLA($1,$3);}
|DECLA_TAB   ',' LIST_DECLA {$$ = creer_noeudLIST_DECLA($1,$3);}
|DECLA_POIN   ',' LIST_DECLA {$$ = creer_noeudLIST_DECLA($1,$3);}

 
;

DECLA_VAR : ID   {$$ = creer_noeudDECLA_VAR( $1  ,NULL );}    
| ID AFF EXP    {$$ = creer_noeudDECLA_VAR( $1  ,$3 );} 
;
DECLA_TAB : ID '[' NB ']'  {$$ = creer_noeudDECLA_TAB( $1  ,$3 );}    
;
DECLA_POIN : '@' ID   {$$ = creer_noeudDECLA_POIN( $2 );}
;

/*___________________________inistraction _____________________*/

LIST_INST : INST SEP {$$  = creer_noeudLIST_INST( $1,NULL );}
|INST SEP LIST_INST   {$$  = creer_noeudLIST_INST( $1,$3 );}
|%empty               {$$ = NULL; }

;

INST : AFFECT  {$$= $1 ;}
|EXP  {$$= $1 ;}
|INST_ECRIRE {$$= $1 ;}
|INST_LIRE {$$= $1 ;}
|STRUCT_TQ {$$= $1 ;}
|STRUCT_SI {$$= $1 ;}
|INST_RENVOYER  {$$= $1 ;}
|ALLOCATION   {$$= $1 ;}
|APPFONC       {$$ = $1;}
|INDICX_RECU  {$$ = $1;}
;

/*___________________________affictation _____________________*/
AFFECT: ID AFF EXP      { $$ = creer_noeudAffic($1, $3); }
      | ID AFF AFFECT      { $$ = creer_noeudAffic($1, $3); }
      
      ;
/*___________________________APPFONC _____________________*/
APPFONC : ID '(' PARAM ')' { $$ = creer_noeudAPPFONC ($1, $3); }
;



/*___________________________EXP_____________________*/
EXP : '(' EXP ')'            { $$ = $2; }
|APPFONC        {$$ = $1;}
|INDICX_SORT   {$$ = $1;}
|NB                 { $$ = creer_feuilleNB(yyval.nb); }
|VRAI                { $$ = creer_feuilleNB(1); }
|FAUX                   { $$ = creer_feuilleNB(0); }
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

| EXP DIFF EXP {$$ = creer_noeudOP(OP_DIFF,$1 ,$3);}

| EXP INFEGAL EXP {$$ = creer_noeudOP(OP_INF_EG,$1 ,$3);}

| EXP SUPEGAL EXP {$$ = creer_noeudOP(OP_SUP_EG,$1 ,$3);}

| EXP EGAL EXP {$$ = creer_noeudOP('=', $1 ,$3);}

| EXP OU EXP {$$ = creer_noeudOP('|',$1 ,$3);}

| EXP ET EXP {$$ = creer_noeudOP('&',$1 ,$3);}

| NON EXP     {$$ = creer_noeudOP('!',$2 ,NULL);}

| '-' EXP     {$$ = creer_noeudOP(M_UN,$2 ,NULL);}







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
  strcpy(exename, "out.ram");
  if (argc == 3){
    strcpy(exename, argv[2]);
  }
  
  exefile = fopen(exename,"w");
  yyparse();

  //_____________________________la on modifier 






  TABLE_SYMBOLES = ts_init_table(CTXTglo) ;
  
  semantic(ARBRE_ABSTRAIT);
  print_asa_dot( ARBRE_ABSTRAIT);
  


  

  

  
  //print_asa(ARBRE_ABSTRAIT);
  ts_print(TABLE_SYMBOLES);
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
