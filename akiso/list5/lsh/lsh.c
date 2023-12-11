#include "command_execution.h"
#include "utils.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void loop(void) {
    char *currentWorkingDirectory;
    char *line;
    char **args;
    ShellStatus status = READY_FOR_NEXT_COMMAND;

    do {
        currentWorkingDirectory = getCurrentWorkingDirectory();
        printf("%s>", currentWorkingDirectory);

        line = readLine();
        args = tokenizeLine(line);
        status = executeCommand(args);

        free(currentWorkingDirectory);
        free(line);
        free(args);
    } while (status == READY_FOR_NEXT_COMMAND);
}

int main(int argc, char **argv) {
    struct sigaction childAction;
    sigaction(SIGCHLD, NULL, &childAction);
    childAction.sa_flags = SA_NOCLDWAIT;
    sigaction(SIGCHLD, &childAction, NULL);

    loop();
}
