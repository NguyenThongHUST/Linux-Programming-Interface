

#include <bits/types/sigset_t.h>
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <signal.h>

using namespace std;

int main(int argc, char* argv[]) {
    int numSigs, sig;
    pid_t pid;

    if(argc < 4 ) {
        cout << "error input \n";
        return -1;
    }

    pid = atol(argv[1]);
    numSigs = atoi(argv[2]);
    sig = atoi(argv[3]);

    printf("%s: sending signal %d to process %ld %d times\n",
            argv[0], sig, (long) pid, numSigs);

    for(int j = 0; j < numSigs; j++) {
        if(kill(pid, sig) == -1) {
            cout << "error kill \n";
            return -1;
        }
    }
       
    return 0;
}
