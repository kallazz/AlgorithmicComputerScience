import random
import string

from rc4 import RC4

ACCOUNT_NUMBER_LENGTH = 16
BANK_IDENTIFIERS = {
    "NBP": "10100000",
    "PKO BP": "10200003",
    "ING": "10500002",
    "mBank": "11400000",
    "Pekao SA": "12400001",
}


def generate_random_client_number() -> str:
    return "".join(random.choices(string.digits, k=ACCOUNT_NUMBER_LENGTH))


def generate_random_key() -> str:
    return "".join(random.choices(string.ascii_letters + string.digits, k=50))


def generate_checksum() -> str:
    # change for actual calculation
    return "".join(random.choices(string.digits, k=2))


def check_bank_identifier_checksum(bank_identifier: str) -> bool:
    digits = [int(number) for number in bank_identifier][:-1]
    weights = [7, 1, 3, 9, 7, 11, 3]
    result = 0
    for digit, weight in zip(digits, weights):
        result += digit * weight
    return result % 10 == bank_identifier[-1]


def generate_random_bank_account_number() -> str:
    return generate_checksum() + random.choice(list(BANK_IDENTIFIERS.values())) + generate_random_client_number()


def main() -> None:
    account_numbers = [generate_random_bank_account_number() for _ in range(10)]
    key = generate_random_key()
    encrypted_account_numbers = [RC4(number, key) for number in account_numbers]
    encrypted_account_numbers_codes = []
    for i, account_number in enumerate(encrypted_account_numbers):
        encrypted_account_numbers_codes[i] = [ord(char) for char in account_number]

    for i in range(len(encrypted_account_numbers) - 1):
        print(f"XOR:")
        print(encrypted_account_numbers[i])
        print(encrypted_account_numbers[i + 1])
        for j in range(len(encrypted_account_numbers)):
            print(encrypted_account_numbers_codes[i][j] ^ encrypted_account_numbers_codes[i + 1][j])


if __name__ == "__main__":
    main()
