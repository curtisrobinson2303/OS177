// Name: Curtis Robinson
// Date: Feb 7th 2024
// Title: Lab4 - Matrix Multiplication with Threads
// Description: This program demonstrates parallel matrix multiplication using threads.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 2 // Matrix dimensions
#define M 2
#define L 2

// Structure to pass arguments to threads
typedef struct {
    int row;
    int (*matrixA)[M];
    int (*matrixB)[L];
    int (*matrixC)[L];
} ThreadArgs;

// Function to be executed by each thread
void* multiplyRow(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int row = args->row;
    int (*matrixA)[M] = args->matrixA;
    int (*matrixB)[L] = args->matrixB;
    int (*matrixC)[L] = args->matrixC;

    for (int j = 0; j < L; j++) {
        int temp = 0;
        for (int k = 0; k < M; k++) {
            temp += matrixA[row][k] * matrixB[k][j];
        }
        matrixC[row][j] = temp;
    }

    pthread_exit(NULL);
}

int main() {
    int matrixA[N][M];
    int matrixB[M][L];
    int matrixC[N][L];

    srand(time(NULL));

    // Initialize matrices with random values as per instructions
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrixA[i][j] = rand() % 10;
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < L; j++) {
            matrixB[i][j] = rand() % 10;
        }
    }


    printf("A Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++) {
            printf("%d ", matrixA[i][j]);
        }
        printf("\n");
    }

    printf("B Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++) {
            printf("%d ", matrixB[i][j]);
        }
        printf("\n");
    }


    // Create an array of threads
    pthread_t threads[N];
    ThreadArgs thread_args[N];

    // Create threads
    for (int i = 0; i < N; i++) {
        thread_args[i].row = i;
        thread_args[i].matrixA = matrixA;
        thread_args[i].matrixB = matrixB;
        thread_args[i].matrixC = matrixC;

        if (pthread_create(&threads[i], NULL, multiplyRow, (void*)&thread_args[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    // Waiting for all threads to finish
    for (int i = 0; i < N; i++) {
        if (pthread_join(threads[i], NULL)) {
            fprintf(stderr, "Error joining thread\n");
            return 1;
        }
    }

    printf("Result Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++) {
            printf("%d ", matrixC[i][j]);
        }
        printf("\n");
    }

return 0;
}