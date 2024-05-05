from typing import List, Type
import random
import math

from algebraic_field import AlgebraicField

class DHSetup():
    def __init__(self, field_class: Type[AlgebraicField]):
        self._field_class: Type[AlgebraicField] = field_class
        self._field_characteristic: int = field_class.CHARACTERISTIC()
        self._generator: AlgebraicField = self._generate_generator()

    @property
    def generator(self) -> AlgebraicField:
        return self._generator

    def power(self, a: AlgebraicField, b: int) -> AlgebraicField:
        result = self._field_class.create_field(1)
        while b > 0:
            if (b & 1) == 1:
                result = result * a
            b = b >> 1
            a = a * a
        return result

    def _generate_generator(self) -> AlgebraicField:
        random.seed()
        generator = self._field_class.create_field(random.randint(1, self._field_characteristic - 1))
        while not self._is_generator(generator):
            generator = self._field_class.create_field(random.randint(1, self._field_characteristic - 1))
        return generator

    def _is_generator(self, generator: AlgebraicField) -> bool:
        p = self._field_characteristic
        prime_factors = self._get_prime_factors(p - 1)

        for q in prime_factors:
            if self.power(generator, (p - 1) // q) == 1:
                return False
        return True

    def _is_prime(self, number: int) -> bool:
        if number <= 1:
            return False
        for i in range(2, int(math.sqrt(number)) + 1):
            if number % i == 0:
                return False
        return True

    def _get_prime_factors(self, number: int) -> List[int]:
        prime_factors = []
        for i in range(2, int(math.sqrt(number)) + 1):
            if number % i == 0 and self._is_prime(i):
                prime_factors.append(i)
        return prime_factors
