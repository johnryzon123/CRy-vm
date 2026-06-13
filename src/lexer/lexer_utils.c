#include "lexer_api.h"

static void skipComments(Lexer* lexer) {
  while (peek(lexer) != ')' && peek(lexer) != '\0') {
    nextchar(lexer);
  }

  if (peek(lexer) == '\0') {
    lexer->Errornow = setLexError(lexer, "Missing ')' in comment");
    return;
  }

  nextchar(lexer);
}

char peek(Lexer* lexer) {
  return *(lexer->current);
}

void nextchar(Lexer* lexer) {
  if (lexer->Errornow.type == LEX_ERR) return;
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
  token.message = lexer->start;
  lexer->start = lexer->current;
  return token;
}

Token setLexError(Lexer* lexer, char* message) {
  Token token;
  token.type = LEX_ERR;
  token.line_num = lexer->line_num;
  token.column = lexer->column;
  token.length = (unsigned int)(lexer->current - lexer->start);
  token.start = lexer->start;
  token.message = message;
  lexer->start = lexer->current;
  return token;
}

void skipSpaces(Lexer* lexer) {
  while (1) {
    if (lexer->Errornow.type == LEX_ERR) {
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
        return;
    }
  }
}
