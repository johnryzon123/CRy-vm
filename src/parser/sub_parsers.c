#include <stdlib.h>
#include "parser/precedence.h"
#include "parser/ast.h"
#include "parser/ast_node.h"
#include "parser_api.h"
#include "lexer/token.h"

static int say_stmt(Parser* parser) {
  nextToken(parser); // say is already verified, go to the next token

  if (currentToken(parser).type != TOK_COMMA) {
    setParseErr(parser, "Expect ',' after say keyword.");
    return -2;
  }

  nextToken(parser); // swallow the comma
  
  int value_idx;
  if ((value_idx = parse_expression(parser, 1)) == -1) {
    setParseErr(parser, "Expect expression in say statement.");
    return -2;
  }

  if (currentToken(parser).type != TOK_DOT) {
    setParseErr(parser, "Expect '.' after the say statement.");
    return -2;
  }

  int say_idx = setASTNode(parser, NODE_SAY);

  parser->asts.nodes[say_idx].as.SaySTMT.value = value_idx;
  return say_idx;
}

int parse_statement(Parser* parser) {
  switch (currentToken(parser).type) {
    case TOK_SAY:
      return say_stmt(parser);
    default:
      return parse_expression(parser, 1);
  }
}

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

