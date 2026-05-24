#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    printf("hello from main\n");
    int fd = open("./out/demo.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc == 0) {
        printf("This is child\n");
        const char *childText = "Hello from child!\n";
        write(fd, childText, strlen(childText));
    } else {
        printf("This is parent\n");
        const char *parentText = "Hello from parent!\n";
        write(fd, parentText, strlen(parentText));
    }
    close(fd);
    return 0;
}
