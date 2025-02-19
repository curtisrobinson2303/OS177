// Name: Curtis Robinson
// Date: Feb 10th 2025
// Title: Lab5 – Step 3
// Description: Here I use semaphores to create a producer consumer model
// program. This allows for users to produce and consume data using sempharoes
// to prevent race conditions in the critical regions.

//  Producer Consumer Model using semaphores

// *** OLD PROGRAM COMMENTED OUT ***
// #include <pthread.h>
// #include <semaphore.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// #define BUFFER_SIZE 5 // storing n items

// int buffer[BUFFER_SIZE];
// int in = 0;
// int out = 0;
// sem_t empty, full, mutex; // mutex = lock according to lab handout

// void *producer(void *arg) {
//   int item;
//   while (1) {
//     item = rand() % 100; // Produce an item
//     printf("Producer produced: %d\n", item);

//     sem_wait(&empty); // Wait for empty slot
//     sem_wait(&mutex); // Acquire lock

//     buffer[in] = item;
//     in = (in + 1) % BUFFER_SIZE;

//     sem_post(&mutex); // Release lock
//     sem_post(&full);  // Signal that a slot is full
//   }
// }

// void *consumer(void *arg) {
//   int item;
//   while (1) {
//     sem_wait(&full);  // Wait for full slot
//     sem_wait(&mutex); // Acquire lock

//     item = buffer[out];
//     out = (out + 1) % BUFFER_SIZE;

//     sem_post(&mutex); // Release lock
//     sem_post(&empty); // Signal that a slot is empty

//     printf("Consumer consumed: %d\n", item);
//   }
// }

// int main() {
//   pthread_t producer_thread, consumer_thread;

//   // Initialize semaphores
//   sem_init(&empty, 0, BUFFER_SIZE); // Initially all slots are empty
//   sem_init(&full, 0, 0);            // Initially no slots are full
//   sem_init(&mutex, 0, 1);           // Initialize mutex for mutual exclusion

//   // Create producer and consumer threads
//   pthread_create(&producer_thread, NULL, producer, NULL);
//   pthread_create(&consumer_thread, NULL, consumer, NULL);

//   // Join threads (not necessary in this infinite loop scenario)
//   // pthread_join(producer_thread, NULL);
//   // pthread_join(consumer_thread, NULL);

//   // Keep the program running (you might want to add a termination condition)
//   while (1) {
//     sleep(1); // Sleep to avoid excessive CPU usage
//   }

//   return 0;
// }

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include for time functions
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
sem_t empty, full, mutex; // mutex = lock according to lab handout

void *producer(void *arg) {
  int item;
  time_t start_time = time(NULL); // Record start time

  while (time(NULL) - start_time < 5) { // Check if 5 seconds have elapsed
    item = rand() % 100;
    printf("Producer produced: %d\n", item);

    sem_wait(&empty);
    sem_wait(&mutex);

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;

    sem_post(&mutex);
    sem_post(&full);
  }
  pthread_exit(NULL); // Exit thread gracefully
}

void *consumer(void *arg) {
  int item;
  time_t start_time = time(NULL); // Record start time

  while (time(NULL) - start_time < 5) { // Check if 5 seconds have elapsed
    sem_wait(&full);
    sem_wait(&mutex);

    item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;

    sem_post(&mutex);
    sem_post(&empty);

    printf("Consumer consumed: %d\n", item);
  }
  pthread_exit(NULL); // Exit thread gracefully
}

int main() {
  pthread_t producer_thread, consumer_thread;

  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);
  sem_init(&mutex, 0, 1);

  pthread_create(&producer_thread, NULL, producer, NULL);
  pthread_create(&consumer_thread, NULL, consumer, NULL);

  // Wait for threads to finish (important!)
  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  // Destroy semaphores when done
  sem_destroy(&empty);
  sem_destroy(&full);
  sem_destroy(&mutex);

  printf("Program finished.\n"); // Indicate program completion
  return 0;
}