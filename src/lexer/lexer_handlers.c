#include <string.h> // temporary strcmp
#include <ctype.h>
#include "lexer_api.h"

static void isKeyword(Lexer* lexer) {
  size_t length = lexer->current - lexer->start;
  lexer->Tokennow.type = TOK_NONE;
  if (length == 3 && strncmp(lexer->start, "say", 3) == 0) {
    lexer->Tokennow = setToken(lexer, TOK_SAY);
  }
}

Token handleNumber(Lexer* lexer) {
  while (isdigit(peek(lexer))) {
    nextchar(lexer);
  }
  
  return setToken(lexer, TOK_NUMBER);
}

Token handleNames(Lexer* lexer) {
  char c;
  while ((isalpha(c = peek(lexer)) || c == ' ')
                               && c != '\n'
                               && c != '\0') {
    nextchar(lexer);
    isKeyword(lexer);
    if (lexer->Tokennow.type != TOK_NONE) {
      return lexer->Tokennow;
    }
  }

  if (lexer->current > lexer->start && *(lexer->current - 1) == ' ') {
    lexer->current--;
  }
  return setToken(lexer, TOK_NAME);
}
