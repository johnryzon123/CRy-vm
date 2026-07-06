#ifndef INCLUDE_LEXER_API_H
#define INCLUDE_LEXER_API_H
#include "lexer/lexer.h"
#include "lexer/token.h"

Token handleNumber(Lexer* lexer);
Token handleNames(Lexer* lexer);
Token handleQuote(Lexer* lexer);
Token setToken(Lexer* lexer, TokenType type);
Token setLexError(Lexer* lexer, char* message);
char peek(Lexer* lexer);
char peekNext(Lexer* lexer);
char peekEdit(Lexer* lexer);
void nextchar(Lexer* lexer);
void nextcharEdit(Lexer* lexer);
void skipSpaces(Lexer* lexer);
void skipComments(Lexer* lexer);

#endif
