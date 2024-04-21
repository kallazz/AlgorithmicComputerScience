wyrazenie(Lista, Wartosc, Wyrazenie) :-
    wyrazenie(Lista, Wyrazenie),
    Wartosc is Wyrazenie, !.

% gdy lista ma tylko jeden element, to wyrazenie to ten element
wyrazenie([Liczba], Liczba).

% przeprowadzamy operacje arytmetyczne na wszystkich liczbach w liscie
wyrazenie(Lista, Wyrazenie) :-
    append(L1, L2, Lista),
    \+ length(L1, 0),
    \+ length(L2, 0),
    wyrazenie(L1, Wynik1),
    wyrazenie(L2, Wynik2),
    dzialanie(Wynik1, Wynik2, Wyrazenie).

dzialanie(Liczba1, Liczba2, Liczba1 + Liczba2).
dzialanie(Liczba1, Liczba2, Liczba1 - Liczba2).
dzialanie(Liczba1, Liczba2, Liczba1 * Liczba2).
dzialanie(Liczba1, Liczba2, Dzielenie) :-
    Liczba2 =\= 0,
    Dzielenie is Liczba1 / Liczba2.
