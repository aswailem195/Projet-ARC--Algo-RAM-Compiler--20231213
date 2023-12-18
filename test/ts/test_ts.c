#include "ts.h"

int main(){
  
  table_symb  table = NULL;
  table = ts_init_table("global");
  ts_ajouter_identificateur(table, "global", "main", 'f', 0);
  ts_ajouter_identificateur(table, "global", "f", 'f',0);
  ts_ajouter_contexte(table, "main");
  ts_ajouter_identificateur(table, "main", "f", 'f',0);
  ts_ajouter_identificateur(table, "main", "ptr", 'p',0);
  ts_ajouter_identificateur(table, "f", "i", 'e',0);
  ts_ajouter_identificateur(table, "f", "x", 'e',0);
  ts_ajouter_identificateur(table, "f", "tab", 't',0);
  ts_ajouter_identificateur(table, "f", "i", 'e',0);

  ts_print(table);

  ts_free_table(table);
  return 0;
}
