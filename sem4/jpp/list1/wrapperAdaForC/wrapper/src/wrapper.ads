with Interfaces.C; use Interfaces.C;

package Wrapper is

   type Diophantine_Equation_Solution is record
      x : int;
      y : int;
   end record;

   function Factorial(N : unsigned_long) return unsigned_long;
   pragma Import(C, Factorial, "factorial");
   function Factorial_Recursive(N : unsigned_long) return unsigned_long;
   pragma Import(C, Factorial_Recursive, "factorialRecursive");

   function GCD(A, B : unsigned) return unsigned;
   pragma Import(C, GCD, "gcd");
   function GCD_Recursive(A, B : unsigned) return unsigned;
   pragma Import(C, GCD_Recursive, "gcdRecursive");
   function GCD_I(A, B : int) return int;
   pragma Import(C, GCD_I, "gcdI");

   function Diophantine(A, B, C : int) return Diophantine_Equation_Solution;
   pragma Import(C, Diophantine, "diophantine");
   function Diophantine_Recursive(A, B, C : int) return Diophantine_Equation_Solution;
   pragma Import(C, Diophantine_Recursive, "diophantineRecursive");

end Wrapper;
