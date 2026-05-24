#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc == 0) {
        printf("This is child, hello\n");
    } else {
        // wait(NULL);
        sleep(1);
        printf("This is parent, bye\n");
    }
    return 0;
}
