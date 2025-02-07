//Name: Curtis Robinson
//Date: Jan 15th 2025
//Title: Lab2 Steps 1,2,3,4
//Description: This is the code for steps 1,2,3, and 4
/* 
    Step 1 Complete
    Step 2 Complete
    Step 3 Complete
    Step 4 Complete
    Step 5 Complete
    Step 6 Complete
    Step 7 Complete
*/

/*Sample C program for Lab assignment 1*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
/* main function with command-line arguments to pass */

int main(int argc, char *argv[]) {
    pid_t pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    
    printf("\n Before forking.\n");

    pid = fork();

    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }

    if (pid){
        // Parent process
        for (i=0;i<100;i++) {
            printf("\t \t \t Parent Process %d \n",i);
            usleep(n);
        }
    }
    else{
        // Child process
        for (i=0;i<100;i++) {
            printf("Child process %d\n",i);
            usleep(n);
        }
    }
    return 0;
}