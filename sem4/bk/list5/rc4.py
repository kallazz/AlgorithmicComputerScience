from typing import List

ASCII_BIGGEST_INDEX = 127
MOD = 256


def _KSA(key: List[int]) -> List[int]:
    key_length = len(key)
    key = [key[i % key_length] for i in range(MOD)]
    S = list(range(MOD))
    j = 0

    for i in range(0, MOD):
        j = (j + S[i] + key[i % key_length]) % MOD
        S[i], S[j] = S[j], S[i]

    return S


def _PRGA(S: List[int], text_length: int) -> List[int]:
    keystream = []
    i = 0
    j = 0

    for _ in range(text_length):
        i = (i + 1) % MOD
        j = (j + S[i]) % MOD
        S[i], S[j] = S[j], S[i]
        keystream.append(S[(S[i] + S[j]) % MOD])

    return keystream


def RC4(text: str, key: str) -> str:
    text_codes = [ord(char) for char in text]
    key_codes = [ord(char) for char in key]

    S = _KSA(key_codes)
    keystream = _PRGA(S, len(text))

    return "".join([chr(p ^ k) for p, k in zip(text_codes, keystream)])


def is_the_same_key(ciphertext1: str, ciphertext2: str) -> bool:
    ciphertext1_codes = [ord(char) for char in ciphertext1]
    ciphertext2_codes = [ord(char) for char in ciphertext2]
    length = min(len(ciphertext1), len(ciphertext2))
    for i in range(length):
        if ciphertext1_codes[i] ^ ciphertext2_codes[i] > ASCII_BIGGEST_INDEX:
            return False

    return True
