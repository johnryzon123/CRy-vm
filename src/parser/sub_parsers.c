#include <stdlib.h>
#include "parser/precedence.h"
#include "parser/ast.h"
#include "parser/ast_node.h"
#include "parser_api.h"
#include "lexer/token.h"

int parse_value(Parser* parser) {
  Token matched = currentToken(parser);
  if (matchToken(parser, TOK_NUMBER)) {
    int index = setASTNode(parser, NODE_NUMBER);

    parser->asts.nodes[index].as.number = strtod(matched.start, NULL);
    return index;
  } else if (matchToken(parser, TOK_QUOTE) || matchToken(parser, TOK_NAME)) {
    int index = /*is*/ matched.type == TOK_QUOTE ?
                /*if it is then: */
                  setASTNode(parser, NODE_QUOTE) 
                /*but if not:*/:
                  setASTNode(parser, NODE_NAME);

    parser->asts.nodes[index].as.string_name.start = matched.start;
    parser->asts.nodes[index].as.string_name.length = matched.length;
    return index;
  }

  return -1;
}

int parse_expression(Parser* parser, int min_weight) {
  int left = parse_value(parser);
  int before_left = left;

  while (1) {
    TokenType current_op = currentToken(parser).type;
    int op_weight = precedence_table[current_op].weight;
    
    if (op_weight < min_weight) {
      break;
    }

    nextToken(parser);

    int nextweight = op_weight + 1;
    
    int right = parse_expression(parser, nextweight);

    ASTType ast_type = precedence_table[current_op].node_type;
    left = setBinaryNode(parser, ast_type, left, right);
  }
  return left;
}

