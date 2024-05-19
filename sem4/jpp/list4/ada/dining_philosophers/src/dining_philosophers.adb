with Chopstick;
with Philosopher;

procedure Dining_Philosophers is
   Number_Of_Philosophers : constant := 5;
   Meal_Limit : constant := 3;

   Chopsticks : array (1 .. Number_Of_Philosophers) of aliased Chopstick.Chopstick_Type;

   type Philosopher_Task_Pointer is access Philosopher.Philosopher_Task;
   Philosopher_Task_Pointers : array (1 .. Number_Of_Philosophers) of Philosopher_Task_Pointer;

   Left_Chopstick_Index : Integer;
   Right_Chopstick_Index : Integer;
begin
   for I in 1 .. Number_Of_Philosophers loop
      if I mod 2 = 0 then
         Left_Chopstick_Index := (I mod Number_Of_Philosophers) + 1;
         Right_Chopstick_Index := I;
      else
         Left_Chopstick_Index := I;
         Right_Chopstick_Index := (I mod Number_Of_Philosophers) + 1;
      end if;

      Philosopher_Task_Pointers (I) := new Philosopher.Philosopher_Task (
         I, Chopsticks (Left_Chopstick_Index)'Access, Chopsticks (Right_Chopstick_Index)'Access, Meal_Limit
      );
   end loop;

   for I in 1 .. Number_Of_Philosophers loop
      Philosopher_Task_Pointers (I).Start;
   end loop;
end Dining_Philosophers;
