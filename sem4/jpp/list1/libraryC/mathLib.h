#ifndef _MATH_LIB_H_
#define _MATH_LIB_H_

typedef struct {
    int x;
    int y;
} DiophantineEquationSolution;

unsigned long factorial(unsigned long n);
unsigned long factorialRecursive(unsigned long n);

unsigned int gcd(unsigned int a, unsigned int b);
unsigned int gcdRecursive(unsigned int a, unsigned int b);
int gcdExtended(int a, int b, int *x, int *y);
int gcdExtendedRecursive(int a, int b, int *x, int *y);
int gcdI(int a, int b);

DiophantineEquationSolution solveDiophantineEquation(int a, int b, int c);
DiophantineEquationSolution solveDiophantineEquationRecursive(int a, int b, int c);

#endif // _MATH_LIB_H_
