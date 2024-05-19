package body Chopstick is
   protected body Chopstick_Type is
      entry Pick_Up when not Is_Used is
      begin
         Is_Used := True;
      end Pick_Up;

      procedure Put_Down is
      begin
         Is_Used := False;
      end Put_Down;
   end Chopstick_Type;
end Chopstick;
