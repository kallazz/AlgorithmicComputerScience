with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Ada.Text_IO; use Ada.Text_IO;

package body Philosopher is
   task body Philosopher_Task is
      Rng : Generator;
      Delay_Factor : constant := 0.2;
   begin
      accept Start;
      Reset (Rng);
      for I in 1 .. Meal_Limit loop
         Put_Line ("Philosopher" & Integer'Image(Id) & " is thinking.");
         delay Duration (Random (Rng) * Delay_Factor);
         Put_Line ("Philosopher" & Integer'Image(Id) & " stopped thinking.");

         Left_Chopstick.Pick_Up;
         Right_Chopstick.Pick_Up;

         Put_Line ("Philosopher" & Integer'Image(Id) & " is eating.");
         delay Duration (Random (Rng) * Delay_Factor);
         Put_Line ("Philosopher" & Integer'Image(Id) & " stopped eating.");

         Left_Chopstick.Put_Down;
         Right_Chopstick.Put_Down;
      end loop;
   end Philosopher_Task;
end Philosopher;
