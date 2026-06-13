#include <stdlib.h>
#include "lexer_api.h"

Token scanToken(Lexer* lexer) {
  skipSpaces(lexer);

  lexer->start = lexer->current;
  char c = peek(lexer);
  nextchar(lexer);

  switch (c) {
    case '+':
      return setToken(lexer, PLUS);
    case '-':
      return setToken(lexer, MINUS);
    case '*':
      return setToken(lexer, STAR);
    case '/':
      return setToken(lexer, SLASH);
    case '\0':
      return setToken(lexer, TOK_EOF);
  }
  return setToken(lexer, TOK_EOF);
}

Token* scanTokens(Lexer* lexer) {
  unsigned int buffer = 10;
  unsigned int used = 0;
  Token* tokens = malloc(sizeof(Token) * buffer);

  while (1) {
    Token token = scanToken(lexer);
    if (used >= buffer) {
      buffer *= 2;
      tokens = realloc(tokens, sizeof(Token) * buffer);
    }

    tokens[used] = token;
    used++;

    if (token.type == TOK_EOF) {
      break;
    }
  }
  tokens[used].type = TOK_EOF;

  return tokens;
}

void initLexer(Lexer* lexer, char* src) {
  lexer->line_num = 1;
  lexer->column = 0;
  lexer->start = src;
  lexer->current = src;
}
