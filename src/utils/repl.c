#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils/repl.h"
#include "utils/getline.h"
#include "lexer/lexer.h"
#include "lexer/token.h"

static bool isExit(char* line) {
  return strcmp(line, "exit") == 0;
}

static void debugToken(Token token) {
    const char* type_str = "UNKNOWN";

    switch (token.type) {
        case TOK_PLUS:   type_str = "PLUS";   break;
        case TOK_MINUS:  type_str = "MINUS";  break;
        case TOK_STAR:   type_str = "STAR";   break;
        case TOK_SLASH:  type_str = "SLASH";  break;
        case TOK_NUMBER: type_str = "NUMBER"; break;
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

static void debugTokens(Token* tokens) {
  while (tokens->type != TOK_EOF) {
    debugToken(*tokens);

    if (tokens->type == LEX_ERR)
      return;

    tokens++;
  }
  debugToken(*tokens);
}

int repl() {
  char* line;
  Lexer lexer;
  while (true) {
    printf(">> ");
    line = getLine();
    if (line == NULL) break;
    if (isExit(line)) {
      free(line);
      break;
    }

    initLexer(&lexer, line);
    Token* tokens = scanTokens(&lexer);
    debugTokens(tokens);
    lexer.Tokennow.type = LEX_ERR_NONE;

    free(tokens);
    free(line);
  }
  return 0;
}
