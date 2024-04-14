with Ada.Text_IO; use Ada.Text_IO;
with Ada.Assertions; use Ada.Assertions;
with Interfaces.C; use Interfaces.C;
with Wrapper;

procedure Test_Wrapper is
   -- Factorial
   procedure Test_Factorial is
      Expected_Results : constant array(0 .. 10) of unsigned_long := (1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800);
   begin
      New_Line;
      Put_Line("************ FACTORIAL ************");
      Put_Line("Non-recursive");
      for Input in Expected_Results'Range loop
         Put_Line("Input: " & Integer'Image(Input));
         Assert (Wrapper.Factorial(unsigned_long(Input)) = Expected_Results(Input));
      end loop;

      New_Line;
      Put_Line("Recursive");
      for Input in Expected_Results'Range loop
         Put_Line("Input: " & Integer'Image(Input));
         Assert (Wrapper.Factorial_Recursive(unsigned_long(Input)) = Expected_Results(Input));
      end loop;
   end Test_Factorial;

   -- GCD
   procedure Test_GCD is
      Inputs : constant array(0 .. 6, 0 .. 1) of unsigned := ((0, 17), (17, 0), (3, 7), (10, 6), (15, 5), (24, 18), (75, 100));
      Expected_Results : constant array(0 .. 6) of unsigned := (17, 17, 1, 2, 5, 6, 25);
   begin
      New_Line;
      Put_Line("*************** GCD ***************");
      Put_Line("Non-recursive");
      for I in Inputs'Range loop
         Put_Line("Input: " & unsigned'Image(Inputs(I, 0)) & " " & unsigned'Image(Inputs(I, 1)));
         Assert (Wrapper.GCD(Inputs(I, 0), Inputs(I, 1)) = Expected_Results(I));
      end loop;

      New_Line;
      Put_Line("Recursive");
      for I in Inputs'Range loop
         Put_Line("Input: " & unsigned'Image(Inputs(I, 0)) & " " & unsigned'Image(Inputs(I, 1)));
         Assert (Wrapper.GCD_Recursive(Inputs(I, 0), Inputs(I, 1)) = Expected_Results(I));
      end loop;

   end Test_GCD;

    -- Diophantine
    procedure Validate_Result(A, B, C : int; Solution : Wrapper.Diophantine_Equation_Solution) is
    begin
        if Solution.X = 0 and Solution.Y = 0 then
            if not (A = 0 and B = 0) then
                Assert (C mod Wrapper.GCD_I(A, B) /= 0);
            end if;
        else
            Assert (A * Solution.X + B * Solution.Y = C);
        end if;
    end Validate_Result;

    procedure Test_Diophantine is
        Inputs : constant array(0 .. 15, 0 .. 2) of int :=
            ((0, 0, 0), (0, 0, 5), (5, 0, 5), (0, 5, 5), (2, 4, 5), (6, -9, 29), (6, -9, 30),
            (-9, 6, 30), (2, -3, 10), (3, 2, 10), (4, 7, 19), (-6, -9, 10), (87, -64, 3),
            (137, 173, 99), (16, 7, 15), (195, 42, 12));
        A : int;
        B : int;
        C : int;
    begin
        New_Line;
        Put_Line("*********** DIOPHANTINE ***********");
        Put_Line("Non-recursive");
        for I in Inputs'Range loop
            A := Inputs(I, 0);
            B := Inputs(I, 1);
            C := Inputs(I, 2);
            Put_Line("Input: a =" & int'Image(A) & " b =" & int'Image(B) & " c =" & int'Image(C));
            declare
                Result : Wrapper.Diophantine_Equation_Solution;
            begin
                Result := Wrapper.Diophantine(A, B, C);
                Validate_Result(A, B, C, Result);
            end;
        end loop;

        New_Line;
        Put_Line("Recursive");
        for I in Inputs'Range loop
            A := Inputs(I, 0);
            B := Inputs(I, 1);
            C := Inputs(I, 2);
            Put_Line("Input: a =" & int'Image(A) & " b =" & int'Image(B) & " c =" & int'Image(C));
            declare
                Result : Wrapper.Diophantine_Equation_Solution;
            begin
                Result := Wrapper.Diophantine_Recursive(A, B, C);
                Validate_Result(A, B, C, Result);
            end;
        end loop;


    end Test_Diophantine;


begin
   Test_Factorial;
   Test_GCD;
   Test_Diophantine;
   New_Line;
   Put("All tests passed!");
end Test_Wrapper;
