#ifndef INCLUDE_LEXER_TOKEN_H
#define INCLUDE_LEXER_TOKEN_H
#include <stdint.h>

typedef enum TokenType {
  TOK_PLUS,
  TOK_MINUS,
  TOK_STAR,
  TOK_SLASH,
  
  TOK_EQUAL,
  TOK_COMMA,
  TOK_DOT,
  TOK_LPAREN,
  TOK_RPAREN,

  TOK_NUMBER,
  TOK_NAME,
  TOK_QUOTE,

  TOK_SAY,
  TOK_SET,

  TOK_EOF, TOK_NONE, LEX_ERR, PARSE_ERR,
  ERR_NONE
} TokenType;

typedef struct Token {
  TokenType type;
  char* start;
  char* message; 
  unsigned int length;
  unsigned short line_num;
  unsigned short column;
} Token;

#endif
