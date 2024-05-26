% 1.
merge(List1, [], List1).
merge([], List2, List2).
merge([X|List1], [Y|List2], [X|MergedList]) :-
    X =< Y,
    merge(List1, [Y|List2], MergedList).
merge([X|List1], [Y|List2], [Y|MergedList]) :-
    X > Y,
    merge([X|List1], List2, MergedList).

splitList(List, FirstHalf, SecondHalf) :-
    append(FirstHalf, SecondHalf, List),
    length(List, ListLength),
    HalfListLength is ListLength div 2,
    (   ListLength mod 2 =:= 0
    ->  LeftLength = HalfListLength
    ;   LeftLength is HalfListLength + 1
    ),
    length(FirstHalf, LeftLength),
    length(SecondHalf, HalfListLength).

mergeSort([], []).
mergeSort([X], [X]).
mergeSort(UnsortedList, SortedList) :-
    splitList(UnsortedList, FirstHalf, SecondHalf),
    mergeSort(FirstHalf, SortedFirstHalf),
    mergeSort(SecondHalf, SortedSecondHalf),
    merge(SortedFirstHalf, SortedSecondHalf, SortedList), !.

% 2.
gcdExtended(0, B, B, 0, 1).
gcdExtended(A, B, G, X, Y) :-
    A \= 0,
    A1 is B mod A,
    gcdExtended(A1, A, G, X1, Y1),
    X is Y1 - (B div A) * X1,
    Y is X1.

diophantine(A, B, X0, Y0, G) :-
    gcdExtended(abs(A), abs(B), G, X, Y),
    (A >= 0 -> X0 is X ; X0 is -X),
    (B >= 0 -> Y0 is Y ; Y0 is -Y).

% 3.
primeFactors(N, Factors) :-
    primeFactors(N, 2, Factors).

primeFactors(1, _, []).
primeFactors(N, Divisor, Factors) :-
    0 is N mod Divisor,
    N1 is N div Divisor,
    primeFactors(N1, Divisor, Factors1),
    Factors = [Divisor|Factors1].
primeFactors(N, Divisor, Factors) :-
    \+ (0 is N mod Divisor),
    Divisor1 is Divisor + 1,
    Divisor1 =< N,
    primeFactors(N, Divisor1, Factors).

% 4.
totient(N, Phi) :-
    primeFactors(N, Factors),
    sort(Factors, UniqueFactors),
    primeFactorsTotient(UniqueFactors, N, FloatPhi),
    Phi is floor(FloatPhi).

primeFactorsTotient([], Phi, Phi).
primeFactorsTotient([Factor|Factors], CurrentPhi, FinalPhi) :-
    totientFactor(Factor, CurrentPhi, NextPhi),
    primeFactorsTotient(Factors, NextPhi, FinalPhi).

totientFactor(Factor, CurrentPhi, NextPhi) :-
    NextPhi is CurrentPhi * (1 - (1 / Factor)).

% 5.
isDivisible(N, D) :-
    0 is N mod D, !.
isDivisible(N, D) :-
    D =< (sqrt(N) - 1),
    isDivisible(N, D + 1).

isPrime(2) :- !.
isPrime(N) :-
    N > 2,
    \+ isDivisible(N, 2).

primes(N, Primes) :-
    findall(X, (between(2, N, X), isPrime(X)), Primes).
