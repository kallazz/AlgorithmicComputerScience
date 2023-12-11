#include "utils.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *ERROR_PREFIX = "LSH_ERROR: ";
const int DIRECTORY_BUFFER_SIZE = 200;
const int TOKEN_BUFFER_SIZE = 64;
const char *TOKEN_DELIMITERS = " \t\r\n";

char **getArraySubset(char **arr, int startIdx, int endIdx) {
    char **subset = malloc((endIdx - startIdx + 2) * sizeof(char*));

    int subsetIdx = 0;
    for (int i = startIdx; i <= endIdx; i++) {
        subset[subsetIdx] = arr[i];
        subsetIdx++;
    }
    subset[endIdx + 1] = NULL;

    return subset;
}

void printError(char *message) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s%s", ERROR_PREFIX, message);

    perror(buffer);
}

char* getCurrentWorkingDirectory(void) {
    const int bufferSize = DIRECTORY_BUFFER_SIZE;
    const size_t allocationSize = bufferSize * sizeof(char);
    char *cwd = malloc(allocationSize);

    if (!cwd) {
        perror("getCurrentWorkingDirectory");
        free(cwd);
        return "";
    }

    if (getcwd(cwd, allocationSize) == NULL) {
        printError("getCurrentWorkingDirectory");
        free(cwd);
        return "";
    }

    return cwd;
}

char *readLine(void) {
    char *line = NULL;
    ssize_t bufferSize = 0;

    if (getline(&line, &bufferSize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            printError("readLine");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}

char **tokenizeLine(char *line) {
    int bufferSize = TOKEN_BUFFER_SIZE;
    int position = 0;
    char **tokens = malloc(bufferSize * sizeof(char*));
    char *token;

    if (!tokens) {
        printError("tokenizeLine");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIMITERS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufferSize) {
            bufferSize += TOKEN_BUFFER_SIZE;
            tokens = realloc(tokens, bufferSize * sizeof(char*));
            if (!tokens) {
                printError("tokenizeLine");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    tokens[position] = NULL;

    return tokens;
}
