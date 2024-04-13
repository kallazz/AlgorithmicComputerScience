#include "../mathLib.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    unsigned int inputs[7][2] = {{0, 17}, {17, 0}, {3, 7}, {10, 6}, {15, 5}, {24, 18}, {75, 100}};
    unsigned int expectedResults[] = {17, 17, 1, 2, 5, 6, 25};
    unsigned int expectedResultsSize = sizeof(expectedResults) / sizeof(expectedResults[0]);

    printf("Non-recursive\n");
    for (unsigned int i = 0; i < expectedResultsSize; i++) {
        printf("Input: %u %u\n", inputs[i][0], inputs[i][1]);
        assert(gcd(inputs[i][0], inputs[i][1]) == expectedResults[i]);
    }

    printf("Recursive\n");
    for (unsigned int i = 0; i < expectedResultsSize; i++) {
        printf("Input: %u %u\n", inputs[i][0], inputs[i][1]);
        assert(gcdRecursive(inputs[i][0], inputs[i][1]) == expectedResults[i]);
    }

    return 0;
}
