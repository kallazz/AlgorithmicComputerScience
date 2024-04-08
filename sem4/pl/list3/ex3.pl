even_permutation(Xs, Ys) :-
    permutation(Xs, Ys),
    count_inversions(Ys, InversionCount),
    is_even(InversionCount).


odd_permutation(Xs, Ys) :-
    permutation(Xs, Ys),
    count_inversions(Ys, InversionCount),
    \+ is_even(InversionCount).


count_inversions(P, InversionCount) :-
    count_inversions(P, 0, InversionCount).
count_inversions([], InversionCount, InversionCount).
count_inversions([H|T], InversionCount, Result) :-
    count_smaller_elements(T, H, SmallerElementsCount),
    InversionCount1 is InversionCount + SmallerElementsCount,
    count_inversions(T, InversionCount1, Result).


count_smaller_elements(L, X, SmallerElementsCount) :-
    count_smaller_elements(L, X, 0, SmallerElementsCount).
count_smaller_elements([], _, SmallerElementsCount, SmallerElementsCount).
count_smaller_elements([H|T], X, SmallerElementsCount, Result) :-
    (X > H -> SmallerElementsCount1 is SmallerElementsCount + 1 ; SmallerElementsCount1 is SmallerElementsCount),
    count_smaller_elements(T, X, SmallerElementsCount1, Result).


is_even(N) :-
    mod(N, 2) =:= 0.
