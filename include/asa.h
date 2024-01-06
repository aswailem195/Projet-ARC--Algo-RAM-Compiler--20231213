#ifndef ASA_H
#define ASA_H


//macro
#define  OP_INF_EG  'S'
#define OP_SUP_EG 'N'
#define  OP_DIFF  'D'

#define   M_UN    'U'




#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define  MAX_SIZE_FIELD_NAME  12
#define  MAX_SIZE_FIELD_VAL   32
#define  TXT_RED    "\x1b[31m"
#define  TXT_GREEN  "\x1b[32m"
#define  TXT_BLUE   "\x1b[34m"
#define  TXT_BOLD   "\x1b[1m"
#define  TXT_NULL   "\x1b[0m"

#define TYPE_ENTIER  'e'
#define TYPE_TABLEAU 't'
#define TYPE_PTR     'p'
#define TYPE_FCT     'f'
//___________________type__________________
typedef enum {typeNB, typeOP, typeID,typeAFF ,typeINST,typeLIST_INST,typeDECLA_VAR,typePROG ,
typeDECS,typeLIST_DECLA,typeDECLA_TAB,typeDECLA_POIN,
typeINST_ECRIRE,typeINST_LIRE,typeSTRUCT_TQ , typeSTRUCT_SI , 
typeMAIN ,typeDEC_FON , typePARAM ,typeRENVOYER ,typeAPPFONC ,typeLIS_DEC_FON ,
typePARAM_APPL ,typePON ,typeL_PARM_APPL ,typeALLOCATION ,typeINDICX_RECU ,  typeINDICX_SORT} typeNoeud;

typedef  enum {t_AFF ,t_EXP} t_INST ;


//___________________feuille__________________

typedef struct {
  int val;
  
} feuilleNb;

//L'identificateur
typedef struct {
  char nom[32];
  char *ctxt ; // pour indiqer la port de variable 
  int  type ;  // pour int , point t , p 
  //utile pour l'app de fonc par variable 


  int adr ; //le meme
  int adr_app;//la adress de applant 
  int adr_PTR  ; //si le ID est pointeu ou table il stocke sans adr dans le tas 
} feuilleId;


//___________________noeud__________________
typedef struct {
  int ope;
  char * nom ;
  struct asa * noeud[2];
} noeudOp;
typedef struct {
  struct asa *id ;
  struct asa *droit ;
}noeuAFFECT ;

typedef struct 
{ 
   
  struct asa *INST ;
  
}noeudINST ;

typedef struct {
  struct asa *INST ;
  struct asa *next ;
}noeudLIST_INST ;


typedef struct {
  struct asa *ID ;
  struct asa *inst_mis ;
}noeudDECLA_VAR ;

typedef struct {
  struct asa *DECLA ;
  struct asa *INST ;
}noeudPROG ;

typedef struct {
  struct asa *DEC;
  struct asa *next ;
}noeudDECS ;


typedef struct {
  struct asa *DEC;
  struct asa *next ;
}noeudLIST_DECLA ;


typedef struct {
  struct asa *id ;
  struct asa *taille ;
}noeudDECLA_TAB;

typedef struct {
  struct asa *id ;
}noeudDECLA_POIN;
typedef struct {
  struct asa * EXP ;
}noeudINST_ECRIRE ;

typedef struct {
  struct asa * ID ;
}noeudINST_LIRE ;


typedef struct {
  struct asa *condition;
  struct asa * inst ;
}noeudSTRUCT_TQ ;


typedef struct {
  struct asa *condition;
  struct asa * inst_si ;
  struct asa * inst_si_non ;
}noeudSTRUCT_SI ;

typedef struct {
  struct asa *DEC;
  struct asa * L_DEC_FN ;
  struct asa * PROG;
  int nb_valiable_local;
}noeudMAIN ;

typedef struct {
  struct asa * ID;
  struct asa * PARAM ;
  struct asa * DECS;
  struct asa * LIST_INST;
}noeudDEC_FON;

typedef struct {
  struct asa * LIST_VAR;
}noeudPARAM;


typedef struct {
  struct asa * INST;
}noeudRENVOYER ;

typedef struct {
  struct asa *ID;
  struct asa * LIST_PARAM ;
}noeudAPPFONC ;

typedef struct {
  struct asa *dec_fon;
  struct asa * next  ;
}noeudLIS_DEC_FON ;

typedef struct {
  struct asa *id ;
}noeudPARAM_APPL ;


