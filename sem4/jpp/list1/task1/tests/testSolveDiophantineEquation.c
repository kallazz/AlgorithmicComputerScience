#include "../mathLib.h"

#include <assert.h>
#include <stdio.h>

void validate_result(int a, int b, int c, DiophantineEquationSolution *solution) {
    if (solution->x == 0 && solution->y == 0) {
        assert((a == 0 && b == 0) || (c % gcdI(a, b) != 0));
    } else {
        assert (a * solution->x + b * solution->y == c);
    }
}

int main(void) {
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

    printf("Non-recursive\n");
    for (int i = 0; i < inputsSize; i++) {
        int a = inputs[i][0];
        int b = inputs[i][1];
        int c = inputs[i][2];
        printf("Input: a = %d, b = %d, c = %d\n", a, b, c);
        DiophantineEquationSolution result = solveDiophantineEquation(a, b, c);
        printf("Result: {%d, %d}\n", result.x, result.y);
        validate_result(a, b, c, &result);
    }

    printf("Recursive\n");
    for (int i = 0; i < inputsSize; i++) {
        int a = inputs[i][0];
        int b = inputs[i][1];
        int c = inputs[i][2];
        printf("Input: a = %d, b = %d, c = %d\n", a, b, c);
        DiophantineEquationSolution result = solveDiophantineEquationRecursive(a, b, c);
        printf("Result: {%d, %d}\n", result.x, result.y);
        validate_result(a, b, c, &result);
    }

    return 0;
}
