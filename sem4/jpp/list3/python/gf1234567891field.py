from algebraic_field import AlgebraicField


class GF1234567891Field(AlgebraicField):
    _CHARACTERISTIC = 1234567891

    def __init__(self, value: int = 0) -> None:
        self._value = value % self._CHARACTERISTIC
        if self._value < 0:
            self._value += self._CHARACTERISTIC

    @staticmethod
    def CHARACTERISTIC() -> int:
        return GF1234567891Field._CHARACTERISTIC

    @property
    def value(self) -> int:
        return self._value

    @staticmethod
    def create_field(value: int) -> "AlgebraicField":
        return GF1234567891Field(value)

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        return self._value == other._value

    def __ne__(self, other: object) -> bool:
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        return self._value != other._value

    def __lt__(self, other: object) -> bool:
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        return self._value < other._value

    def __le__(self, other: object) -> bool:
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        return self._value <= other._value

    def __gt__(self, other: object) -> bool:
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        return self._value > other._value

    def __ge__(self, other: object) -> bool:
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        return self._value >= other._value

    def __add__(self, other: object) -> "GF1234567891Field":
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        return GF1234567891Field((self._value + other._value) % self._CHARACTERISTIC)

    def __sub__(self, other: object) -> "GF1234567891Field":
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        return GF1234567891Field((self._value - other._value) % self._CHARACTERISTIC)

    def __mul__(self, other: object) -> "GF1234567891Field":
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        return GF1234567891Field((self._value * other._value) % self._CHARACTERISTIC)

    def __truediv__(self, other: object) -> "GF1234567891Field":
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        if other._value == 0:
            raise ValueError("Division by 0!")
        inverse = self._get_modular_inverse(other._value)
        return GF1234567891Field((self._value * inverse) % self._CHARACTERISTIC)

    def assign(self, other: "AlgebraicField") -> None:
        self._value = other.value % self._CHARACTERISTIC

    def __iadd__(self, other: object) -> "GF1234567891Field":
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        self._value = (self._value + other._value) % self._CHARACTERISTIC
        return self

    def __isub__(self, other: object) -> "GF1234567891Field":
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        self._value = (self._value - other._value) % self._CHARACTERISTIC
        if self._value < 0:
            self._value += self._CHARACTERISTIC
        return self

    def __imul__(self, other: object) -> "GF1234567891Field":
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        self._value = (self._value * other._value) % self._CHARACTERISTIC
        return self

    def __itruediv__(self, other: object) -> "GF1234567891Field":
        if not isinstance(other, GF1234567891Field):
            return NotImplemented
        if other._value == 0:
            raise ValueError("Division by 0!")
        inverse = self._get_modular_inverse(other._value)
        self._value = (self._value * inverse) % self._CHARACTERISTIC
        return self

    def __str__(self) -> str:
        return str(self._value)

    def __repr__(self) -> str:
        return f"GF1234567891Field({self._value})"

    def __int__(self) -> int:
        return self._value

    def __float__(self) -> float:
        return float(self._value)

    def _get_modular_inverse(self, number: int) -> int:
        modulo = self._CHARACTERISTIC
        original_modulo = modulo
        inverse = 0
        temp_result = 1

        while number > 1:
            quotient = number // modulo
            temp = modulo
            modulo = number % modulo
            number = temp
            temp = inverse
            inverse = temp_result - quotient * inverse
            temp_result = temp

        if temp_result < 0:
            temp_result += original_modulo

        return temp_result
