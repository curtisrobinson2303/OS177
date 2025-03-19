// Name: Curtis Robinson
// Description: writing to a new file every time
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s filename buffer_size\n", argv[0]);
    return 1;
  }

  int bufSize = atoi(argv[2]);
  if (bufSize <= 0) {
    fprintf(stderr, "Invalid buffer size\n");
    return 1;
  }

  FILE *inFile = fopen(argv[1], "rb");
  if (!inFile) {
    perror("fopen input");
    return 1;
  }

  FILE *outFile = fopen("copy.out", "wb");
  if (!outFile) {
    perror("fopen output");
    fclose(inFile);
    return 1;
  }

  char *buffer = malloc(bufSize);
  if (!buffer) {
    perror("malloc");
    fclose(inFile);
    fclose(outFile);
    return 1;
  }

  size_t bytesRead;
  while ((bytesRead = fread(buffer, 1, bufSize, inFile)) > 0) {
    size_t bytesWritten = fwrite(buffer, 1, bytesRead, outFile);
    if (bytesWritten != bytesRead) {
      perror("fwrite");
      free(buffer);
      fclose(inFile);
      fclose(outFile);
      return 1;
    }
  }

  free(buffer);
  fclose(inFile);
  fclose(outFile);
  return 0;
}
