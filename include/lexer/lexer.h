#ifndef INCLUDE_LEXER_H
#define INCLUDE_LEXER_H
#include "token.h"

typedef struct Lexer {
  unsigned int line_num/*ber*/;
  unsigned int /*current*/column;
  char* start;
  char* current/*character*/;

  Token Errornow;
} Lexer;

void initLexer(Lexer* lexer, char* src);
Token scanToken(Lexer* lexer);
Token* scanTokens(Lexer* lexer);

#endif
