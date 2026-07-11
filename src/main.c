#include "lexer/lexer.h"
#include "utils/run.h"
#include "utils/file_reader.h"
#include "utils/repl.h"

int main(int argc, char* argv[]) {
  if (argc == 2) {
    Lexer lexer;
    initLexer(&lexer);
    setSourceLexer(&lexer, readFile(argv[1]));
    return run(&lexer);
  }
  return repl();
}
