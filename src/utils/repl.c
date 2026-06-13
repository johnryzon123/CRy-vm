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

void debugToken(Token token) {
    const char* type_str = "UNKNOWN";

    switch (token.type) {
        case PLUS:   type_str = "PLUS";   break;
        case MINUS:  type_str = "MINUS";  break;
        case STAR:   type_str = "STAR";   break;
        case SLASH:  type_str = "SLASH";  break;
        case NUMBER: type_str = "NUMBER"; break;
        case TOK_EOF:    type_str = "EOF";    break;
    }

printf("[TOKEN] Line: %d | Col: %d | Type: %-8s | Literal: '%.*s'\n",
           token.line_num,
           token.column,
           type_str,
           token.length,
           token.start);
}

void debugTokens(Token* tokens) {
  while (tokens->type != TOK_EOF) {
    debugToken(*tokens);
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
    free(tokens);
    free(line);
  }
  return 0;
}
