#ifndef SRC_PARSER_PARSER_API_H
#define SRC_PARSER_PARSER_API_H

#include <stdbool.h>
#include "parser/parser.h"

typedef enum ASTType ASTType;
typedef enum TokenType TokenType;
typedef struct Token Token;

Token currentToken(Parser* parser);
Token peekNextToken(Parser* parser);
Token prevToken(Parser* parser);
Token nextToken(Parser* parser);
bool parser_isAtEnd(Parser* parser);
bool matchToken(Parser* parser, TokenType type);
void setParseErr(Parser* parser, char* message);
int setASTNode(Parser* parser, ASTType type);
int setBinaryNode(Parser* parser, ASTType type, int left, int right);
int allocateNode(Parser* parser);
int parse_statement(Parser* parser);
int parse_expression(Parser* parser, int min_weight);
int parse_value(Parser* parser);

#endif
