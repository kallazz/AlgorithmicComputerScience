import random
from typing import Tuple

from math_utils import gcd, is_prime


def generate_rsa_keypair(p: int, q: int) -> Tuple[Tuple[int, int], Tuple[int, int]]:
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
