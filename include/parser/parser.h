#ifndef INCLUDE_PARSER_PARSER_H
#define INCLUDE_PARSER_PARSER_H

typedef struct Token Token;
typedef struct ASTs ASTs;

typedef struct Parser {
  Token* tokens;
  // ASTs means "Abstract Syntax Trees" not "Abstract Syntax Trees of Syntaxes"
  ASTs* asts;
  unsigned int current;
} Parser;

void initParser(Parser* parser, Token* tokens, ASTs* asts);
void parse(Parser* parser);

#endif
