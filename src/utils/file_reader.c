#include <stdio.h> //Foe printing stuff
#include <stdlib.h> //Allocating memory
#include <unistd.h> //To help with syntax write() and read() as well as lseek()
#include <fcntl.h>  //Also used on file I/O , like open()
#include "utils/file_reader.h" //For header purposes, right?
char* readFile(char* filename) {
  int fd = open(filename, O_RDONLY); //Open file
  if (fd < 0) { //Just like if file == NULL type syscall
    printf("cry: File does not exist\n");
    exit(1); //To quit? Yeah
  }
  
  int size = lseek(fd, 0, SEEK_OUT); // Find the size of the file
  lseek(fd, 0, SEEK_SET); // Low-level why of rewinding
  
  char* buffer = malloc(sizeof(char) * size+1); // I'll keep it

  if (buffer == NULL) { //You know, if buffer equal to No string
    close(fd);  //Ya'll closing the file, like closing the barn
    return NULL;
  }
  
  read(fd, buffer, size); // Read the file
  buffer[size] = '\0'; // Add a null-terminator so the code don't crash =)
  close(fd); //Close the file , duh
  return buffer; //Returning buffer? , ok 
}
/*Joke of the day: You know why developer like dark mode
  Because: The light attract bugs
*/
