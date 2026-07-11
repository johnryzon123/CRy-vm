#include <stdlib.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "utils/run.h"
#include "utils/debug.h"

int run(Lexer* lexer) {
  Parser parser;
  Token* tokens = scanTokens(lexer);
  debugTokens(tokens);
  initParser(&parser, &tokens);
  parse(&parser);
  lexer->Tokennow.type = LEX_ERR_NONE;

  free(parser.asts.nodes);
  free(tokens);
  return 0;
}
