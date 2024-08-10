#define _GNU_SOURCE
#include <sys/types.h>  /* Type definitions used by many programs */
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */
#include <stdbool.h>    /* 'bool' type plus 'true' and 'false' constants */
#include <iostream>
#include <signal.h>
#include <vector>

using namespace std;

static vector<int> sigCnt(NSIG); 
static volatile sig_atomic_t gotSigint = 0;

static void handler(int sig) {
    if (sig == SIGINT)
        gotSigint = 1;
    else
        sigCnt[sig]++;
}

int main(int argc, char* argv[]) {
    int n, numSecs;
    sigset_t pendingMask, blockingMask, emptyMask;

    printf("%s: PID is %ld\n", argv[0], (long) getpid());
    for(int i = 0; i < NSIG; i++) {
        (void) signal(i, handler);
    }

    if(argc < 2) 
        return -1;
    
    numSecs = atoi(argv[1]);

    // blocked all signals
    sigfillset(&blockingMask);
    if (sigprocmask(SIG_SETMASK, &blockingMask, NULL) == -1)
        cout << "sigprocmask error\n";

    printf("%s: sleeping for %d seconds\n", argv[0], numSecs);

    if(sigpending(&pendingMask) == -1){
        cout << "sigpending error \n";
        return -1;
    }

    sigemptyset(&emptyMask);
    if (sigprocmask(SIG_SETMASK, &emptyMask, NULL) == -1)
            cout << "sigprocmask error \n";

    while (!gotSigint)                  /* Loop until SIGINT caught */
        continue;
    for (n = 1; n < NSIG; n++)          /* Display number of signals received */
        if (sigCnt[n] != 0)
            printf("%s: signal %d caught %d time%s\n", argv[0], n,
                    sigCnt[n], (sigCnt[n] == 1) ? "" : "s");
    return 0;
}
