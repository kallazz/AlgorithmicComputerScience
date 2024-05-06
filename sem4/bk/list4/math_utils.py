from math import sqrt


def is_prime(n: int) -> bool:
    if n <= 1:
        return False
    for i in range(2, int(sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


def gcd(a: int, b: int) -> int:
    if b == 0:
        return a
    return gcd(b, a % b)
