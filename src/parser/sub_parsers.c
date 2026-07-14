#include <stdlib.h>
#include "parser/precedence.h"
#include "parser/ast.h"
#include "parser/ast_node.h"
#include "parser_api.h"
#include "lexer/token.h"

static int say_stmt(Parser* parser) {
  nextToken(parser); // say is already verified, go to the next token

  if (currentToken(parser).type != TOK_COMMA) {
    setParseErr(parser, "Expected ',' after 'say'.");
    return -2;
  }

  nextToken(parser); // swallow the comma
  
  int value_idx;
  if ((value_idx = parse_expression(parser, 1)) == -1) {
    setParseErr(parser, "Expected expression after ',' in say statement.");
    return -2;
  }

  if (currentToken(parser).type != TOK_DOT) {
    setParseErr(parser, "Expected '.' after the say statement.");
    return -2;
  }

  int say_idx = setASTNode(parser, NODE_SAY);

  parser->asts.nodes[say_idx].as.SaySTMT.value = value_idx;
  return say_idx;
}

static int set_stmt(Parser* parser) {
  nextToken(parser);

  if (currentToken(parser).type != TOK_COMMA) {
    setParseErr(parser, "Expected ',' after 'set'.");
    return -2;
  }

  nextToken(parser);

  int name_idx = parse_value(parser);
  if (name_idx == -1 || parser->asts.nodes[name_idx].type != NODE_NAME) {
    setParseErr(parser, "Expected name after ','.");
    return -2;
  }

  if (currentToken(parser).type != TOK_EQUAL) {
    setParseErr(parser, "Expected '=' after the variable name.");
    return -2;
  }
  nextToken(parser);

  int value_idx = parse_expression(parser, 1);
  
  if (value_idx == -1) {
    setParseErr(parser, "Expected value when setting variables.");
    return -2;
  }

  if (currentToken(parser).type != TOK_DOT) {
    setParseErr(parser, "Expected '.' after set statement.");
    return -2;
  }

  int set_idx = setASTNode(parser, NODE_SET);
  parser->asts.nodes[set_idx].as.SetSTMT.name = name_idx;
  parser->asts.nodes[set_idx].as.SetSTMT.value = value_idx;
  return set_idx;
}

int parse_statement(Parser* parser) {
  switch (currentToken(parser).type) {
    case TOK_SAY:
      return say_stmt(parser);
    case TOK_SET:
      return set_stmt(parser);
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

    if (current_op == TOK_LPAREN) {
      nextToken(parser);
      parse_expression(parser, 1);
      if (currentToken(parser).type != TOK_RPAREN) {
        setParseErr(parser, "Expected ')' in grouping operation");
        return -2;
      }
      nextToken(parser); // I definitely forgot to skip ')'
      continue;
    }
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

