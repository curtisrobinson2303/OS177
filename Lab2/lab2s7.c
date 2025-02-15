//Name: Curtis Robinson
//Date: Jan 15th 2025
//Title: Lab2 - Step 7
//Description: This is the code for step 7 of the lab 

#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */

int main(int argc, char *argv[]) {
    pid_t pid;
    
    printf("\n Before forking.\n");

    pid = fork();

    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }

    if(pid == 0)
        {
            execlp("/bin/ls", "ls", NULL);
        }
        else
        {
            wait(NULL);
            printf("Child Complete");
            exit(0);
        }
    return 0;
}