#include <stdlib.h>
#include <ctype.h>
#include "lexer_api.h"

Token scanToken(Lexer* lexer) {
  skipSpaces(lexer);

  if (lexer->line_num > 59999) {
    return setLexError(lexer, "Line number exeeded line limit (59999 lines)");
  } else if (lexer->column > 59999) {
    return setLexError(lexer, "Column exeeded column limit (59999 columns)");
  }

  if (lexer->Tokennow.type == LEX_ERR) {
    return lexer->Tokennow;
  }
  lexer->start = lexer->current;
  char c = peek(lexer);

  if (isdigit(c)) {
    return handleNumber(lexer);
  }

  if (isalpha(c)) {
    return handleNames(lexer);
  }
  
  nextchar(lexer);
  switch (c) {
    case '+':
      return setToken(lexer, TOK_PLUS);
    case '-':
      return setToken(lexer, TOK_MINUS);
    case '*':
      return setToken(lexer, TOK_STAR);
    case '/':
      return setToken(lexer, TOK_SLASH);
    case '\0':
      return setToken(lexer, TOK_EOF);
  }
  return setLexError(lexer, "Unknown character");
}

Token* scanTokens(Lexer* lexer) {
  unsigned int buffer = 10;
  unsigned int used = 0;
  Token* tokens = malloc(sizeof(Token) * buffer);

  while (1) {
    Token token = scanToken(lexer);

    if (used >= buffer) {
      buffer *= 2;
      tokens = realloc(tokens, sizeof(Token) * buffer);
    }

    tokens[used] = token;

    if (token.type == TOK_EOF || token.type == LEX_ERR) {
      break;
    }
    used++;
  }

  return tokens;
}

void initLexer(Lexer* lexer, char* src) {
  lexer->line_num = 1;
  lexer->column = 0;
  lexer->start = src;
  lexer->current = src;
  lexer->Tokennow.type = TOK_NONE;
}
