jednokrotnie(X, L) :-
    select(X, L, L2),
    \+ member(X, L2).

dwukrotnie(X, L) :-
    select(X, L, L2),
    select(X, L2, L3),
    \+ member(X, L3).
