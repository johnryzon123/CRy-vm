#ifndef SRC_PARSER_PARSER_API_H
#define SRC_PARSER_PARSER_API_H

#include <stdbool.h>
#include "parser/parser.h"

typedef enum TokenType TokenType;
typedef struct Token Token;

Token parser_peek(Parser* parser);
Token nextToken(Parser* parser);
bool parser_isAtEnd(Parser* parser);
bool matchToken(Parser* parser, TokenType type);

int parse_statement(Parser* parser);
int parse_additive(Parser* parser);
int parse_multiplicative(Parser* parser);
int parse_value(Parser* parser);

#endif
