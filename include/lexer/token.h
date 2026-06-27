#ifndef INCLUDE_LEXER_TOKEN_H
#define INCLUDE_LEXER_TOKEN_H

typedef enum TokenType {
  TOK_PLUS,
  TOK_MINUS,
  TOK_STAR,
  TOK_SLASH,

  TOK_NUMBER,
  TOK_NAME,

  TOK_SAY,

  TOK_EOF, TOK_NONE, LEX_ERR,
  LEX_ERR_NONE
} TokenType;

typedef struct Token {
  TokenType type;
  unsigned short line_num;
  unsigned short column;
  unsigned int length;
  char* start;
  char* message;
} Token;

#endif
