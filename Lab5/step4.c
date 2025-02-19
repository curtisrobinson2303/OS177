// Name: Curtis Robinson
// Date: Feb 10th 2025
// Title: Lab5 – Step 4
// Description: In this program the goal is to create the same producer consumer
// model to prevent race conditions in the critical area. This will be done with
// mutex locks instead of semaphores as previously used in step 3.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int buffer_count = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
  srand(time(NULL));

  while (1) {
    int item = rand() % 100 + 1;
    printf("Producer produced: %d\n", item);

    pthread_mutex_lock(&lock);
    while (buffer_count == BUFFER_SIZE) {
      pthread_cond_wait(&empty, &lock);
    }

    buffer[buffer_count] = item;
    buffer_count++;

    pthread_cond_signal(&full);
    pthread_mutex_unlock(&lock);

    usleep(20000);
  }
  return NULL;
}

void *consumer(void *arg) {
  while (1) {
    pthread_mutex_lock(&lock);
    while (buffer_count == 0) {
      pthread_cond_wait(&full, &lock);
    }

    int item = buffer[0]; // Correct access: Get the *first* item
    // Shift remaining elements
    for (int i = 0; i < buffer_count - 1; i++) {
      buffer[i] = buffer[i + 1];
    }
    buffer_count--;

    printf("Consumer consumed: %d\n", item);

    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&lock);

    usleep(30000);
  }
  return NULL;
}

int main() {
  pthread_t producer_thread, consumer_thread;

  pthread_create(&producer_thread, NULL, producer, NULL);
  pthread_create(&consumer_thread, NULL, consumer, NULL);

  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  return 0;
}