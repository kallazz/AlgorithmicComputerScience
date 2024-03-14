is_divisible(N, D) :- mod(N, D) =:= 0, !.
is_divisible(N, D) :- N > D + 1, is_divisible(N, D + 1).

is_prime(2).
is_prime(N) :- N > 2, \+ is_divisible(N, 2).

prime(LO, HI, N) :-
    between(LO, HI, N),
    is_prime(N).
