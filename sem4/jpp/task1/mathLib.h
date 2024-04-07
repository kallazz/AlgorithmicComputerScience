#ifndef _MATH_LIB_H_
#define _MATH_LIB_H_

struct diophantineEquationResult {
    int x;
    int y;
};

extern long factorial(long n);
extern int gcd(int a, int b);
extern int diophantineEquation(int a, int b, int c);

#endif // _MATH_LIB_H_