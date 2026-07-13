#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include "utils/file_reader.h" 
char* readFile(char* filename) {
  int fd = open(filename, O_RDONLY); //Open file
  if (fd < 0) { //Just like if file == NULL type syscall
    printf("cry: File does not exist\n");
    exit(1);
  }
  
  int size = lseek(fd, 0, SEEK_OUT);
  lseek(fd, 0, SEEK_SET);
  
  char* buffer = malloc(sizeof(char) * size+1);

  if (buffer == NULL) {
    close(fd);
    return NULL;
  }

  read(fd, buffer, size);
  buffer[size] = '\0';
  close(fd);
  return buffer;
}
