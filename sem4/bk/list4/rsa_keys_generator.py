import random
from math import sqrt
from typing import Tuple, Optional


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


def generate_rsa_key_pair(p: int, q: int) -> Tuple[Tuple[int, int], Tuple[int, int]]:
    """Generates a pair of RSA keys. Returns (public_key, private_key)"""
    if not is_prime(p) or not is_prime(q):
        raise ValueError("p or/and q is not prime!")
    phi = (p - 1) * (q - 1)

    e = random.randint(2, phi)
    while gcd(e, phi) != 1:
        e = random.randint(2, phi)

    d = pow(e, -1, phi)
    n = p * q
    public_key = (n, e)
    private_key = (n, d)

    return public_key, private_key
