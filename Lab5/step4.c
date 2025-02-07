#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0; 

pthread_mutex_t mutex;
pthread_cond_t empty, full; 

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item
        printf("Producer produced: %d\n", item);

        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) { // Buffer is full
            pthread_cond_wait(&empty, &mutex); 
        }

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        pthread_cond_signal(&full); 
        pthread_mutex_unlock(&mutex);
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        pthread_mutex_lock(&mutex);

        while (count == 0) { // Buffer is empty
            pthread_cond_wait(&full, &mutex); 
        }

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        pthread_cond_signal(&empty); 
        pthread_mutex_unlock(&mutex);

        printf("Consumer consumed: %d\n", item);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);

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

    // Clean up (optional)
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);

    return 0;
}