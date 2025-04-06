with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Random_Seeds; use Random_Seeds;
with Ada.Real_Time; use Ada.Real_Time;

procedure Travelers is

-- Travelers moving on the board

  Nr_Of_Travelers : constant Integer := 15;

  Min_Steps : constant Integer := 10;
  Max_Steps : constant Integer := 100;

  Min_Delay : constant Duration := 0.01;
  Max_Delay : constant Duration := 0.05;

  -- Timeout for deadlock detection
  Deadlock_Timeout : constant Duration := 3.0 * Max_Delay;

-- 2D Board with torus topology

  Board_Width  : constant Integer := 15;
  Board_Height : constant Integer := 15;

-- Timing

  Start_Time : Time := Clock;  -- global starting time

-- Random seeds for the tasks' random number generators
 
  Seeds : Seed_Array_Type(1..Nr_Of_Travelers) := Make_Seeds(Nr_Of_Travelers);

-- Types, procedures and functions

  -- Positions on the board
  type Position_Type is record	
    X: Integer range 0 .. Board_Width - 1; 
    Y: Integer range 0 .. Board_Height - 1; 
  end record;
  
  -- For position equality comparison
  function "=" (Left, Right : Position_Type) return Boolean is
  begin
    return Left.X = Right.X and Left.Y = Right.Y;
  end "=";

  -- elementary steps
  procedure Move_Down(Position: in out Position_Type) is
  begin
    Position.Y := (Position.Y + 1) mod Board_Height;
  end Move_Down;

  procedure Move_Up(Position: in out Position_Type) is
  begin
    Position.Y := (Position.Y + Board_Height - 1) mod Board_Height;
  end Move_Up;

  procedure Move_Right(Position: in out Position_Type) is
  begin
    Position.X := (Position.X + 1) mod Board_Width;
  end Move_Right;

  procedure Move_Left(Position: in out Position_Type) is
  begin
    Position.X := (Position.X + Board_Width - 1) mod Board_Width;
  end Move_Left;

  -- traces of travelers
  type Trace_Type is record 	      
    Time_Stamp: Duration;	      
    Id : Integer;
    Position: Position_Type;      
    Symbol: Character;	      
  end record;	      

  type Trace_Array_type is array(0 .. Max_Steps) of Trace_Type;

  type Traces_Sequence_Type is record
    Last: Integer := -1;
    Trace_Array: Trace_Array_type;
  end record; 


  procedure Print_Trace(Trace : Trace_Type) is
  begin
    Put_Line(
        Duration'Image(Trace.Time_Stamp) & " " &
        Integer'Image(Trace.Id) & " " &
        Integer'Image(Trace.Position.X) & " " &
        Integer'Image(Trace.Position.Y) & " " &
        (Trace.Symbol & "")
      );
  end Print_Trace;

  procedure Print_Traces(Traces : Traces_Sequence_Type) is
  begin
    for I in 0 .. Traces.Last loop
      Print_Trace(Traces.Trace_Array(I));
    end loop;
  end Print_Traces;

  -- task Printer collects and prints reports of traces
  task Printer is
    entry Report(Traces : Traces_Sequence_Type);
  end Printer;
  
  task body Printer is 
    Finished_Travelers : Integer := 0;
  begin
    loop
      select
        accept Report(Traces : Traces_Sequence_Type) do
          Print_Traces(Traces);
          Finished_Travelers := Finished_Travelers + 1;
        end Report;
        exit when Finished_Travelers = Nr_Of_Travelers;
      or
        terminate;
      end select;
    end loop;
  end Printer;

  -- Field occupancy management using protected objects
  protected type Field_Type is
    entry Acquire(ID : Integer);
    procedure Release;
    function Is_Occupied return Boolean;
  private
    Occupied : Boolean := False;
    Occupier_ID : Integer := -1;
  end Field_Type;

  protected body Field_Type is
    entry Acquire(ID : Integer) when not Occupied is
    begin
      Occupied := True;
      Occupier_ID := ID;
    end Acquire;

    procedure Release is
    begin
      Occupied := False;
      Occupier_ID := -1;
    end Release;

    function Is_Occupied return Boolean is
    begin
      return Occupied;
    end Is_Occupied;
  end Field_Type;

  -- Array of protected objects for each field on the board
  type Board_Type is array (0 .. Board_Width - 1, 0 .. Board_Height - 1) of Field_Type;
  Board : Board_Type;

  -- travelers
  type Traveler_Type is record
    Id: Integer;
    Symbol: Character;
    Position: Position_Type;
    Direction: Integer; -- 0=up, 1=down, 2=left, 3=right
  end record;

  task type Traveler_Task_Type is	
    entry Init(Id: Integer; Seed: Integer; Symbol: Character);
    entry Start;
  end Traveler_Task_Type;	

  task body Traveler_Task_Type is
    G : Generator;
    Traveler : Traveler_Type;
    Time_Stamp : Duration;
    Nr_of_Steps: Integer;
    Traces: Traces_Sequence_Type;
    Is_Deadlocked : Boolean := False;

    procedure Store_Trace is
    begin  
      Traces.Last := Traces.Last + 1;
      Traces.Trace_Array(Traces.Last) := ( 
          Time_Stamp => Time_Stamp,
          Id => Traveler.Id,
          Position => Traveler.Position,
          Symbol => Traveler.Symbol
        );
    end Store_Trace;
    
    -- Try to make a step in the specified direction with a non-blocking approach
    procedure Try_Move(Success : out Boolean) is
      New_Position : Position_Type := Traveler.Position;
    begin
      Success := False;
      
      -- Calculate new position
      case Traveler.Direction is
        when 0 =>
          Move_Up(New_Position);
        when 1 =>
          Move_Down(New_Position);
        when 2 =>
          Move_Left(New_Position);
        when 3 =>
          Move_Right(New_Position);
        when others =>
          Put_Line("Invalid direction: " & Integer'Image(Traveler.Direction));
          return;
      end case;
      
      -- Try to acquire the field without blocking
      select
        Board(New_Position.X, New_Position.Y).Acquire(Traveler.Id);
        -- Release the old position
        Board(Traveler.Position.X, Traveler.Position.Y).Release;
        -- Update the traveler's position
        Traveler.Position := New_Position;
        Success := True;
      else
        -- Field is occupied, we continue trying
        Success := False;
      end select;
    end Try_Move;
    
    procedure Make_Step is
      Move_Start_Time : Time := Clock;
      Success : Boolean := False;
    begin
      -- Keep trying to move until success or timeout
      while not Success loop
        -- Try to move in the predetermined direction
        Try_Move(Success);
        
        -- If successful, we're done
        exit when Success;
        
        -- Check if we've been trying for too long (potential deadlock)
        if Clock - Move_Start_Time > To_Time_Span(Deadlock_Timeout) then
          -- We're deadlocked - change symbol to lowercase
          Traveler.Symbol := Character'Val(Character'Pos(Traveler.Symbol) + 32);
          Is_Deadlocked := True;
          exit;
        end if;

        delay Min_Delay + (Max_Delay - Min_Delay) * Duration(Random(G));
      end loop;
    end Make_Step;

  begin
    accept Init(Id: Integer; Seed: Integer; Symbol: Character) do
      Reset(G, Seed); 
      Traveler.Id := Id;
      Traveler.Symbol := Symbol;
      
      -- Set starting position to (i, i) on the diagonal
      Traveler.Position := (X => Id, Y => Id);
      
      -- Try to acquire this position (should always succeed as positions are unique)
      Board(Traveler.Position.X, Traveler.Position.Y).Acquire(Traveler.Id);
      
      -- Choose initial direction based on ID parity
      if Id mod 2 = 0 then
        -- Even ID: vertical movement (up=0 or down=1)
        Traveler.Direction := Integer(Float'Floor(2.0 * Random(G)));
      else
        -- Odd ID: horizontal movement (left=2 or right=3)
        Traveler.Direction := 2 + Integer(Float'Floor(2.0 * Random(G)));
      end if;
      
      -- Store starting position
      Time_Stamp := To_Duration(Clock - Start_Time);
      Store_Trace;
      
      -- Number of steps to be made by the traveler  
      Nr_of_Steps := Min_Steps + Integer(Float(Max_Steps - Min_Steps) * Random(G));
    end Init;
    
    -- wait for initializations of the remaining tasks:
    accept Start do
      null;
    end Start;

    for Step in 1 .. Nr_of_Steps loop
      exit when Is_Deadlocked;
      
      -- Random delay before moving
      delay Min_Delay + (Max_Delay - Min_Delay) * Duration(Random(G));
      
      -- Attempt to move
      Make_Step;
      
      -- Record the new position
      Time_Stamp := To_Duration(Clock - Start_Time);
      Store_Trace;
    end loop;
    
    -- Report results
    Printer.Report(Traces);
  end Traveler_Task_Type;

-- local for main task

  Travel_Tasks: array (0 .. Nr_Of_Travelers-1) of Traveler_Task_Type;
  Symbol : Character := 'A';
begin 
  
  -- Print the line with the parameters needed for display script:
  Put_Line(
      "-1 " &
      Integer'Image(Nr_Of_Travelers) & " " &
      Integer'Image(Board_Width) & " " &
      Integer'Image(Board_Height)      
    );

  -- Init travelers tasks
  for I in Travel_Tasks'Range loop
    Travel_Tasks(I).Init(I, Seeds(I+1), Symbol);
    Symbol := Character'Succ(Symbol);
  end loop;

  -- Start travelers tasks
  for I in Travel_Tasks'Range loop
    Travel_Tasks(I).Start;
  end loop;

end Travelers;