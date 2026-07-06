#ifndef INCLUDE_PARSER_AST_NODE_H
#define INCLUDE_PARSER_AST_NODE_H
#include "ast_type.h"

typedef struct ASTNode {
  ASTType type;
  unsigned int line;
  unsigned int column;

  union {
    double number;

    struct {
      const char* start;
      unsigned int length;
    } string_name;

    struct {
      int left;
      int right;
    } Math;

    struct {
      int value;
    } SaySTMT;
  } as;

} ASTNode;



#endif
