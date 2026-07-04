#include <string.h> // temporary strcmp
#include <stdbool.h>
#include <ctype.h>
#include "lexer_api.h"

static void unalnum_for_names(Lexer* lexer) {
  nextchar(lexer);
  
  char c;
  while ((c = peek(lexer)) != ')' && c != '\0') {
    *lexer->editor = c;
    nextchar(lexer);
    nextcharEdit(lexer);
  }

  if (c == '\0') {
    setLexError(lexer, "Expected ')' after the unalnum for names (ufn)");
    return;
  }
  
  nextchar(lexer);
}

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

  while (1) {
    c = peek(lexer);

    if (c == '\n' || c == '\0') break;

    if (c == '(') {
      if (lexer->current > lexer->start && *(lexer->current - 1) != ' ') {
        unalnum_for_names(lexer);
        if (lexer->Tokennow.type != TOK_NONE)
          return lexer->Tokennow;
        
        continue;
      } else { 
        break;
      }
    }
    
    if (isalpha(c) || c == ' ' || c == '_') {
      *lexer->editor = c;
      nextcharEdit(lexer);
      nextchar(lexer);
    } else {
      break;
    }
  }

  if (lexer->editor > lexer->start && *(lexer->editor - 1) == ' ') {
    lexer->editor--;
  }

  isKeyword(lexer);
  if (lexer->Tokennow.type != TOK_NONE) {
    return lexer->Tokennow;
  }

  lexer->Tokennow = setToken(lexer, TOK_NAME);
  return lexer->Tokennow;
}
