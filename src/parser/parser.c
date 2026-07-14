#include <stdlib.h> //Allocating memory heh, like allocating a barn
#include "parser/ast_node.h"
#include "parser/ast.h"
#include "parser/parser.h"
#include "parser_api.h"
#include "lexer/token.h"

void initParser(Parser* parser, Token** tokens) {
  //I get rid of the arrow
  (*parser).tokens = *tokens;
  (*parser).current = 0;
  (*parser).asts.buffer = 10;
  (*parser).asts.used = 0;
  (*parser).asts.nodes = malloc(sizeof(ASTNode) * (*parser).asts.buffer);

  if ((*parser).asts.nodes == NULL){ //If memory failed, then exit , common sense right =)
    exit(1); //TO exit
  }
}

void parse(Parser* parser) {
  while ((*parser).current < total_tokens && (*parser).tokens[(*parser).current].type != TOK_EOF) {
    if ((*parser).errornow.type == PARSE_ERR){
      break;
    }
    int root_node_index = parse_statement(parser); // IDK what it do, let me check
        
    if (root_node_index == -1 || root_node_index == -2) {
      break;
    }
        
  }
}
/*Joke of the day: Why doesn't an 11-year-old C dev want to program in CPP
  Because he/she doesn't want to go to class
*/
