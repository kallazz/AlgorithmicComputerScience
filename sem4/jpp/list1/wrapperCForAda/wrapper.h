#ifndef _WRAPPER_H_
#define _WRAPPER_H_

extern void adainit(void);
extern void adafinal(void);

typedef struct {
    int x;
    int y;
} DiophantineEquationSolution;

extern unsigned long factorial(unsigned long n);
extern unsigned long factorialRecursive(unsigned long n);

extern unsigned int gcd(unsigned int a, unsigned int b);
extern unsigned int gcdRecursive(unsigned int a, unsigned int b);
extern int gcdI(int a, int b);

extern DiophantineEquationSolution diophantine(int a, int b, int c);
extern DiophantineEquationSolution diophantineRecursive(int a, int b, int c);

#endif // _WRAPPER_H_
