from typing import Optional
import random

from algebraic_field import AlgebraicField
from dh_setup import DHSetup


class User:
    def __init__(self, dh_setup: DHSetup):
        self._dh_setup: DHSetup = dh_setup
        self._secret: int = self._generate_secret()
        self._public_key: AlgebraicField = self._generate_public_key()
        self._encryption_key: Optional[AlgebraicField] = None

    @property
    def public_key(self) -> AlgebraicField:
        return self._public_key

    def set_key(self, a: AlgebraicField) -> None:
        self._encryption_key = self._dh_setup.power(a, self._secret)

    def encrypt(self, m: AlgebraicField) -> AlgebraicField:
        if self._encryption_key is None:
            raise RuntimeError("Encryption key was not initialized!")
        return m * self._encryption_key

    def decrypt(self, c: AlgebraicField) -> AlgebraicField:
        if self._encryption_key is None:
            raise RuntimeError("Encryption key was not initialized!")
        return c / self._encryption_key

    def _generate_secret(self) -> int:
        random.seed()
        return random.randint(1, self._dh_setup.generator.CHARACTERISTIC() - 1)

    def _generate_public_key(self) -> AlgebraicField:
        return self._dh_setup.power(self._dh_setup.generator, self._secret)
