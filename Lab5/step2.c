// Name: Curtis Robinson
// Date: Feb 10th 2025
// Title: Lab5 – Step 2
// Description: Here I used mutex locks to create the same functionality of
// entering and leading the critical section.

// Modifying Threadsync.c to use Mutex Locks

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t mutex;

void *go(void *arg) {
  pthread_mutex_lock(&mutex);                                 // entry section
  printf("Thread %d Entered Critical Section..\n", (int)arg); // critical
                                                              // section
  sleep(1);
  pthread_mutex_unlock(&mutex); // exit section
  return (NULL);
}

int main() {
  pthread_mutex_init(&mutex, NULL);

  static int i;
  for (i = 0; i < NTHREADS; i++)
      pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
    printf("\t\t\tThread %d returned \n", i);
  }
  printf("Main thread done.\n");
  pthread_mutex_destroy(&mutex);
  return 0;
}