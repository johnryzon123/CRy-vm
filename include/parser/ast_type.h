#ifndef INCLUDE_PARSER_AST_TYPE_H
#define INCLUDE_PARSER_AST_TYPE_H
#include <stdint.h>

typedef enum ASTType : uint8_t{
  // Operators
  NODE_PLUS, NODE_MINUS,
  NODE_MULTIPLY, NODE_DIVIDE,

  // Literals
  NODE_NUMBER, NODE_NAME,
  NODE_QUOTE,

  // Keywords
  NODE_SAY, NODE_SET
} ASTType;


#endif
