from abc import ABC, abstractmethod


class AlgebraicField(ABC):
    @staticmethod
    @abstractmethod
    def CHARACTERISTIC() -> int:
        pass

    @staticmethod
    @abstractmethod
    def create_field(value: int) -> "AlgebraicField":
        pass

    @property
    @abstractmethod
    def value(self) -> int:
        pass

    @abstractmethod
    def __eq__(self, other: object) -> bool:
        pass

    @abstractmethod
    def __ne__(self, other: object) -> bool:
        pass

    @abstractmethod
    def __lt__(self, other: object) -> bool:
        pass

    @abstractmethod
    def __le__(self, other: object) -> bool:
        pass

    @abstractmethod
    def __gt__(self, other: object) -> bool:
        pass

    @abstractmethod
    def __ge__(self, other: object) -> bool:
        pass

    @abstractmethod
    def __add__(self, other: object) -> "AlgebraicField":
        pass

    @abstractmethod
    def __sub__(self, other: object) -> "AlgebraicField":
        pass

    @abstractmethod
    def __mul__(self, other: object) -> "AlgebraicField":
        pass

    @abstractmethod
    def __truediv__(self, other: object) -> "AlgebraicField":
        pass

    @abstractmethod
    def assign(self, other: "AlgebraicField") -> None:
        pass

    @abstractmethod
    def __iadd__(self, other: object) -> "AlgebraicField":
        pass

    @abstractmethod
    def __isub__(self, other: object) -> "AlgebraicField":
        pass

    @abstractmethod
    def __imul__(self, other: object) -> "AlgebraicField":
        pass

    @abstractmethod
    def __itruediv__(self, other: object) -> "AlgebraicField":
        pass

    @abstractmethod
    def __str__(self) -> str:
        pass

    @abstractmethod
    def __repr__(self) -> str:
        pass

    @abstractmethod
    def __int__(self) -> int:
        pass

    @abstractmethod
    def __float__(self) -> float:
        pass
