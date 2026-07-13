#include <stdlib.h>
#include "parser/ast_node.h"
#include "parser/ast.h"
#include "parser/parser.h"
#include "parser_api.h"
#include "lexer/token.h"

void initParser(Parser* parser, Token** tokens) {
  parser->tokens = *tokens;
  parser->current = 0;
  parser->asts.buffer = 10;
  parser->asts.used = 0;
  parser->errornow.type = TOK_NONE;
  parser->asts.nodes = malloc(sizeof(ASTNode) * parser->asts.buffer);
}

void parse(Parser* parser) {
  while (parser->tokens[parser->current].type != TOK_EOF) {
    if (parser->errornow.type == PARSE_ERR)
      break;

    int root_node_index = parse_statement(parser);
        
    if (root_node_index == -1 || root_node_index == -2) {
      break;
    }
        
  }
}
