
#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h> 
#include <stdio.h>     
#include <stdlib.h>    
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */
#include <stdbool.h>    /* 'bool' type plus 'true' and 'false' constants */

using namespace std;

int main(int argc, char *argv[]) {
    int s, sig;
    long s_pid;

    if(argc != 3) {
        cout << "error input \n";
        return -1;
    }

    s_pid = atol(argv[1]);
    sig = atoi(argv[2]);

    s = kill(s_pid, sig);
    
    if(sig != 0) {
        if(s == -1) {
            cout << "kill\n";
            return -1;
        } else {
            cout << "send signal success\n";
        }
    } else {
        if (s == 0) {
            printf("Process exists and we can send it a signal\n");
        } else {
            if (errno == EPERM)
                printf("Process exists, but we don't have "
                       "permission to send it a signal\n");
            else if (errno == ESRCH)
                printf("Process does not exist\n");
            else
                cout << "kill\n";
        }

    }
    return 0;
}