package Math_Lib is
   type Diophantine_Equation_Solution is record
      X : Integer;
      Y : Integer;
   end record;

   function Factorial(N : Natural) return Natural;
   pragma Export (C, Factorial, "factorial");
   function Factorial_Recursive(N : Natural) return Natural;
   pragma Export (C, Factorial_Recursive, "factorialRecursive");

   function GCD(A, B : Natural) return Natural;
   pragma Export (C, GCD, "gcd");
   function GCD_Recursive(A, B : Natural) return Natural;
   pragma Export (C, GCD_Recursive, "gcdRecursive");
   function GCD_Extended(A, B : Integer; X, Y : out Integer) return Integer;
   function GCD_Extended_Recursive(A, B : Integer; X, Y : out Integer) return Integer;
   function GCD_I(A, B : Integer) return Integer;
   pragma Export (C, GCD_I, "gcdI");

   function Diophantine(A, B, C : Integer) return Diophantine_Equation_Solution;
   pragma Export (C, Diophantine, "diophantine");
   function Diophantine_Recursive(A, B, C : Integer) return Diophantine_Equation_Solution;
   pragma Export (C, Diophantine_Recursive, "diophantineRecursive");
end Math_Lib;
