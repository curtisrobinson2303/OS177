/*Sample C program for Lab assignment 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//main
int main() {
int fds[2];
pipe(fds);
/*child 1 duplicatesdownstream into stdin */
if (fork() == 0) {
dup2(fds[0], 0);
close(fds[1]);
execlp("more", "more", 0);
}
/*child 2 duplicates upstream into stdout */
else if (fork() == 0) {
dup2(fds[1], 1);
close(fds[0]);
execlp("ls", "ls", 0);
}
else { /*parent closes both ends and waits for children*/
    close(fds[0]);
    close(fds[1]);
    wait(0);
    wait(0);
}
return 0;
}