#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello from main\n");
    int x = 100;
    int rc = fork();
    if (rc == 0) {
        x = 10;
        printf("This is child, x = %d\n", x);
    } else {
        x = 1000 * 3209 * x;
        printf("This is parent, x = %d\n", x);
    }

    return 0;
}
