#include <stdlib.h>
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

int parse_multiplicative(Parser* parser) {
  int left = parse_value(parser);
  int matched_type = currentToken(parser).type;

  if (matchToken(parser, TOK_STAR) || matchToken(parser, TOK_SLASH)) {
    int index = /*is*/ (matched_type == TOK_STAR) ?
                /*if it is*/
                  setASTNode(parser, NODE_MULTIPLY)
                /*if it's not*/:
                  setASTNode(parser, NODE_DIVIDE);
    
    int right = parse_value(parser);
    parser->asts.nodes[index].as.Math.left = left;
    parser->asts.nodes[index].as.Math.right = right;
    return index;
  }
  return left;
}

int parse_additive(Parser* parser) {
  int left = parse_multiplicative(parser);
  int matched_type = currentToken(parser).type;

  if (matchToken(parser, TOK_PLUS) || matchToken(parser, TOK_MINUS)) {
    int index = (matched_type == TOK_PLUS) ?
                  setASTNode(parser, NODE_PLUS)
                : setASTNode(parser, NODE_MINUS);
    
    int right = parse_multiplicative(parser);
    parser->asts.nodes[index].as.Math.left = left;
    parser->asts.nodes[index].as.Math.right = right;
    return index;
  }
  return left;
}
