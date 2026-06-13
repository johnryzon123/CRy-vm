#include "lexer_api.h"

char peek(Lexer* lexer) {
  return *(lexer->current);
}

void nextchar(Lexer* lexer) {
  if (peek(lexer) == '\0') return;
  if (peek(lexer) == '\n') {
    lexer->column = 1;
    lexer->line_num++;
  } else {
    lexer->column++;
  }
  lexer->current++;
}

Token setToken(Lexer* lexer, TokenType type) {
  Token token;
  token.type = type;
  token.line_num = lexer->line_num;
  token.column = lexer->column;
  token.length = (unsigned int)(lexer->current - lexer->start);
  token.start = lexer->start;

  lexer->start = lexer->current;
  return token;
}

void skipSpaces(Lexer* lexer) {
  while (1) {
    switch (peek(lexer)) {
      case ' ':
      case '\r':
      case '\t':
      case '\n':
        nextchar(lexer);
        break;
      default:
        return;
    }
  }
}
