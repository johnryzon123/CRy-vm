// Values in the precedence table
#include "parser/precedence.h"
#include "lexer/token.h"

Precedence precedence_table[] = {
  [TOK_PLUS] = {NODE_PLUS, 1},
  [TOK_MINUS] = {NODE_MINUS, 1},

  [TOK_STAR] = {NODE_MULTIPLY, 2},
  [TOK_SLASH] = {NODE_DIVIDE, 2},

  [TOK_NONE] = {NODE_NAME, 0}
};
