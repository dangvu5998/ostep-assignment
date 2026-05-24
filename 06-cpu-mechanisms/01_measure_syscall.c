#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    // need to create demo.txt file before run the program
    int fd = open("./demo.txt", O_RDONLY);
    char buffer[1];
    struct timeval starttime;
    struct timeval endtime;
    gettimeofday(&starttime, NULL);
    int nbOfIters = 10000000;
    for (int i = 0; i < nbOfIters; i++) {
        read(fd, buffer, 0);
    }
    gettimeofday(&endtime, NULL);
    long long total_time_us = (endtime.tv_sec - starttime.tv_sec) * 1000000LL + (endtime.tv_usec - starttime.tv_usec);
    double avg_syscall_ns = (double) total_time_us * 1000.0 / nbOfIters;
    printf("After %d iteration took: %lldus\n", nbOfIters, total_time_us);
    printf("Average time on system call = %.2fns\n", avg_syscall_ns);
    return 0;
}
