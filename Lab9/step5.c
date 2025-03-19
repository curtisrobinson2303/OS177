// Name: Curtis Robinson
// Description: Writing to new files on multiple threads
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *filename;
  int bufferSize;
  int threadNum;
} thread_arg;

void *copy_file(void *arg) {
  thread_arg *targ = (thread_arg *)arg;
  FILE *inFile = fopen(targ->filename, "rb");
  if (!inFile) {
    fprintf(stderr, "Thread %d: Error opening input file %s: %s\n",
            targ->threadNum, targ->filename, strerror(errno));
    pthread_exit((void *)1);
  }
  char outFilename[256];
  snprintf(outFilename, sizeof(outFilename), "copy%d.out", targ->threadNum);
  FILE *outFile = fopen(outFilename, "wb");
  if (!outFile) {
    fprintf(stderr, "Thread %d: Error opening output file %s: %s\n",
            targ->threadNum, outFilename, strerror(errno));
    fclose(inFile);
    pthread_exit((void *)1);
  }
  char *buffer = malloc(targ->bufferSize);
  if (!buffer) {
    fprintf(stderr, "Thread %d: Memory allocation error\n", targ->threadNum);
    fclose(inFile);
    fclose(outFile);
    pthread_exit((void *)1);
  }

  size_t bytesRead;
  while ((bytesRead = fread(buffer, 1, targ->bufferSize, inFile)) > 0) {
    size_t bytesWritten = fwrite(buffer, 1, bytesRead, outFile);
    if (bytesWritten != bytesRead) {
      fprintf(stderr, "Thread %d: Write error\n", targ->threadNum);
      free(buffer);
      fclose(inFile);
      fclose(outFile);
      pthread_exit((void *)1);
    }
  }

  free(buffer);
  fclose(inFile);
  fclose(outFile);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    fprintf(stderr, "Usage: %s filename buffer_size num_threads\n", argv[0]);
    return 1;
  }

  char *filename = argv[1];
  int bufferSize = atoi(argv[2]);
  int numThreads = atoi(argv[3]);

  if (bufferSize <= 0 || numThreads <= 0) {
    fprintf(stderr, "Invalid buffer size or number of threads\n");
    return 1;
  }

  pthread_t *threads = malloc(numThreads * sizeof(pthread_t));
  thread_arg *args = malloc(numThreads * sizeof(thread_arg));
  if (!threads || !args) {
    perror("malloc");
    free(threads);
    free(args);
    return 1;
  }

  for (int i = 0; i < numThreads; i++) {
    args[i].filename = filename;
    args[i].bufferSize = bufferSize;
    args[i].threadNum = i; // Output file will be copy0.out, copy1.out, etc.
    if (pthread_create(&threads[i], NULL, copy_file, &args[i]) != 0) {
      fprintf(stderr, "Error creating thread %d\n", i);
    }
  }

  for (int i = 0; i < numThreads; i++) {
    pthread_join(threads[i], NULL);
  }

  free(threads);
  free(args);
  return 0;
}
