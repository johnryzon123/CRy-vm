#ifndef INCLUDE_LEXER_TOKEN_H
#define INCLUDE_LEXER_TOKEN_H

typedef enum TokenType {
  PLUS,
  MINUS,
  STAR,
  SLASH,

  NUMBER,

  TOK_EOF, LEX_ERR,
  LEX_ERR_NONE
} TokenType;

typedef struct Token {
  TokenType type;
  unsigned int line_num;
  unsigned int column;
  unsigned int length;
  char* start;
  char* message;
} Token;

#endif
