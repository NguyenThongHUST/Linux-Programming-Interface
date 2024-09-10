
/* ignore_pending.c - shows the behavior of ignored pending signals.
 *
 * When a process receives a signal that is currently blocked (i.e., is in the
 * process' procmask), it is said to be 'pending'. Pending signals are delivered
 * to the process as soon as the signal is unblocked, i.e., removed from the
 * sigprocmask.
 *
 * This program demonstrates that if we choose to ignore pending signals, then
 * they will not reach the process after they are unblocked. To that aim, this
 * program will first block SIGINT, and then raise it; after checking that the
 * signal is indeed in the pending list, SIGINT is then unblocked and we show
 * that the process terminates gracefully, without receiving the signal (there
 * is no custom handler for that signal and the default action is to terminate
 * the process).
 *
 * Usage
 *
 *    $ ./ignore_pending 
 *    using CRTL + C to send SIGINT from terminal to child process (executable file run as 
 *    a child proces of terminal)
 *
 * Author: thong.nguyen
 */

#include <csignal>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    sigset_t cur_set, pending_set;
    sigemptyset(&cur_set);
    sigaddset(&cur_set, SIGINT);

    // blocking signals
    if(sigprocmask(SIG_BLOCK, &cur_set, nullptr) == -1) {
        cout << "error sigprocmask\n";
        return -1;
    }
    
    cout << "process sleeping 10 seconds \n";
    sleep(10);

    if(sigpending(&cur_set) == -1) {
        cout << "eror sigpending \n";
        return -1;
    }

    // check SIGINT is pending signal
    if(sigismember(&cur_set, SIGINT)) {
        cout << "SIGINT is member pending list \n";
    }

    if(signal(SIGINT, SIG_IGN) == SIG_ERR) {
        cout << "error ignore SIGINT\n";
    }
    // unblocking signal
    
    if(sigprocmask(SIG_UNBLOCK, &cur_set, nullptr) == -1 ) {
        cout << "error sigprocmask \n";
    }


    if(sigpending(&cur_set) == -1) {
        cout << "eror sigpending\n";
        return -1;
    }

    // check SIGINT is pending signal
    if(sigismember(&cur_set, SIGINT)) {
        cout << "SIGINT is still in the pending list, aborting\n \n";
        return -1;
    } else {
        cout << "SIGINT signal is not on the pending list any more \n";
    }

    cout << "terminate success \n";
    return 0;
}