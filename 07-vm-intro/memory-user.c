#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <memory in MB> <time in seconds>\n", argv[0]);
        return 1;
    }
    int memory_mb = atoi(argv[1]);
    int time_in_s = atoi(argv[2]);
    size_t total_bytes = (size_t)memory_mb * 1048576;
    char* hold_memory = malloc(memory_mb * 1048576);
    if (hold_memory == NULL) {
        printf("Failed to allocate memory");
        return 1;
    }
    pid_t pid = getpid();
    printf("PID = %d\n", pid);
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < time_in_s) {
        for (int i = 0; i < memory_mb * 1048576; i++) {
            *(hold_memory + i) = 'a';
        }
    }

    free(hold_memory);
    return 0;
}
