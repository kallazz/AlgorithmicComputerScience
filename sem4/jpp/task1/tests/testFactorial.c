#include "../mathLib.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    int numbers_to_test = 11;
    int expected_results[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

    for (int input = 0; input < numbers_to_test; input++) {
        assert(factorial(input) == expected_results[input]);
    }
    printf("Tests passed.\n");

    return 0;
}