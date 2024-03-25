parzysty(N) :- mod(N, 2) =:= 0.

srodkowy(L, X) :-
    length(L, DLUGOSC),
    \+ parzysty(DLUGOSC),
    append(_, [X | PRAWA], L),
    length(PRAWA, DLUGOSC2),
    DLUGOSC2 =:= DLUGOSC // 2.
