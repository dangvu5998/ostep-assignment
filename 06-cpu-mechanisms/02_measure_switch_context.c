#define _GNU_SOURCE
#include <sys/time.h>
#include <sched.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(2, &cpuset); // depend on system
    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) == -1) {
        perror("sched_setaffinity failed");
        return 1;
    }
    int fd1[2];
    int fd2[2];
    if (pipe(fd1) != 0 || pipe(fd2)) {
        perror("can't create pipe");
        return 1;
    }
    int rc = fork();
    if (rc < 0) {
        perror("can't fork new process");
        return 1;
    }
    char wbuff = 'A';
    int rbuff[1];
    int nb_of_iters = 50000;
    if (rc != 0) {
        close(fd1[0]);
        close(fd2[1]);
        struct timeval starttime;
        struct timeval endtime;
        gettimeofday(&starttime, NULL);
        for (int i = 0; i < nb_of_iters; i++) {
            write(fd1[1], &wbuff, 1);
            read(fd2[0], &rbuff, 1);
        }
        gettimeofday(&endtime, NULL);
        int nb_of_sw = nb_of_iters * 2; // switch parent -> child -> parent
        long long total_duration = (endtime.tv_sec - starttime.tv_sec) * 1000000LL +
            (endtime.tv_usec - starttime.tv_usec);
        double avg_sw_time = (double) total_duration / nb_of_sw;
        printf("Total time: %lldus\n", total_duration);
        printf("Avg after %d switches: %.2fus\n", nb_of_sw, avg_sw_time);

        close(fd1[1]);
        close(fd2[0]);
    } else {
        close(fd1[1]);
        close(fd2[0]);
        for (int i = 0; i < nb_of_iters; i++) {
            read(fd1[0], &rbuff, 1);
            write(fd2[1], &wbuff, 1);
        }
        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    }
}
