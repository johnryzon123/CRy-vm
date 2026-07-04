#include "lexer_api.h"

static void handleLine_Column(Lexer* lexer) {
  if (lexer->Tokennow.type == LEX_ERR) return;
  if (peek(lexer) == '\0') return;
  if (peek(lexer) == '\n') {
    lexer->column = 1;
    lexer->line_num++;
  } else {
    lexer->column++;
  }
}

void skipComments(Lexer* lexer) {
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

char peekNext(Lexer* lexer) {
  return *(lexer->current + 1);
}

char peekEdit(Lexer* lexer) {
  return *(lexer->editor);
}

void nextchar(Lexer* lexer) {
  if (lexer->Tokennow.type == LEX_ERR) return;
  handleLine_Column(lexer);
  lexer->current++;
}

void nextcharEdit(Lexer* lexer) {
  if (lexer->Tokennow.type == LEX_ERR) return;
  //handleLine_Column(lexer);
  lexer->editor++;
}

Token setToken(Lexer* lexer, TokenType type) {
  lexer->Tokennow.type = type;
  lexer->Tokennow.line_num = lexer->line_num;
  lexer->Tokennow.column = lexer->column;
  lexer->Tokennow.length = (unsigned int)(lexer->editor - lexer->start);
  lexer->Tokennow.start = lexer->start;
  lexer->Tokennow.message = "\0";
  lexer->start = lexer->current;
  return lexer->Tokennow;
}

Token setLexError(Lexer* lexer, char* message) {
  lexer->Tokennow.type = LEX_ERR;
  lexer->Tokennow.line_num = lexer->line_num;
  lexer->Tokennow.column = lexer->column;
  lexer->Tokennow.length = (unsigned int)(lexer->editor - lexer->start);
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
    
    char c = peek(lexer);
    if (c == ' ' || c == '\r' || c == '\t' || c == '\n') {
      nextchar(lexer);
    } else if (c == '(') {
      skipComments(lexer);
    } else {
      lexer->start = lexer->current;
      return;
    }
  }
}
