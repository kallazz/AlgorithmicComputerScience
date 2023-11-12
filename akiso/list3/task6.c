#include <stdio.h>

const char* getAnsiColorCode(char colorCode[15], int colorId) {
    snprintf(colorCode, 15, "\e[38;5;%dm", colorId);
    return colorCode;
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < 256; i++) {
        char colorCode[15];
        printf("%sHello, World!\n", getAnsiColorCode(colorCode, i));
    }
}