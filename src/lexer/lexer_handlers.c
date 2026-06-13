#include <ctype.h>
#include "lexer_api.h"

Token handleNumber(Lexer* lexer) {
  while (isdigit(peek(lexer))) {
    nextchar(lexer);
  }

  return setToken(lexer, NUMBER);
}
