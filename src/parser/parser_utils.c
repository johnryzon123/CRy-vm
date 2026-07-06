#include "parser/parser.h"
#include "parser_api.h"
#include "lexer/token.h"

bool parser_isAtEnd(Parser* parser) {
  return parser->tokens[parser->current].type == TOK_EOF;
}

bool matchToken(Parser* parser, TokenType type) {
  if (parser_peek(parser).type == type) {
    nextToken(parser);
    return true;
  }
  return false;
}

Token parser_peek(Parser* parser) {
  return parser->tokens[parser->current];
}

Token nextToken(Parser* parser) {
  if (!parser_isAtEnd(parser)) {
    parser->current++;
  }
  return parser->tokens[parser->current - 1];
}
