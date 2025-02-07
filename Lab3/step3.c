//Name: Curtis Robinson
//Date: Jan 22th 2025
//Title: Lab3 - Step 3
//Description: In this step we will be redirecting the output of our ls command to an alternate pipe. 


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fds[2];
    char buff[60];
    int count;
    int i;

    // Create a pipe
    pipe(fds);

    if (fork() == 0) {
        // Writer process
        printf("\nWriter on the upstream end of the pipe -> running `ls` command\n");
        
        // Redirect the output of `ls` to the write end of the pipe
        close(fds[0]);        // Close unused read end
        dup2(fds[1], 1);      // Redirect stdout to the pipe's write end
        close(fds[1]);        // Close the original write end

        // Execute the `ls` command
        execlp("ls", "ls", NULL);

        // If execlp fails, exit with error
        perror("execlp failed");
        exit(1);
    } else if (fork() == 0) {
        // Reader process
        printf("\nReader on the downstream end of the pipe\n");
        
        close(fds[1]);        // Close unused write end
        while ((count = read(fds[0], buff, sizeof(buff) - 1)) > 0) {
            buff[count] = '\0'; // Null-terminate the buffer
            printf("%s", buff); // Print the received data
        }
        close(fds[0]);        // Close the read end
        exit(0);
    } else {
        // Parent process
        close(fds[0]);        // Close both ends of the pipe
        close(fds[1]);
        wait(0);              // Wait for child processes to finish
        wait(0);
    }
    return 0;
}
