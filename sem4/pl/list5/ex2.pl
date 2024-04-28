
% code from list 4 solving the N-Queens Problem:
queens(N, P) :-
	numlist(1, N, L),
	perm(L, P),
	good(P).

perm([], []).
perm(L1, [X | L3]) :-
	select(X, L1, L2),
	perm(L2, L3).

good(X) :-
	\+ bad(X).

bad(X) :-
	append(_, [Wi | L1], X),
	append(L2, [Wj | _], L1),
	length(L2, K),
	abs(Wi - Wj) =:= K + 1.


% *******************************************************
% ******************** LINE PRINTING ********************
% *******************************************************

print_line(CurrentRowIndex, MaxIndex) :-
    CurrentRowIndex >= MaxIndex,
    write('+-----+'),
    !.

print_line(CurrentRowIndex, MaxIndex) :-
    write('+-----'),
    print_line(CurrentRowIndex + 1, MaxIndex).


% ****************************************************************
% ******************** INNER SEGMENT PRINTING ********************
% ****************************************************************

print_inner_segment_black(CurrentRowIndex, MaxIndex, [QueenPosition|_], Level) :-
    CurrentRowIndex >= MaxIndex,
    (
        Level =:= QueenPosition ->
        write('|:###:|') ; write('|:::::|')
    ),
    !.

print_inner_segment_black(CurrentRowIndex, MaxIndex, [QueenPosition|Rest], Level) :-
    (
        Level =:= QueenPosition ->
        write('|:###:') ; write('|:::::')
    ),
    print_inner_segment_white(CurrentRowIndex + 1, MaxIndex, Rest, Level).

print_inner_segment_white(CurrentRowIndex, MaxIndex, [QueenPosition|_], Level) :-
    CurrentRowIndex >= MaxIndex,
    (
        Level =:= QueenPosition ->
        write('| ### |') ; write('|     |')
    ),
    !.

print_inner_segment_white(CurrentRowIndex, MaxIndex, [QueenPosition|Rest], Level) :-
    (
        Level =:= QueenPosition ->
        write('| ### ') ; write('|     ')
    ),
    print_inner_segment_black(CurrentRowIndex + 1, MaxIndex, Rest, Level).


% ******************************************************
% ******************** ROW PRINTING ********************
% ******************************************************

print_rows_black(CurrentRowIndex, BoardSize, _) :-
    CurrentRowIndex > BoardSize,
    print_line(1, BoardSize), nl,
    !.

print_rows_black(CurrentRowIndex, BoardSize, QueenPositions) :-
    print_line(1, BoardSize), nl,
    print_inner_segment_black(1, BoardSize, QueenPositions, BoardSize - CurrentRowIndex + 1), nl,
    print_inner_segment_black(1, BoardSize, QueenPositions, BoardSize - CurrentRowIndex + 1), nl,
    print_rows_white(CurrentRowIndex + 1, BoardSize, QueenPositions).

print_rows_white(CurrentRowIndex, BoardSize, _) :-
    CurrentRowIndex > BoardSize,
    print_line(1, BoardSize), nl,
    !.

print_rows_white(CurrentRowIndex, BoardSize, QueenPositions) :-
    print_line(1, BoardSize), nl,
    print_inner_segment_white(1, BoardSize, QueenPositions, BoardSize - CurrentRowIndex + 1), nl,
    print_inner_segment_white(1, BoardSize, QueenPositions, BoardSize - CurrentRowIndex + 1), nl,
    print_rows_black(CurrentRowIndex + 1, BoardSize, QueenPositions).


% ********************************************************
% ******************** BOARD PRINTING ********************
% ********************************************************

board(QueenPositions) :-
    length(QueenPositions, BoardSize),
    (
        BoardSize mod 2 =:= 0 ->
        print_rows_white(1, BoardSize, QueenPositions) ; print_rows_black(1, BoardSize, QueenPositions)
    ),
    !.
