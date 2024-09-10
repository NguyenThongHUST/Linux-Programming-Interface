
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

void signal_handler(int sig) {
    printf("Parent received signal: %d\n", sig);
}


int main() {
    pid_t pid;
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(pid == 0) {
        printf("Child process started, PID: %d\n", getpid());
        sleep(2);
        kill(getppid(), SIGUSR1);
        printf("Child sent signal to parent\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Parent process, PID: %d\n", getpid());
        pause(); // wait signal to be sent
        wait(NULL);
        printf("Parent process finishing\n");
    }

    return 0;
}