package Math_Lib is
   type Diophantine_Equation_Solution is record
      X : Integer;
      Y : Integer;
   end record;

   function Factorial(N : Natural) return Natural;
   function Factorial_Recursive(N : Natural) return Natural;

   function GCD(A, B : Natural) return Natural;
   function GCD_Recursive(A, B : Natural) return Natural;
   function GCD_Extended(A, B : Integer; X, Y : out Integer) return Integer;
   function GCD_Extended_Recursive(A, B : Integer; X, Y : out Integer) return Integer;
   function GCD_I(A, B : Integer) return Integer;

   function Solve_Diophantine_Equation(A, B, C : Integer) return Diophantine_Equation_Solution;
   function Solve_Diophantine_Equation_Recursive(A, B, C : Integer) return Diophantine_Equation_Solution;
end Math_Lib;
