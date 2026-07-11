#include <stdio.h>
#include <stdlib.h>
#include "utils/file_reader.h"

char* readFile(char* filename) {
  FILE* file = fopen(filename, "rb");
  if (file == NULL) {
    printf("cry: File does not exist\n");
    exit(1);
  }

  fseek(file, 0, SEEK_END);

  int size = ftell(file);
  rewind(file);
  
  char* buffer = malloc(sizeof(char) * size+1);

  if (buffer == NULL) {
    fclose(file);
    return NULL;
  }

  fread(buffer, sizeof(char), size, file);

  buffer[size] = '\0';
  fclose(file);
  return buffer;
}
