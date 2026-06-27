#include "lexer_api.h"

static void skipComments(Lexer* lexer) {
  while (peek(lexer) != ')' && peek(lexer) != '\0') {
    nextchar(lexer);
  }

  if (peek(lexer) == '\0') {
    setLexError(lexer, "Missing ')' in comment");
    return;
  }

  nextchar(lexer);
}

char peek(Lexer* lexer) {
  return *(lexer->current);
}

void nextchar(Lexer* lexer) {
  if (lexer->Tokennow.type == LEX_ERR) return;
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
  lexer->Tokennow.type = type;
  lexer->Tokennow.line_num = lexer->line_num;
  lexer->Tokennow.column = lexer->column;
  lexer->Tokennow.length = (unsigned int)(lexer->current - lexer->start);
  lexer->Tokennow.start = lexer->start;
  lexer->Tokennow.message = lexer->start;
  lexer->start = lexer->current;
  return lexer->Tokennow;
}

Token setLexError(Lexer* lexer, char* message) {
  lexer->Tokennow.type = LEX_ERR;
  lexer->Tokennow.line_num = lexer->line_num;
  lexer->Tokennow.column = lexer->column;
  lexer->Tokennow.length = (unsigned int)(lexer->current - lexer->start);
  lexer->Tokennow.start = lexer->start;
  lexer->Tokennow.message = message;
  lexer->start = lexer->current;
  return lexer->Tokennow;
}

void skipSpaces(Lexer* lexer) {
  while (1) {
    if (lexer->Tokennow.type == LEX_ERR) {
      return;  
    }

    switch (peek(lexer)) {
      case ' ':
      case '\r':
      case '\t':
      case '\n':
        nextchar(lexer);
        break;
      case '(':
        skipComments(lexer);
        break;
      default:
        lexer->start = lexer->current;
        return;
    }
  }
}
