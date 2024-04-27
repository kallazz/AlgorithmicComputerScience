is_separator(';').
is_separator('+').
is_separator('-').
is_separator('*').
is_separator('/').
is_separator('(').
is_separator(')').
is_separator('<').
is_separator('>').
is_separator('=<').
is_separator('>=').
is_separator(':=').
is_separator('=').
is_separator('/=').

is_whitespace(' ').
is_whitespace('\t').
is_whitespace('\n').

scanner() :-
    open('ex1.prog', read, Str),
    read_word(Str,House1),
    read_word(Str,House2),
    read_word(Str,House3),
    read_word(Str,House4),
    close(Str),
    write([House1,House2,House3,House4]),  nl.

read_word(InputStream, Word) :-
    get_char(InputStream, Char),
    check_char_and_read_rest(Char, Chars, InputStream),
    atom_chars(Word, Chars).

check_char_and_read_rest(end_of_file, [], _) :- !.
check_char_and_read_rest('\t', [], _) :- !. % tab
check_char_and_read_rest('\n', [], _) :- !. % new line
check_char_and_read_rest(' ', [], _) :- !. % space
check_char_and_read_rest(Char, Chars, InputStream) :-
    is_separator(Char),
    \+ check_if_combined_separator(Char, InputStream),
    Chars = [Char, Chars],
    !.
check_char_and_read_rest(Char, [Char|NextChar], InputStream) :-
    is_separator(Char),
    check_if_combined_separator(Char, InputStream),
    get_char(NextChar),
    !.
check_char_and_read_rest(Char, [Char|NextChar], InputStream) :-
    Char = ':',
    check_if_combined_separator(Char, InputStream),
    get_char(NextChar),
    !.
% otherwise read the next char
check_char_and_read_rest(Char, [Char|Chars], InputStream) :-
    get_char(InputStream, NextChar),
    check_char_and_read_rest(NextChar, Chars, InputStream).

check_if_combined_separator(Char, InputStream) :-
    peek_char(InputStream, NextChar),
    atom_chars(CombinedChars, [Char, NextChar]),
    is_separator(CombinedChars).
