#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc == 0) {
        printf("This is child, hello\n");
        char* command[3];
        command[0] = "/bin/ls";
        command[1] = "-l";
        command[2] = NULL;
        execvp(command[0], command);
    } else {
        // __pid_t pid = wait(NULL);
        __pid_t pid = waitpid(rc, NULL, 0);
        printf("Return pid = %d\n", pid);
        printf("This is parent, bye\n");
    }
    return 0;
}
