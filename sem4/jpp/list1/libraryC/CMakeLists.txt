cmake_minimum_required(VERSION 3.10)
project(MathLib VERSION 1.0)

set(SRC
    mathLib.c
    mathLib.h
)

add_executable(${PROJECT_NAME}-factorial-ut tests/testFactorial.c ${SRC})
add_executable(${PROJECT_NAME}-gcd-ut tests/testGcd.c ${SRC})
add_executable(${PROJECT_NAME}-solveDiophantineEquation-ut tests/testSolveDiophantineEquation.c ${SRC})

enable_testing()
add_test(NAME factorialTests COMMAND ${PROJECT_NAME}-factorial-ut)
add_test(NAME gcdTests COMMAND ${PROJECT_NAME}-gcd-ut)
add_test(NAME solveDiophantineEquationTests COMMAND ${PROJECT_NAME}-solveDiophantineEquation-ut)
