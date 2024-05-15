from typing import List

MOD = 256


def KSA(key: List[int]) -> List[int]:
    key_length = len(key)
    key = [key[i % key_length] for i in range(MOD)]
    S = list(range(MOD))
    j = 0

    for i in range(0, MOD):
        j = (j + S[i] + key[i % key_length]) % MOD
        S[i], S[j] = S[j], S[i]

    return S


def PRGA(S: List[int], text_length: int) -> List[int]:
    keystream = []
    i = 0
    j = 0

    for _ in range(text_length):
        i = (i + 1) % MOD
        j = (j + S[i]) % MOD
        S[i], S[j] = S[j], S[i]
        keystream.append(S[(S[i] + S[j]) % MOD])

    return keystream


def RC4(text: str, key: str) -> List[int]:
    text = [ord(char) for char in text]
    key = [ord(char) for char in key]

    S = KSA(key)
    keystream = PRGA(S, len(text))

    return "".join([chr(p ^ k) for p, k in zip(text, keystream)])


def were_texts_encrypted_using_the_same_key(ciphertext1: str, ciphertext2: str) -> bool:
    ciphertext1 = [ord(char) for char in ciphertext1]
    ciphertext2 = [ord(char) for char in ciphertext2]
    for i in range(min(len(ciphertext1), len(ciphertext2))):
        if ciphertext1[i] ^ ciphertext2[i] >= 128:
            return False
    return True
