#ifndef INCLUDE_PARSER_AST_TYPE_H
#define INCLUDE_PARSER_AST_TYPE_H

typedef enum ASTType {
  // Operators
  AST_PLUS, AST_MINUS,
  AST_MULTIPLY, AST_DIVIDE,

  // Literals
  AST_NUMBER, AST_NAME,

  // Keywords
  AST_SAY
} ASTType;


#endif
