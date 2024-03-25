is_order_correct(X, Index) :-
    LowerBound is X - 1,
    HigherBound is 2 * LowerBound,
    between(LowerBound, HigherBound, Index).

is_distance_even(X, L) :-
    nth0(Index0, L, X),
    nth0(Index1, L, X),
    Index0 < Index1,
    is_order_correct(X, Index0),
    mod(Index1 - Index0, 2) =:= 1.

is_list_even(0, _).
is_list_even(N, L) :-
    is_distance_even(N, L),
    N2 is N - 1,
    is_list_even(N2, L).

lista(N, X) :-
    N2 is 2 * N,
	length(X, N2),
    is_list_even(N, X).
