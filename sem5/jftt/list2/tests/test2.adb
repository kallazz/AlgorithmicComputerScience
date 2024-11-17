with Ada.Text_IO; use Ada.Text_IO;

-- Test2 Main File
procedure Test2 is
begin -- Preserve things befor this
    Put_Line ("=== Ada ===");
    --This will be removed
    -- With space too
    Put_Line ("--- Not a comment ---");
    --- Three work as well
    -- -- As does commenting twice

    Put_Line ("""-- Not comment either");

    Put_Line (
        "Result:" & Integer'Image(2--1)
    ));
end Test2;