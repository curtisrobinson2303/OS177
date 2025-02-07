//Name: Curtis Robinson
//Date: Jan 15th 2025
//Title: Lab2 - Step 5
//Description: In this part of the lab we will be creating an algorithm that will create 7 processes throguhout the program. The Requirements are listed in the section below.
/*  Step 5 Complete
    Requirements: 
        Created 7 Processes 
        One Parent 
        Six Children 
        Every process must have 2 children
        Print each of the PID of the current process and its parent and its children
*/

#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */


void process_tree(int level, int maxlevels){
    if (level > maxlevels){
        return;
    }

    printf("Current Level: %d\n", level);

    pid_t left_child, right_child; 
    left_child = fork();

    if (left_child == 0)
    {
        process_tree(level + 1, maxlevels);
        exit(0);
    } else if (left_child > 0 ){
        right_child = fork();

        if (right_child == 0) {
            process_tree(level + 1, maxlevels);
            exit(0);
        } else if (right_child > 0) {
            printf("parent process: PID=%d, left child PID=%d, right child PID=%d\n\n", getpid(), left_child, right_child);
        } else {
            fprintf(stderr, "error forking right child\n");
        }
    } else 
    {
        printf("left child fork failed to create\n\n");
    }

    wait(NULL);
    wait(NULL);
}

int main(int argc, char *argv[]) {
    printf("\n\nCreating 7 processes\n");
    printf("Current Head Node: process: PID=%d\n", getpid());

    process_tree(1,2);

    printf("7 Processes created");

    return 0;
}