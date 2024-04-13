with Ada.Integer_Text_IO;
use Ada.Integer_Text_IO;

package body Math_Lib is
   function Factorial(N : Natural) return Natural is
      Result : Natural := 1;
   begin
      for I in 1 .. N loop
         Result := Result * I;
      end loop;
      return Result;
   end Factorial;

   function Factorial_Recursive(N : Natural) return Natural is
   begin
      if N <= 1 then
         return 1;
      else
         return N * Factorial_Recursive(N - 1);
      end if;
   end Factorial_Recursive;

   function GCD(A, B : Natural) return Natural is
      Local_A : Natural := A;
      Local_B : Natural := B;
      R : Natural;
   begin
      if Local_B = 0 then
         return Local_A;
      end if;

      while Local_A mod Local_B > 0 loop
         R := Local_A mod Local_B;
         Local_A := Local_B;
         Local_B := R;
      end loop;

      return Local_B;
   end GCD;

   function GCD_I(A, B : Integer) return Integer is
      Local_A : Integer := A;
      Local_B : Integer := B;
      R : Integer;
   begin
      if Local_B = 0 then
         return Local_A;
      end if;

      while Local_A mod Local_B > 0 loop
         R := Local_A mod Local_B;
         Local_A := Local_B;
         Local_B := R;
      end loop;

      return Local_B;
   end GCD_I;

   function GCD_Recursive(A, B : Natural) return Natural is
   begin
      if B /= 0 then
         return GCD_Recursive(B, A mod B);
      end if;
      return A;
   end GCD_Recursive;

   function GCD_Extended(A, B : Integer; X, Y : out Integer) return Integer is
      Local_A : Integer := A;
      Local_B : Natural := B;
      X_Prev : Integer := 1;
      Y_Prev : Integer := 0;
      X_Curr : Integer := 0;
      Y_Curr : Integer := 1;
      Quotient : Integer;
      Temp : Integer;
   begin
      while Local_B /= 0 loop
         Quotient := Local_A / Local_B;

         Temp := Local_B;
         Local_B := Local_A mod Local_B;
         Local_A := Temp;

         Temp := X_Prev - Quotient * X_Curr;
         X_Prev := X_Curr;
         X_Curr := Temp;
         Temp := Y_Prev - Quotient * Y_Curr;
         Y_Prev := Y_Curr;
         Y_Curr := Temp;
      end loop;

      X := X_Prev;
      Y := Y_Prev;

      return Local_A;
   end GCD_Extended;

   function GCD_Extended_Recursive(A, B : Integer; X, Y : out Integer) return Integer is
   begin
      if A = 0 then
         X := 0;
         Y := 1;
         return B;
      end if;

      declare
         X1 : Integer;
         Y1 : Integer;
         GCD_Result : Integer;
      begin
         GCD_Result := GCD_Extended_Recursive(B mod A, A, X1, Y1);
         X := Y1 - (B / A) * X1;
         Y := X1;
         return GCD_Result;
      end;
   end GCD_Extended_Recursive;

   function Solve_Diophantine_Equation(A, B, C : Integer) return Diophantine_Equation_Solution is
      Solution : Diophantine_Equation_Solution := (0, 0);
      GCD_Result : Integer;
      X_Solution, Y_Solution : Integer;
   begin
      if A = 0 and B = 0 then
         return Solution;
      end if;

      GCD_Result := GCD_Extended(Abs(A), Abs(B), X_Solution, Y_Solution);

      if C mod GCD_Result /= 0 then
         return Solution;
      end if;

      X_Solution := X_Solution * (C / GCD_Result);
      Y_Solution := Y_Solution * (C / GCD_Result);
      if A < 0 then
         X_Solution := -X_Solution;
      end if;
      if B < 0 then
         Y_Solution := -Y_Solution;
      end if;

      Solution.X := X_Solution;
      Solution.Y := Y_Solution;

      return Solution;
   end Solve_Diophantine_Equation;

   function Solve_Diophantine_Equation_Recursive(A, B, C : Integer) return Diophantine_Equation_Solution is
      Solution : Diophantine_Equation_Solution := (0, 0);
      GCD_Result : Integer;
      X_Solution, Y_Solution : Integer;
   begin
      if A = 0 and B = 0 then
         return Solution;
      end if;

      GCD_Result := GCD_Extended_Recursive(Abs(A), Abs(B), X_Solution, Y_Solution);

      if C mod GCD_Result /= 0 then
         return Solution;
      end if;

      X_Solution := X_Solution * (C / GCD_Result);
      Y_Solution := Y_Solution * (C / GCD_Result);
      if A < 0 then
         X_Solution := -X_Solution;
      end if;
      if B < 0 then
         Y_Solution := -Y_Solution;
      end if;

      Solution.X := X_Solution;
      Solution.Y := Y_Solution;

      return Solution;
   end Solve_Diophantine_Equation_Recursive;

end Math_Lib;
