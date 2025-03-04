// Name: Curtis Robinson
// Date: March 4th 2025
// Title: Lab8 – Number Generator Algorithm
// Description: This file implements the a number generator for page replacement
// testing.s

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  char buffer[sizeof(int)];
  int i;

  int numRequests = 1000;
  int possiblePages = 100;

  fp = fopen("testInput.txt", "w");
  for (i = 0; i < numRequests; i++) {
    sprintf(buffer, "%d\n", rand() % possiblePages);
    fputs(buffer, fp);
  }
  fclose(fp);
  return 0;
}