typedef struct {
  struct asa *id ;
}noeudPON ;

typedef struct {
  struct asa * var;
  struct asa * next  ;
}noeudL_PARM_APPL; // LIST de parametre dans la apple de fonction 


typedef struct {
  struct asa * id;
  struct asa * taille ;
}noeudALLOCATION ;

typedef struct {
  struct asa * id;
  struct asa * index ;
  struct asa * exp ;

}noeudINDICX_RECU ;


typedef struct {
  struct asa * id;
  struct asa * index ;
}noeudINDICX_SORT ;
//_____________________asa_____________________
typedef struct asa{
  typeNoeud type;
  int memadr;
  int codelen;
  union {
    feuilleNb nb;
    noeudOp op;
    feuilleId id;
    noeuAFFECT affect ;
    noeudINST  inst;
    noeudLIST_INST  list_inst;
    noeudDECLA_VAR decla_var ;
    noeudPROG prog;
    noeudDECS decs ;
    noeudLIST_DECLA list_decla;
    noeudDECLA_TAB  decla_tab ;
    noeudDECLA_POIN decla_poin ;
    noeudINST_ECRIRE inst_ecrire ;
    noeudINST_LIRE   inst_lire ;
    noeudSTRUCT_TQ  struct_tq ;
    noeudSTRUCT_SI  struct_si ;
    noeudMAIN  main ;
    noeudDEC_FON dec_fon;
    noeudPARAM param;
    noeudRENVOYER renvoyer ;
    noeudAPPFONC appfonc ;
    noeudLIS_DEC_FON lis_dec_fon ;
    noeudPARAM_APPL param_appl ;
    noeudPON pon ;
    noeudL_PARM_APPL l_param_appl ;
    noeudALLOCATION allocation ;
   noeudINDICX_SORT indicx_sort ;
   noeudINDICX_RECU indicx_recu ;
    
  };
} asa;





//__________________
asa * creer_feuilleNB( int value );
asa * creer_noeudOP( int ope, asa * p1, asa * p2 );
asa * creer_feuilleID(char* nom);

asa * creer_noeudAffic( char* id , asa * p1 );
asa * creer_noeudINST(asa* p1) ;
asa * creer_noeudLIST_INST(asa* p1 ,asa* p2) ;
asa * creer_noeudDECLA_VAR( char* id   ,asa* p1 );
asa * creer_noeudPROG( asa* p1 ,asa* p2 );
asa * creer_noeudDECS(asa* p1 ,asa* p2) ;
asa * creer_noeudLIST_DECLA(asa* p1 ,asa* p2) ;
asa * creer_noeudDECLA_TAB( char* id  ,int value );
asa * creer_noeudDECLA_POIN( char* id );
asa * creer_noeudINST_ECRIRE(asa * p1);
asa * creer_noeudINST_LIRE( char* id  );
asa * creer_noeudSTRUCT_TQ(asa* p1 ,asa* p2);
asa * creer_noeudSTRUCT_SI(asa* p1 ,asa* p2 ,asa* p3);
asa * creer_noeudMAIN( asa* p1 ,asa* p2 ,asa* p3 );
asa * creer_noeudDEC_FON(char* id ,asa* p2 ,asa* p3, asa* p4);
asa * creer_noeudPARAM(asa* p1 );
asa * creer_noeudRENVOYER(asa* p1) ;
asa * creer_noeudAPPFONC (char* id ,asa* p2);
asa * creer_noeudLIS_DEC_FON(asa* p1 ,asa* p2);
asa* creer_noeudLIST_VAR(asa* p1 ,asa* p2) ;
asa* creer_noeudPARAM_APPL(char* id) ;
asa* creer_noeudPON(char* id) ;
asa*  creer_noeudINDICX_SORT(char* id ,asa* p2 ); 
asa* creer_noeudINDICX_RECU(char* id ,asa* p2,asa*  p3 ) ;


asa* creer_noeudALLOCATION(char* id ,asa* p2); 




//____________________
void free_asa(asa *p);


//__________________
void print_asa(asa * p);
void print_typeOP(asa *p);
void print_typeNB(asa *p);

/*affichage de arbe par dot */
void print_asa_dot_node(FILE *output, asa *p);
void print_asa_dot_edge(FILE *output, asa *parent, asa *child) ;
void print_asa_dot_recursive(FILE *output, asa *p);
int print_asa_dot( asa *p);

void error_asa(const char * s);

#endif
