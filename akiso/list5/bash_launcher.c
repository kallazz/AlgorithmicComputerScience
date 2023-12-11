#include <stdlib.h>

/*
    Before executing:
    sudo chown root:root a.out
    sudo chmod +s a.out
*/

int main(int argc, char **argv, char **envp) {
    char *command[] = {"bash", NULL};

    setuid(0);
    execve("/bin/bash", command, envp);

    // This code will be executed if something goes wrong
    perror("Error");
    exit(1);
}
