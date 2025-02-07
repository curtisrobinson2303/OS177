//Name: Curtis Robinson
//Date: Jan 15th 2025
//Title: Lab2 - Step 6
//Description: This is the code for step 6 of the lab 

#include <stdio.h> /* printf, stderr */
#include <stdlib.h> /* atoi */
#include <unistd.h> /* usleep */
#include <pthread.h> /* pthread */

void *parent_thread(void *arg) {
    int n = *((int *)arg);
    for (int i = 0; i < 100; i++) {
        printf("\t \t \t parent thread %d \n", i);
        usleep(n);
    }
    return NULL;
}

void *child_thread(void *arg) {
    int n = *((int *)arg);
    for (int i = 0; i < 100; i++) {
        printf("child thread %d\n", i);
        usleep(n);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);

    printf("\n before creating threads. \n");

    pthread_t parent_tid, child_tid;

    // create the parent thread
    pthread_create(&parent_tid, NULL, parent_thread, &n);

    // create the child thread
    pthread_create(&child_tid, NULL, child_thread, &n);

    // let threads complete and rejoin them
    pthread_join(parent_tid, NULL);
    pthread_join(child_tid, NULL);

    return 0;
}
