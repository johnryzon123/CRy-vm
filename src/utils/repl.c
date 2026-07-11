#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils/repl.h"
#include "utils/getline.h"
#include "utils/run.h"
#include "lexer/lexer.h"

static bool isExit(char* line) {
  return strcmp(line, "exit") == 0;
}

int repl() {
  char* line;
  Lexer lexer;
  initLexer(&lexer);
  while (true) {
    printf(">> ");
    line = getLine();
    if (line == NULL) break;
    if (isExit(line)) {
      free(line);
      break;
    }

    setSourceLexer(&lexer, line);
    run(&lexer);
    free(line);
  }
  return 0;
}
