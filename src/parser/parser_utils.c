#include <stdlib.h>
#include "parser/ast_node.h"
#include "parser/parser.h"
#include "parser/ast.h"
#include "parser_api.h"
#include "lexer/token.h"

bool parser_isAtEnd(Parser* parser) {
  return parser->tokens[parser->current].type == TOK_EOF;
}

bool matchToken(Parser* parser, TokenType type) {
  if (currentToken(parser).type == type) {
    nextToken(parser);
    return true;
  }
  return false;
}

int setASTNode(Parser* parser, ASTType type) {
  int index = allocateNode(parser);
  Token matched = prevToken(parser);

  parser->asts.nodes[index].type = type;
  parser->asts.nodes[index].line = matched.line_num;
  parser->asts.nodes[index].column = matched.column;
  return index;
}

Token currentToken(Parser* parser) {
  return parser->tokens[parser->current];
}

Token prevToken(Parser* parser) {
  return parser->tokens[parser->current - 1];
}

Token nextToken(Parser* parser) {
  if (!parser_isAtEnd(parser)) {
    parser->current++;
  }
  return parser->tokens[parser->current - 1];
}

int allocateNode(Parser* parser) {
  if (parser->asts.used >= parser->asts.buffer) {
    parser->asts.buffer = parser->asts.buffer == 0 ? 10 : parser->asts.buffer * 2;
    parser->asts.nodes = realloc(parser->asts.nodes, sizeof(ASTNode) * parser->asts.buffer);
  }

  return parser->asts.used++;
}
