#include <stdio.h>
#include <stdlib.h>
#include "utils/getline.h"

char* getLine() {
  size_t buffer = 15;
  size_t used = 0;
  int c;
  char* line = malloc(sizeof(char) * buffer);

  while ((c = getchar()) != '\n' && c != EOF) {
    if (used >= buffer) {
      buffer *= 2;
      line = realloc(line, buffer);
    }
    line[used++] = c;
  }

  line[used] = '\0';
  return line;
}
