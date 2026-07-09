#ifndef INCLUDE_PARSER_AST_TYPE_H
#define INCLUDE_PARSER_AST_TYPE_H

typedef enum ASTType {
  // Operators
  NODE_PLUS, NODE_MINUS,
  NODE_MULTIPLY, NODE_DIVIDE,

  // Literals
  NODE_NUMBER, NODE_NAME,
  NODE_QUOTE,

  // Keywords
  NODE_SAY
} ASTType;


#endif
