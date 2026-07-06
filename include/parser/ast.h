#ifndef INCLUDE_PARSER_AST_H
#define INCLUDE_PARSER_AST_H

typedef struct ASTNode ASTNode;

typedef struct ASTs {
  ASTNode* nodes;
  unsigned int used;
  unsigned int buffer;
} ASTs;

#endif
