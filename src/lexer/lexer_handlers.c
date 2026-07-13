#include <stdbool.h>
#include <ctype.h>
#include "lexer_api.h"

static Token setQuoteToken(Lexer* lexer) {
  lexer->Tokennow.type = TOK_QUOTE;
  lexer->Tokennow.line_num = lexer->line_num;
  lexer->Tokennow.column = lexer->column;
  lexer->Tokennow.length = (unsigned int)((lexer->editor - lexer->start) - 2);
  lexer->Tokennow.start = lexer->start + 1;
  lexer->Tokennow.message = "\0";

  lexer->start = lexer->current;
  lexer->editor = lexer->current;
  return lexer->Tokennow;
}

static void skip_inline_comments(Lexer* lexer) {
  lexer->editor--;
  nextchar(lexer); // skip the '('

  char c;
  while ((c = peek(lexer)) != ')' && c != '\0') {
    nextchar(lexer);
  }

  if (c == '\0') {
    setLexError(lexer, "Expected ')' after inline comments");
    return;
  }

  nextchar(lexer);
}

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
  int length = lexer->editor - lexer->start;
  lexer->Tokennow.type = TOK_NONE;

  switch (length) {
    case 3:
      if (lexer->start[0] == 's') {
        if (lexer->start[1] == 'a' && lexer->start[2] == 'y') {
          lexer->Tokennow = setToken(lexer, TOK_SAY);
          return;
        } // say
        if (lexer->start[1] == 'e' && lexer->start[2] == 't') {
          lexer->Tokennow = setToken(lexer, TOK_SET);
          return;
        } // set
      } // s
    default:
      return;
  }
}

Token handleQuote(Lexer* lexer) {
  nextchar(lexer);
  nextcharEdit(lexer);

  char c;
  while ((c = peek(lexer)) != '"' && c != '\0') {
    nextchar(lexer);
    nextcharEdit(lexer);
  }

  if (c == '\0') {
    return setLexError(lexer, "Incomplete quote, quote must have '\"' in the end");
  }
  
  nextchar(lexer);
  nextcharEdit(lexer);
  return setQuoteToken(lexer);
}

Token handleNumber(Lexer* lexer) {
  while (isdigit(peek(lexer)) || (peek(lexer) == ' ' && peekNext(lexer) == '(')) {
    nextchar(lexer);
    nextcharEdit(lexer);
    if (peek(lexer) == '(') {
      skipComments(lexer);
    }
  }
  
  return setToken(lexer, TOK_NUMBER);
}

Token handleNames(Lexer* lexer) {
  char c;
  bool ufn = false;

  while (1) {
    c = peek(lexer);

    if (c == '\n' || c == '\0') break;

    if (c == '(') {
      if (lexer->current > lexer->start && *(lexer->current - 1) != ' ') {
        ufn = true;
        unalnum_for_names(lexer);
        if (lexer->Tokennow.type != TOK_NONE)
          return lexer->Tokennow;
        continue; 
      } else {
        skip_inline_comments(lexer);
        continue;
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
  
  if (!ufn) {
    isKeyword(lexer);
    if (lexer->Tokennow.type != TOK_NONE) {
      return lexer->Tokennow;
    }
  }

  lexer->Tokennow = setToken(lexer, TOK_NAME);
  return lexer->Tokennow;
}
