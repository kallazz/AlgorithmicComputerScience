with Chopstick;

package Philosopher is
   task type Philosopher_Task (Id : Integer; Left_Chopstick, Right_Chopstick : not null access Chopstick.Chopstick_Type; Meal_Limit : Integer) is
      entry Start;
   end Philosopher_Task;
end Philosopher;
