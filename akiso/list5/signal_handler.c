#include <stdio.h>
#include <signal.h>

void handleSignal(int signalId) {
    printf("Received signal %d\n", signalId);
}

int main(void) {
    for (int i = 1; i <= 31; i++) {
        if (signal(i, handleSignal) == SIG_ERR) {
            printf("Couldn't catch signal %d\n", i);
        }
    }
    while(1);

    return 0;
}
