import ctypes

# gcc -shared -o math_lib.so ../libraryC/mathLib.c

math_lib = ctypes.CDLL("./math_lib.so")


class DiophantineEquationSolution(ctypes.Structure):
    _fields_ = [("x", ctypes.c_int), ("y", ctypes.c_int)]


def factorial(n: ctypes.c_ulong) -> ctypes.c_ulong:
    math_lib.factorial.restype = ctypes.c_ulong
    return math_lib.factorial(n)


def factorial_recursive(n: ctypes.c_ulong) -> ctypes.c_ulong:
    math_lib.factorialRecursive.restype = ctypes.c_ulong
    return math_lib.factorialRecursive(n)


def gcd(a: ctypes.c_uint, b: ctypes.c_uint) -> ctypes.c_uint:
    math_lib.gcd.restype = ctypes.c_uint
    return math_lib.gcd(a, b)


def gcd_recursive(a: ctypes.c_uint, b: ctypes.c_uint) -> ctypes.c_uint:
    math_lib.gcdRecursive.restype = ctypes.c_uint
    return math_lib.gcdRecursive(a, b)


def gcd_i(a: ctypes.c_int, b: ctypes.c_int) -> ctypes.c_int:
    math_lib.gcdI.restype = ctypes.c_int
    return math_lib.gcdI(a, b)


def diophantine(
    a: ctypes.c_int, b: ctypes.c_int, c: ctypes.c_int
) -> DiophantineEquationSolution:
    math_lib.diophantine.restype = DiophantineEquationSolution
    return math_lib.diophantine(a, b, c)


def diophantine_recursive(
    a: ctypes.c_int, b: ctypes.c_int, c: ctypes.c_int
) -> DiophantineEquationSolution:
    math_lib.diophantineRecursive.restype = DiophantineEquationSolution
    return math_lib.diophantineRecursive(a, b, c)
