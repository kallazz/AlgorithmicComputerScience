#include "../mathLib.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    unsigned int expectedResults[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
    unsigned int expectedResultsSize = sizeof(expectedResults) / sizeof(expectedResults[0]);

    printf("Non-recursive\n");
    for (unsigned int input = 0; input < expectedResultsSize; input++) {
        printf("Input: %u\n", input);
        assert(factorial(input) == expectedResults[input]);
    }

    printf("Recursive\n");
    for (unsigned int input = 0; input < expectedResultsSize; input++) {
        printf("Input: %u\n", input);
        assert(factorialRecursive(input) == expectedResults[input]);
    }

    return 0;
}
