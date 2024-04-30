from typing import Tuple

from rsa_keys_generator import generate_rsa_key_pair


def calculate_private_key(public_key: int, p: int, q: int) -> Tuple[int, int]:
    n, e = public_key
    phi = (p - 1) * (q - 1)
    d = pow(e, -1, phi)
    private_key = (n, d)
    return private_key


def main() -> None:
    p = 10007
    q = 10009
    public_key_a, private_key_a = generate_rsa_key_pair(p, q)
    public_key_b, private_key_b = generate_rsa_key_pair(p, q)
    print(f"A Keys: {public_key_a, private_key_a}")
    print(f"B Keys: {public_key_b, private_key_b}")

    calculated_private_key = calculate_private_key(public_key_b, p, q)
    print(f"Calculated private B key: {calculated_private_key}")
    if calculated_private_key == private_key_b:
        print("The keys match!")


if __name__ == "__main__":
    main()
