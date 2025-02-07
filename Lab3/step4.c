//Name: Curtis Robinson
//Date: Jan 22th 2025
//Title: Lab3 - Step 4
//Description: In this step we will be be using cat and grep on seperate children processes to demonstrate multiple pipes

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fds[2];
    // Create a pipe
    if (pipe(fds) == -1) {
        perror("pipe");
        exit(1);
    }
    if (fork() == 0) {
        close(fds[0]);          
        dup2(fds[1], 1);        // Redirect stdout to the write end of the pipe
        close(fds[1]);         

        // Execute "cat /etc/passwd"
        execlp("cat", "cat", "/etc/passwd", NULL);

        perror("execlp cat");
        exit(1);
    }
    // Second child process (grep root)
    if (fork() == 0) {
        close(fds[1]);          
        dup2(fds[0], 0);        // Redirect stdin to the read end of the pipe
        close(fds[0]);   
        execlp("grep", "grep", "root", NULL);

        // If execlp fails
        perror("execlp grep");
        exit(1);
    }

    // Parent process
    close(fds[0]);              
    close(fds[1]);             

    wait(NULL);
    wait(NULL);

    return 0;
}
