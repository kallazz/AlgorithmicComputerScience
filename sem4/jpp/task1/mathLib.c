#include "mathLib.h"

long factorial(long n) {
    long result = 1;
    while (n > 1) {
        result = result * n;
        n--;
    }

    return result;
}

int gcd(int a, int b) {
    int r;
    while (a % b > 0) {
        r = a % b;
        a = b;
        b = r;
    }

    return b;
}

int diophantineEquation(int a, int b, int c) {
    return 0;
}