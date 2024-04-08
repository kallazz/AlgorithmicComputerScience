max_sum(L, S) :-
    max_sum(L, 0, 0, S).

max_sum([], _, MaxSum, MaxSum).
max_sum([H|T], CurrentSum, MaxSum, FinalSum) :-
    NewSum is max(CurrentSum + H, 0),
    NewMaxSum is max(MaxSum, NewSum),
    max_sum(T, NewSum, NewMaxSum, FinalSum).
