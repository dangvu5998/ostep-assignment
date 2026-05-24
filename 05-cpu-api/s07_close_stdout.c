#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    close(STDOUT_FILENO);
    // Print nothing
    printf("Hello!");
    return 0;
}
