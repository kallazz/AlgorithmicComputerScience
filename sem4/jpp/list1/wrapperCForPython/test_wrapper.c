#include "wrapper.h"

#include <assert.h>
#include <stdio.h>

// gcc wrapper.c test_wrapper.c -I/usr/include/python3.8 -lpython3.8 && ./a.out

void testFactorial() {
    unsigned int expectedResults[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
    unsigned int expectedResultsSize = sizeof(expectedResults) / sizeof(expectedResults[0]);

    printf("\n************ FACTORIAL ************\n");
    printf("Non-recursive\n");
    for (unsigned int input = 0; input < expectedResultsSize; input++) {
        printf("Input: %u\n", input);
        assert(factorial(input) == expectedResults[input]);
    }

    printf("\nRecursive\n");
    for (unsigned int input = 0; input < expectedResultsSize; input++) {
        printf("Input: %u\n", input);
        assert(factorialRecursive(input) == expectedResults[input]);
    }
}

void testGcd() {
    unsigned int inputs[7][2] = {{0, 17}, {17, 0}, {3, 7}, {10, 6}, {15, 5}, {24, 18}, {75, 100}};
    unsigned int expectedResults[] = {17, 17, 1, 2, 5, 6, 25};
    unsigned int expectedResultsSize = sizeof(expectedResults) / sizeof(expectedResults[0]);

    printf("\n*************** GCD ***************\n");
    printf("Non-recursive\n");
    for (unsigned int i = 0; i < expectedResultsSize; i++) {
        printf("Input: %u %u\n", inputs[i][0], inputs[i][1]);
        assert(gcd(inputs[i][0], inputs[i][1]) == expectedResults[i]);
    }

    printf("\nRecursive\n");
    for (unsigned int i = 0; i < expectedResultsSize; i++) {
        printf("Input: %u %u\n", inputs[i][0], inputs[i][1]);
        assert(gcdRecursive(inputs[i][0], inputs[i][1]) == expectedResults[i]);
    }
}

void validate_diophantine_result(int a, int b, int c, DiophantineEquationSolution *solution) {
    printf("Valid\n");
    if (solution->x == 0 && solution->y == 0) {
        assert((a == 0 && b == 0) || (c % gcdI(a, b) != 0));
    } else {
        assert (a * solution->x + b * solution->y == c);
    }
}

void testDiophantine() {
    int inputs[16][3] = {
        {0, 0, 0},
        {0, 0, 5},
        {5, 0, 5},
        {0, 5, 5},
        {2, 4, 5},
        {6, -9, 29},
        {6, -9, 30},
        {-9, 6, 30},
        {2, -3, 10},
        {3, 2, 10},
        {4, 7, 19},
        {-6, -9, 10},
        {87, -64, 3},
        {137, 173, 99},
        {16, 7, 15},
        {195, 42, 12}
    };
    int inputsSize = sizeof(inputs) / sizeof(inputs[0]);

    printf("\n*********** DIOPHANTINE ***********\n");
    printf("Non-recursive\n");
    for (int i = 0; i < inputsSize; i++) {
        int a = inputs[i][0];
        int b = inputs[i][1];
        int c = inputs[i][2];
        printf("Input: a = %d, b = %d, c = %d\n", a, b, c);
        DiophantineEquationSolution result = diophantine(a, b, c);
        printf("Result: {%d, %d}\n", result.x, result.y);
        validate_diophantine_result(a, b, c, &result);
    }

    printf("\nRecursive\n");
    for (int i = 0; i < inputsSize; i++) {
        int a = inputs[i][0];
        int b = inputs[i][1];
        int c = inputs[i][2];
        printf("Input: a = %d, b = %d, c = %d\n", a, b, c);
        DiophantineEquationSolution result = diophantineRecursive(a, b, c);
        printf("Result: {%d, %d}\n", result.x, result.y);
        validate_diophantine_result(a, b, c, &result);
    }
}


int main(void) {
    testFactorial();
    testGcd();
    testDiophantine();
    printf("\nAll tests passed!\n");

    return 0;
}