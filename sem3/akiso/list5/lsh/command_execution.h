#ifndef COMMAND_EXECUTION_H
#define COMMAND_EXECUTION_H

#include "utils.h"

#include <stdbool.h>

extern const char *BUILT_IN_COMMANDS[];
extern ShellStatus (*BUILT_IN_COMMAND_FUNCTIONS[]) (char**);
extern const int AMOUNT_OF_BUILT_IN_COMMANDS;

ShellStatus lsh_cd(char **args);
ShellStatus lsh_exit(char **args);
ShellStatus lsh_background(ShellStatus (*command)(char**), char **args);

ShellStatus chooseCommand(char **args, bool background);
ShellStatus executeCommand(char **args);
ShellStatus executeExternalCommand(char **args, bool background);

#endif // COMMAND_EXECUTION_H
