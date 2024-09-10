
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>

using namespace std;

static int idata = 111;
int main(int argc, char* argv[]) {

    int istack = 222;
    pid_t childPid;

    switch (childPid = fork()) {
        case -1:
            cout << "fork err\n";
            return -1;
        case 0:
            idata *= 3;
            istack *= 3;
            break;
        default:
        sleep(2);
        break;

    }
    printf("PID=%ld %s idata=%d istack=%d\n", (long) getpid(), (childPid == 0) ? "(child) " : "(parent)", idata, istack);
    return 0;
}