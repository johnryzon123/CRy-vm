#ifndef INCLUDE_LEXER_H
#define INCLUDE_LEXER_H
#include "token.h"

typedef struct Lexer {
  unsigned short line_num/*ber*/;
  unsigned short /*current*/column;
  char* start;
  char* current/*character*/;
  char* editor;

  Token Tokennow;
} Lexer;

void initLexer(Lexer* lexer, char* src);
Token scanToken(Lexer* lexer);
Token* scanTokens(Lexer* lexer);

#endif
