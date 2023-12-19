%{
  #include <string.h>
  #include "parser.h"

  extern void yyerror(char *);

  char errmsg[256]="";
  const char charerr[] = "\x1b[1m\x1b[31m[erreur lexicale]\x1b[0m caractère \x1b[41m%c\x1b[0m inattendu";
  
  /* MACRO défini 
   * Action executee avant chaque action semantique (meme vide)  
   * et rempli la variable Bison `yylloc` avec la position du token
   */
#define YY_USER_ACTION                                             \
  yylloc.first_line = yylloc.last_line;                            \
  yylloc.first_column = yylloc.last_column;                        \
  if (yylloc.last_line == yylineno)                                \
    yylloc.last_column += yyleng;                                  \
  else {                                                           \
    yylloc.last_line = yylineno;                                   \
    yylloc.last_column = 1;					   \
  }



%}
%option nounput
%option noinput
%option yylineno

CHIFFRE  [0-9]
NOMBRE   [0-9]+
IDENT    [a-z]+


%%

{NOMBRE}        {  yylval.nb = atoi(yytext); return NB; }
{IDENT}         { strcpy(yylval.id, yytext); return ID; }
"PROGRAMME"     { return PROGRAMME; } /*Pour qu'il reconnaisse le mot PROGRAMME dans exemple1*/
"DEBUT"         { return DEBUT; } /*Pour reconnaitre le mot DEBUT dans exemple1*/
"FIN"           { return FIN; } /* Pour reconnaitre le mot FIN dans l'exemple1 */

"<-"           { return AFF; }

"VAR"         { return VAR;}


"ET"          { return ET;}
"OU"          { return OU;}
"NON"         { return NON;}
"<="          { return INFEGAL;}
">="          { return SUPEGAL;}
"!="          { return DIFF;}
"<"           { return '<';}
">"           { return '>';}
"="           { return EGAL;}




[-*+/=%\n(),@]      {return *yytext;}

"]"      {return *yytext;}
"["      {return *yytext;}

[ \t]           { /* ignorer les blancs */ }



"ECRIRE"  {return ECRIRE ;}
"LIRE"   {return LIRE ;}

"FSI"   {return FSI;}
"SINON"  {return SINON ; }
"ALORS" {return ALORS;}
"SI"   {return SI;}
"FTQ" {return FTQ; }
"FAIRE" {return FAIRE;}
"TQ" {return TQ ;}


.         {           
	    sprintf(errmsg,charerr, yytext[0]);
            yyerror(errmsg);
            return 1;
          }

%%
 
