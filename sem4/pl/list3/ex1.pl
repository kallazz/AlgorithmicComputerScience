wariancja(L, D) :-
    mean(L, M),
    maplist(subtract_element(M), L, L2),
    maplist(square_element, L2, L3),
    sum_list(L3, Sum),
    length(L, N),
    D is Sum / N.

mean(L, M) :- 
    length(L, Dlugosc),
    sum_list(L, Sum),
    M is Sum / Dlugosc.

subtract_element(N, Element, Result) :-
    Result is Element - N.

square_element(Element, Result) :-
    Result is Element * Element.
