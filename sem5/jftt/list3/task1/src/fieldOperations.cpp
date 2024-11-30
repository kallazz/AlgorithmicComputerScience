#include "fieldOperations.hpp"

long long fieldAdd(long long a, long long b, long long fieldCharacteristic) {
    return (a + b) % fieldCharacteristic;
}

long long fieldSub(long long a, long long b, long long fieldCharacteristic) {
    return (a - b + fieldCharacteristic) % fieldCharacteristic;
}

long long fieldMul(long long a, long long b, long long fieldCharacteristic) {
    return (a * b) % fieldCharacteristic;
}

long long fieldDiv(long long a, long long b, long long fieldCharacteristic) {
    return (a * fieldPow(b, fieldCharacteristic - 2, fieldCharacteristic)) % fieldCharacteristic;
}

long long fieldPow(long long a, long long b, long long fieldCharacteristic) {
    long long result = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            result = fieldMul(result, a, fieldCharacteristic);
        }
        a = fieldMul(a, a, fieldCharacteristic);
        b /= 2;
    }
    return result;
}
