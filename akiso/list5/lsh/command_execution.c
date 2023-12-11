#include "command_execution.h"

#include <linux/limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

const char *BUILT_IN_COMMANDS[] = {"cd", "exit"};
ShellStatus (*BUILT_IN_COMMAND_FUNCTIONS[]) (char**) = {&lsh_cd, &lsh_exit};
const int AMOUNT_OF_BUILT_IN_COMMANDS = sizeof(BUILT_IN_COMMANDS) / sizeof(BUILT_IN_COMMANDS[0]);

// ********************************************** Built-in commands **********************************************
ShellStatus lsh_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd requires 1 argument!\n");
    } else if (chdir(args[1]) != 0) {
        perror("cd");
    }

    return READY_FOR_NEXT_COMMAND;
}

ShellStatus lsh_exit(char **args) {
    return TERMINATE;
}

// For executing internal commands in the background(&)
ShellStatus lsh_background(ShellStatus (*command)(char**), char **args) {
    pid_t pid = fork();

    if (pid <= -1) {
        printError("lsh_background");
    }
    if (pid > 0) {
        // Parent
        printf("[%d launched in the background]\n", pid);

        int status;
        if (waitpid(pid, &status, WUNTRACED) == -1) {
            printError("waitpid");
            return READY_FOR_NEXT_COMMAND;  // or TERMINATE, depending on your design
        }
    }
    else {
        // Child
        command(args);
        _exit(EXIT_SUCCESS);
    }

    return READY_FOR_NEXT_COMMAND;
}

// ********************************************** Command handling **********************************************

ShellStatus executeCommand(char **args) {
    if (args[0] == NULL) {
        return READY_FOR_NEXT_COMMAND;
    }

    int commandIndex = 0;
    int argsSize = 0;
    while (args[argsSize] != NULL) { argsSize++; }
    for (int i = 0; i < argsSize; i++) {
        if (strcmp(args[i], "&") == 0) {
            char **arraySubset = getArraySubset(args, commandIndex, i - 1);
            chooseCommand(arraySubset, true);
            free(arraySubset);

            commandIndex = i + 1;
        }
    }

    if (strcmp(args[argsSize - 1], "&") != 0) {
        char **arraySubset = getArraySubset(args, commandIndex, argsSize - 1);
        ShellStatus ret = chooseCommand(arraySubset, false);
        free(arraySubset);
        return ret;
    }

    return READY_FOR_NEXT_COMMAND;
}

ShellStatus chooseCommand(char **args, bool background) {
    // Check if this is an internal command
    for (int i = 0; i < AMOUNT_OF_BUILT_IN_COMMANDS; i++) {
        if (strcmp(args[0], BUILT_IN_COMMANDS[i]) == 0) {
            if (background) {
                return lsh_background(BUILT_IN_COMMAND_FUNCTIONS[i], args);
            }
            return BUILT_IN_COMMAND_FUNCTIONS[i](args);
        }
    }

    // If not, try to execute Linux commands
    return executeExternalCommand(args, background);
}

void redirectIO(char *file, int fd, int flags) {
    int file_desc = open(file, flags, 0644);
    if (file_desc < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (dup2(file_desc, fd) < 0) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(file_desc);
}

ShellStatus executeExternalCommand(char **args, bool background) {
    pid_t pid = fork();

    if (pid < 0) {
        printError("executeExternalCommand");
    } else if (pid == 0) {
        // Dziecko
        // Ustawianie przekierowań I/O
        for (int i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], ">") == 0 && args[i+1] != NULL) {
                redirectIO(args[i+1], STDOUT_FILENO, O_WRONLY | O_CREAT | O_TRUNC);
                args[i] = NULL; // Usuwanie przekierowania z argumentów
            } else if (strcmp(args[i], "<") == 0 && args[i+1] != NULL) {
                redirectIO(args[i+1], STDIN_FILENO, O_RDONLY);
                args[i] = NULL; // Usuwanie przekierowania z argumentów
            } else if (strcmp(args[i], "2>") == 0 && args[i+1] != NULL) {
                redirectIO(args[i+1], STDERR_FILENO, O_WRONLY | O_CREAT | O_TRUNC);
                args[i] = NULL; // Usuwanie przekierowania z argumentów
            }
        }

        // Uruchamianie komendy
        if (execvp(args[0], args) == -1) {
            printError("executeExternalCommand");
            _exit(EXIT_FAILURE);
        }
    } else {
        // Rodzic
        if (!background) {
            // Czekanie na zakończenie procesu w przypadku uruchomienia w trybie foreground
            int status;
            waitpid(pid, &status, WUNTRACED);
        } else {
            printf("[%d launched in the background]\n", pid);
        }
    }

    return READY_FOR_NEXT_COMMAND;
}