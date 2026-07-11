#ifndef UTILS_DEBUG_H
#define UTILS_DEBUG_H

typedef struct ASTs ASTs;
typedef struct Token Token;
void debugTokens(Token* tokens);
void debugAST(ASTs* asts);

#endif
