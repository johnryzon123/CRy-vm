#ifndef INCLUDE_PARSER_PRECEDENCE_H
#define INCLUDE_PARSER_PRECEDENCE_H
#include "ast_type.h"

typedef struct Precedence {
  ASTType node_type;
  int weight;
} Precedence;
/* using extern to put the values into a source file and
    reduce building the entire language just for one change on the table */
extern Precedence precedence_table[];

#endif
