#include "gcd.h"

#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    assert(gcd(1, 2) == 1);
    assert(gcd(2, 1) == 1);
    assert(gcd(2, 2) == 2);
    assert(gcd(370, 1000) == 10);
    assert(gcd(1000, 370) == 10);
    assert(gcd(43, 91) == 1);

    puts("All tests passed");
}