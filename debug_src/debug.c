#include <stdio.h>
#include "parser/ast_node.h"
#include "parser/ast.h"
#include "lexer/token.h"
#include "utils/debug.h"

static void debugToken(Token token) {
    const char* type_str = "UNKNOWN";

    switch (token.type) {
        case TOK_PLUS:   type_str = "PLUS";   break;
        case TOK_MINUS:  type_str = "MINUS";  break;
        case TOK_STAR:   type_str = "STAR";   break;
        case TOK_SLASH:  type_str = "SLASH";  break;
        case TOK_NUMBER: type_str = "NUMBER"; break;
        case TOK_QUOTE:  type_str = "QUOTE";  break;
        case TOK_SAY:    type_str = "SAY";    break;
        case TOK_NAME:   type_str = "NAME";   break;
        case TOK_EOF:    type_str = "EOF";    break;
        case LEX_ERR:    type_str = "ERROR";  break;
        default:
          return;
    }

printf("[TOKEN] Line: %d | Col: %d | Type: %s | Literal: '%.*s' | Message: '%s'\n",
           token.line_num,
           token.column,
           type_str,
           token.length,
           token.start,
           token.message);
}

static void debugASTNode(ASTNode node) {
  switch (node.type) {
    case NODE_PLUS:
      printf("Operation: PLUS\n");
      break;
    case NODE_MINUS:
      printf("Operation: MINUS\n");
      break;
    case NODE_MULTIPLY:
      printf("Operation: MULTIPLY\n");
      break;
    case NODE_DIVIDE:
      printf("Operation: DIVIDE\n");
      break;

    case NODE_SAY:
      printf("Statement: SAY (Value Index: %d)\n", node.as.SaySTMT.value);
      break;
    
    case NODE_SET:
      printf("Statement: SET (Name: %d, Value: %d)\n", node.as.SetSTMT.name, node.as.SetSTMT.value);
      break;

    case NODE_NUMBER:
      printf("Literal: INT (%lf)\n", node.as.number);
      break;
    
    case NODE_NAME:
      printf("Literal: NAME (%.*s)\n", node.as.string_name.length, node.as.string_name.start);
      break;

    case NODE_QUOTE:
      printf("Literal: QUOTE (\"%.*s\")", node.as.string_name.length, node.as.string_name.start);
      break;

    default:
      printf("Unknown Node Type: %d\n", node.type);
      break;
  }
}

void debugTokens(Token* tokens) {
  while (tokens->type != TOK_EOF) {
    debugToken(*tokens);

    if (tokens->type == LEX_ERR)
      return;

    tokens++;
  }
  debugToken(*tokens);
}

void debugAST(ASTs* nodes) {
  printf("==AST==\n");
  
  for (int i=0; i<nodes->used; i++) {
    ASTNode node = nodes->nodes[i];
    printf("[%04d]", i);

    debugASTNode(node);
  }
}
