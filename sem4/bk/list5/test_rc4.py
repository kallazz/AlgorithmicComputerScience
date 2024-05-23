import random
import string

import pytest
from rc4 import RC4, is_the_same_key

TEST_REPEATS = 100


class TestRC4:
    @staticmethod
    def generate_random_string(length: int = 20) -> str:
        return "".join(random.choices(string.ascii_letters + string.digits, k=length))

    def test_encryption(self):
        for _ in range(TEST_REPEATS):
            text1 = self.generate_random_string()
            text2 = self.generate_random_string()
            key1 = self.generate_random_string()
            key2 = self.generate_random_string()

            ciphertext1 = RC4(text1, key1)
            ciphertext2 = RC4(text2, key2)

            assert RC4(ciphertext1, key1) == text1
            assert RC4(ciphertext2, key2) == text2

    def test_same_keys(self):
        for _ in range(TEST_REPEATS):
            text1 = self.generate_random_string()
            text2 = self.generate_random_string()
            text3 = self.generate_random_string()
            key1 = self.generate_random_string()
            key2 = self.generate_random_string()
            while key2 == key1:
                key2 = self.generate_random_string()

            ciphertext1 = RC4(text1, key1)
            ciphertext2 = RC4(text2, key1)
            ciphertext3 = RC4(text3, key2)

            assert is_the_same_key(ciphertext1, ciphertext2) == True
            assert is_the_same_key(ciphertext1, ciphertext3) == False  # False positives are possible
            assert is_the_same_key(ciphertext2, ciphertext3) == False  # False positives are possible
