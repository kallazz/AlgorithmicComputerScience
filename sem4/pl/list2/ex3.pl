arc(a, b).
arc(b, a).
arc(b, c).
arc(c, d).

osiagalny(X, Y) :- osiagalny(X, Y, []).

osiagalny(X, X, _).
osiagalny(X, Y, Visited) :-
    arc(X, Z),
    \+ member(Z, Visited),
    osiagalny(Z, Y, [X | Visited]).
