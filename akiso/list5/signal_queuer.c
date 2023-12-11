#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

const int AMOUT_OF_SIGNALS = 10;
const int SIGNAL = SIGUSR1;

void handleSignal(int signalId) {
    printf("Received signal %d\n", signalId);
}

int main(void) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        signal(SIGNAL, handleSignal);

        while (1) {
            sleep(1);
        }

        _exit(EXIT_SUCCESS);
    } else {
        // Parent process
        int status;
        sleep(2);

        for (int i = 0; i < AMOUT_OF_SIGNALS; i++) {
            kill(pid, SIGNAL);
        }

        (void) waitpid(pid, &status, 0);
    }

    return 0;
}
