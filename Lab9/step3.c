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

  FILE *fp = fopen(argv[1], "rb");
  if (!fp) {
    perror("fopen");
    return 1;
  }

  char *buffer = malloc(bufSize);
  if (!buffer) {
    perror("malloc");
    fclose(fp);
    return 1;
  }

  // Read using the variable buffer size
  while (fread(buffer, 1, bufSize, fp) > 0) {
    // No processing needed
  }

  free(buffer);
  fclose(fp);
  return 0;
}
