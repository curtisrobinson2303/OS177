// Thread Sychronization
// To compile this code:
// If using the SCU Linux lab first add #include<fcntl.h>
// Then you're ready to compile.
// gcc threadSync.c
// gcc threadSync.c -o test

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t *sem;

void *go(void *arg) {
  sem_wait(sem);                                              // entry section
  printf("Thread %d Entered Critical Section..\n", (int)arg); // critical
                                                              // section
  sleep(1);
  sem_post(sem); // exit section
  return (NULL);
}

int main() {
  sem = sem_open("sem", O_CREAT, 0644, 1);
  static int i;
  for (i = 0; i < NTHREADS; i++)
    pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
    printf("\t\t\tThread %d returned \n", i);
  }
  printf("Main thread done.\n");
  sem_unlink("sem");
  return 0;
}
