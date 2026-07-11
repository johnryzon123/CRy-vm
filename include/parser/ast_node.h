#ifndef INCLUDE_PARSER_AST_NODE_H
#define INCLUDE_PARSER_AST_NODE_H
#include "ast_type.h"

typedef struct ASTNode {
  // Bigger members first
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

    struct {
      int name;
      int value;
    } SetSTMT;
  } as;
  

  // Smaller members last
  unsigned int line;
  unsigned int column;
  ASTType type;
} ASTNode;

#endif
