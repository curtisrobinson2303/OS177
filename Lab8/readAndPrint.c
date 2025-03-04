
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  char *inputBuffer = ""; // add the input to the buffer which comes from the
                          // std output of the other file

  while (fgets(inputBuffer, 100, stdin)) { //  read the input through stdin
    int page_num = atoi(inputBuffer);      // store the input in a buffer
    printf("%d\n", page_num);              // output a buffer
  }
}