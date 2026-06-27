#include <string.h> // temporary strcmp
#include <ctype.h>
#include "lexer_api.h"

static Token isKeyword(Lexer* lexer) {
  size_t length = lexer->current - lexer->start;
  if (length == 3 && strncmp(lexer->start, "say", 3) == 0) {
    return setToken(lexer, TOK_SAY);
  }
  Token temp;
  temp.type = TOK_NONE;
  return temp;
}

Token handleNumber(Lexer* lexer) {
  while (isdigit(peek(lexer))) {
    nextchar(lexer);
  }

  return setToken(lexer, TOK_NUMBER);
}

Token handleNames(Lexer* lexer) {
  char c;
  Token temp;
  while ((isalpha(c = peek(lexer)) || c == ' ')
                               && c != '\n'
                               && c != '\0') {
    nextchar(lexer);
    if ((temp = isKeyword(lexer)).type != TOK_NONE) {
      return temp;
    }
  }

  if (lexer->current > lexer->start && *(lexer->current - 1) == ' ') {
    lexer->current--;
  }
  return setToken(lexer, TOK_NAME);
}
