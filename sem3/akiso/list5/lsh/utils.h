#ifndef UTILS_H
#define UTILS_H

typedef enum ShellStatus { READY_FOR_NEXT_COMMAND, TERMINATE } ShellStatus;

extern const char *ERROR_PREFIX;
extern const int DIRECTORY_BUFFER_SIZE;
extern const int TOKEN_BUFFER_SIZE;
extern const char *TOKEN_DELIMITERS;

char **getArraySubset(char **arr, int startIdx, int endIdx);
void printError(char *message);
char *getCurrentWorkingDirectory(void);
char *readLine(void);
char **tokenizeLine(char *line);

#endif // UTILS_H
