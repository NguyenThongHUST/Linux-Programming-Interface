
/* nodefer.cc - demonstrates the effect of the SA_NODEFER flag of sigaction(2).
 *
 * The SA_NODEFER is a flag that can be passed to the `sigaction(2)` system call
 * and tells the kernel not to block the received signal while the handler is
 * running. As a consequence, if the same signal is received during the handler
 * execution, the handler itself will be suspended and another handler instance
 * will start running.
 *
 * This program demonstrates this behavior by registering a handler for the
 * SIGINT signal that prints a message and then sleeps. The user is able to
 * confirm that another instance of the handler is executed by triggering another
 * interrupt while the first one is sleeping. It is also possible to notice
 * that the first handler will only finish after the second one is done.
 *
 * Usage
 *
 *    $ ./nodefer
 *
 * Author: thong.nguyen
 */

#include <csignal>
#include <cstdint>
#include <cstdlib>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

#define NODEFER_SLEEPTIME 2

static void handler(int sig) {
    static int count = 0;
    count ++;
    if(count == 5) {
        exit(EXIT_SUCCESS);
    }
    int id = count;
    printf("\t[%d] SIGINT received. Sleeping for %d seconds...\n", id, NODEFER_SLEEPTIME);
    sleep(NODEFER_SLEEPTIME);

    printf("\t[%d] Done\n", id);
}

int main() {
    struct sigaction sig_act;
    sig_act.sa_handler = handler;
    sig_act.sa_flags = SA_NODEFER;
    sigemptyset(&sig_act.sa_mask);

    if (sigaction(SIGINT, &sig_act, NULL) == -1) 
    {
        cout << "sigaction error \n";
        return -1;
    }

    for (;;) {
        pause();
    }

    exit(EXIT_SUCCESS);
    return 0;
}