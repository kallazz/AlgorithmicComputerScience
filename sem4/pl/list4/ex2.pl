% Dom to [Numer, Kolor, Mieszkaniec, Zwierze, Picie, Palenie]
rybki(Kto) :-
    domy(D),
    member([_, _, Kto, rybki, _, _], D), !.

domy(Domy) :-
    Domy = [[1, _, _, _, _, _], [2, _, _, _, _, _], [3, _, _, _, _, _], [4, _, _, _, _, _], [5, _, _, _, _, _]],
    % 1. Norweg zamieszkuje pierwszy dom
    member([1, _, norweg, _, _, _], Domy),
    % 2. Anglik mieszka w czerwonym domu.
    member([_, czerwony, anglik, _, _, _], Domy),
    % 3. Zielony dom znajduje się bezpośrednio po lewej stronie domu białego.
    po_lewej([_, zielony, _, _, _, _], [_, bialy, _, _, _, _], Domy),
    % 4. Duńczyk pija herbatkę.
    member([_, _, dunczyk, _, herbatka, _], Domy),
    % 5. Palacz papierosów light mieszka obok hodowcy kotów.
    obok([_, _, _, _, _, light], [_, _, _, koty, _, _], Domy),
    % 6. Mieszkaniec żółtego domu pali cygara.
    member([_, zolty, _, _, _, cygara], Domy),
    % 7. Niemiec pali fajkę.
    member([_, _, niemiec, _, _, fajka], Domy),
    % 8. Mieszkaniec środkowego domu pija mleko.
    member([3, _, _, _, mleko, _], Domy),
    % 9. Palacz papierosów light ma sąsiada, który pija wodę.
    obok([_, _, _, _, _, light], [_, _, _, _, woda, _], Domy),
    % 10. Palacz papierosów bez filtra hoduje ptaki.
    member([_, _, _, ptaki, _, bez_filtra], Domy),
    % 11. Szwed hoduje psy.
    member([_, _, szwed, psy, _, _], Domy),
    % 12. Norweg mieszka obok niebieskiego domu.
    obok([_, _, norweg, _, _, _], [_, niebieski, _, _, _, _], Domy),
    % 13. Hodowca koni mieszka obok żółtego domu.
    obok([_, _, _, konie, _, _], [_, zolty, _, _, _, _], Domy),
    % 14. Palacz mentolowych pija piwo.
    member([_, _, _, _, piwo, mentolowe], Domy),
    % 15. W zielonym domu pija się kawę.
    member([_, zielony, _, _, kawa, _], Domy).


po_lewej(LewyDom, PrawyDom, [LewyDom, PrawyDom | _]).
po_lewej(LewyDom, PrawyDom, [_ | Domy]) :-
    po_lewej(LewyDom, PrawyDom, Domy).

obok(Dom1, Dom2, [Dom1, Dom2 | _]).
obok(Dom1, Dom2, [Dom2, Dom1 | _]).
obok(Dom1, Dom2, [_ | Domy]) :-
    obok(Dom1, Dom2, Domy).
