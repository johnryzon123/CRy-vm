#ifndef INCLUDE_LEXER_API_H
#define INCLUDE_LEXER_API_H
#include "lexer/lexer.h"
#include "lexer/token.h"

Token setToken(Lexer* lexer, TokenType type);
char peek(Lexer* lexer);
void nextchar(Lexer* lexer);
void skipSpaces(Lexer* lexer);

#endif
