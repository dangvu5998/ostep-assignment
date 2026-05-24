#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed!");
        return -1;
    }
    int rc1 = fork();
    if (rc1 < 0) {
        perror("Fork failed");
        return -1;
    }
    if (rc1 > 0) {
        int rc2 = fork();
        if (rc2 < 0) {
            perror("Fork failed");
            return -1;
        }
        if (rc2 == 0) {
            // read something
            char buffer[100];
            ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';
                printf("Print from child 2: %s", buffer);
            }
        }
    } else {
        // write something
        char *message = "Hello from child 1\n";
        write(pipefd[1], message, strlen(message));
    }
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
