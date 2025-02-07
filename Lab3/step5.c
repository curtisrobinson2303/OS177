//Name: Curtis Robinson
//Date: Jan 22th 2025
//Title: Lab3 - Step 5
//Description: In this step we will be creating the producer consumer model 


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MESSAGE_SIZE 32 

int main() {
    int fds[2];  // Pipe file descriptors
    pid_t pid;

    // Create the pipe
    if (pipe(fds) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        close(fds[1]); 
        char buffer[MESSAGE_SIZE];
        while (1) {
            ssize_t bytesRead = read(fds[0], buffer, MESSAGE_SIZE - 1);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0'; 
                printf("Consumer received: %s\n", buffer);
            } else if (bytesRead == 0) {
                break; 
            } else {
                perror("read");
                break;
            }
        }

        close(fds[0]);  // Close the read end
        exit(0);
    } else {
        close(fds[0]);  

        char message[MESSAGE_SIZE];
        int messageCount = 0;

        while (1) {
            snprintf(message, MESSAGE_SIZE, "Message %d", ++messageCount);

            write(fds[1], message, strlen(message));
            printf("Producer sent: %s\n", message);

            usleep(500000);  // 500 ms
            if (messageCount >= 10) {
                break;
            }
        }

        close(fds[1]);  
        wait(NULL);  
    }
    return 0;
}
