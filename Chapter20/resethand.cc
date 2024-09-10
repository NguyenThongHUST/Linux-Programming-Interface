
/* resethand.cc - demonstrates the effect of the SA_RESETHAND flag of sigaction(2).
 *
 * The SA_RESETHAND is a flag that can be passed to the `sigaction(2)` system call
 * and tells the kernel to reset the signal disposition before executing the handler.
 * This has the effect of registering the handler just for the next signal of the
 * given type that arrives (thus the legacy name SA_ONESHOT).
 *
 * This program verifies this behavior by registering a custom handler for the
 * SIGINT signal, printing a message in the screen. The second time the signal
 * is sent, the default action is taken and the process is terminated.
 *
 * Usage
 *
 *    $ ./resethand
 *
 * Author: thong.nguyen
 */

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

void handler(int sig) {
    if(sig == SIGINT)
        cout << "received SIGINT signal \n";
}

int main() {
    struct sigaction action;
    action.sa_flags = SA_RESETHAND;
    action.sa_handler = handler;

    if(sigaction(SIGINT, &action, NULL) == -1) 
    {
        cout << "Error sigaction api \n"; 
        return -1;
    }

    while (1) {
        pause();
    }
    exit(EXIT_SUCCESS);
}