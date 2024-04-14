#ifndef _WRAPPER_H_
#define _WRAPPER_H_

typedef struct {
    int x;
    int y;
} DiophantineEquationSolution;

unsigned long factorial(unsigned long n);
unsigned long factorialRecursive(unsigned long n);

unsigned int gcd(unsigned int a, unsigned int b);
unsigned int gcdRecursive(unsigned int a, unsigned int b);
int gcdI(int a, int b);

DiophantineEquationSolution diophantine(int a, int b, int c);
DiophantineEquationSolution diophantineRecursive(int a, int b, int c);

#endif // _WRAPPER_H_
