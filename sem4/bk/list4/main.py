from typing import Tuple

from math_utils import gcd
from rsa_keys_generator import generate_rsa_keypair


def crack_p(n: int, d1: int, e1: int) -> int:
    kphi = d1 * e1 - 1
    t = kphi

    while t % 2 == 0:
        t //= 2

    a = 2
    while True:
        k = t
        while k < kphi:
            x = pow(a, k, n)
            if x != 1 and x != (n - 1) and pow(x, 2, n) == 1:
                r = gcd(x - 1, n)
                return n // r
            k *= 2
        a += 2


def crack_private_key(n: int, d1: int, e1: int, e2: int) -> Tuple[int, int]:
    p = crack_p(n, d1, e1)
    q = n // p
    phi = (p - 1) * (q - 1)
    d = pow(e2, -1, phi)
    private_key = (n, d)
    return private_key


def main() -> None:
    p = 10007
    q = 10009
    n = p * q
    public_key_a, private_key_a = generate_rsa_keypair(p, q)
    public_key_b, private_key_b = generate_rsa_keypair(p, q)
    print(f"A Keys: {public_key_a, private_key_a}")
    print(f"B Keys: {public_key_b, private_key_b}")

    calculated_private_key = crack_private_key(
        n, public_key_a[1], public_key_b[1], public_key_b[1]
    )
    print(f"Calculated private key: {calculated_private_key}")

    if calculated_private_key == private_key_b:
        print("The keys match!")


if __name__ == "__main__":
    main()
