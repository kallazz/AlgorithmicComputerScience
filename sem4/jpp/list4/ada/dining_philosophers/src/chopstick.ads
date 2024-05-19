package Chopstick is
   protected type Chopstick_Type is
      entry Pick_Up;
      procedure Put_Down;
   private
      Is_Used : Boolean := False;
   end Chopstick_Type;
end Chopstick;
