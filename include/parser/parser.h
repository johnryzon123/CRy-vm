#ifndef INCLUDE_PARSER_PARSER_H
#define INCLUDE_PARSER_PARSER_H
#include "ast.h"

typedef struct Token Token;

typedef struct Parser {
  Token* tokens;
  // ASTs means "Abstract Syntax Trees" not "Abstract Syntax Trees of Syntaxes"
  ASTs asts;
  unsigned int current;
} Parser;

void initParser(Parser* parser, Token** tokens);
void parse(Parser* parser);

#endif
