#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
sem_t empty, full, mutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item
        printf("Producer produced: %d\n", item);

        sem_wait(&empty); // Wait for empty slot
        sem_wait(&mutex); // Acquire lock

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Release lock
        sem_post(&full); // Signal that a slot is full
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full); // Wait for full slot
        sem_wait(&mutex); // Acquire lock

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Release lock
        sem_post(&empty); // Signal that a slot is empty

        printf("Consumer consumed: %d\n", item);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Initially all slots are empty
    sem_init(&full, 0, 0);          // Initially no slots are full
    sem_init(&mutex, 0, 1);         // Initialize mutex for mutual exclusion

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Join threads (not necessary in this infinite loop scenario)
    // pthread_join(producer_thread, NULL);
    // pthread_join(consumer_thread, NULL);

    // Keep the program running (you might want to add a termination condition)
    while (1) {
        sleep(1); // Sleep to avoid excessive CPU usage
    }

    return 0;
}