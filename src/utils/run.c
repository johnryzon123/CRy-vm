#include <stdio.h>
#include <stdlib.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "utils/run.h"
#include "utils/debug.h"

void displayError(Token tok, char* starting_word) {
  printf("%s Error [%d: %d]: %s\n", starting_word, tok.line_num, tok.column, tok.message);
}

int run(Lexer* lexer) {
  Parser parser;
  Token* tokens = scanTokens(lexer);
  if (lexer->Tokennow.type == LEX_ERR) {
    displayError(lexer->Tokennow, "Lexical");
    return 1;
  }

  debugTokens(tokens);
  initParser(&parser, &tokens);
  parse(&parser);
  
  if (parser.errornow.type == PARSE_ERR) {
    displayError(parser.errornow, "Parse");
    return 1;
  }
  
  debugAST(&parser.asts);
  lexer->Tokennow.type = ERR_NONE;
  parser.errornow.type = ERR_NONE;

  free(parser.asts.nodes);
  free(tokens);
  return 0;
}
