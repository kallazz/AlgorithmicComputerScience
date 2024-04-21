#include "mathLib.h"

#include <stdlib.h>

unsigned long factorial(unsigned long n) {
    unsigned long result = 1;
    while (n > 1) {
        result = result * n;
        n--;
    }

    return result;
}

unsigned long factorialRecursive(unsigned long n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorialRecursive(n - 1);
}

unsigned int gcd(unsigned int a, unsigned int b) {
    if (b == 0) {
        return a;
    }

    unsigned int r;
    while (a % b > 0) {
        r = a % b;
        a = b;
        b = r;
    }

    return b;
}

int gcdI(int a, int b) {
    if (b == 0) {
        return a;
    }

    int r;
    while (a % b > 0) {
        r = a % b;
        a = b;
        b = r;
    }

    return b;
}

unsigned int gcdRecursive(unsigned int a, unsigned int b) {
    if (b != 0) {
        return gcdRecursive(b, a % b);
    }
    return a;
}

int gcdExtended(int a, int b, int *x, int *y) {
    int xPrev = 1, yPrev = 0, xCurr = 0, yCurr = 1;
    int quotient, temp;

    while (b != 0) {
        quotient = a / b;

        temp = b;
        b = a % b;
        a = temp;

        temp = xPrev - quotient * xCurr;
        xPrev = xCurr;
        xCurr = temp;
        temp = yPrev - quotient * yCurr;
        yPrev = yCurr;
        yCurr = temp;
    }

    *x = xPrev;
    *y = yPrev;

    return a;
}

int gcdExtendedRecursive(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcdResult = gcdExtendedRecursive(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcdResult;
}

DiophantineEquationSolution diophantine(int a, int b, int c) {
    DiophantineEquationSolution solution = {0, 0};

    if (a == 0 && b == 0) {
        return solution;
    }

    int xSolution, ySolution;
    int gcdResult = gcdExtended(abs(a), abs(b), &xSolution, &ySolution);

    if (c % gcdResult != 0) {
        return solution;
    }

    xSolution *= c / gcdResult;
    ySolution *= c / gcdResult;
    if (a < 0) {
        xSolution *= -1;
    }
    if (b < 0) {
        ySolution *= -1;
    }
    solution.x = xSolution;
    solution.y = ySolution;

    return solution;
}

DiophantineEquationSolution diophantineRecursive(int a, int b, int c) {
    DiophantineEquationSolution solution = {0, 0};

    if (a == 0 && b == 0) {
        return solution;
    }

    int xSolution, ySolution;
    int gcdResult = gcdExtendedRecursive(abs(a), abs(b), &xSolution, &ySolution);

    if (c % gcdResult != 0) {
        return solution;
    }

    xSolution *= c / gcdResult;
    ySolution *= c / gcdResult;
    if (a < 0) {
        xSolution *= -1;
    }
    if (b < 0) {
        ySolution *= -1;
    }
    solution.x = xSolution;
    solution.y = ySolution;

    return solution;
}
