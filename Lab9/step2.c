#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    return 1;
  }

  FILE *fp = fopen(argv[1], "rb");
  if (!fp) {
    perror("fopen");
    return 1;
  }

  char buffer[10000];
  // Read until end-of-file
  while (fread(buffer, sizeof(buffer), 1, fp) == 1) {
    // No processing needed
  }

  fclose(fp);
  return 0;
}
