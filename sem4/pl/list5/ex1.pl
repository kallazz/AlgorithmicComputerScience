is_whitespace(' ').
is_whitespace('\t').
is_whitespace('\n').
is_whitespace('\r').


% *****************************************************
% ******************** TOKEN TYPES ********************
% *****************************************************

is_key(read).
is_key(write).
is_key(if).
is_key(then).
is_key(else).
is_key(fi).
is_key(while).
is_key(do).
is_key(od).
is_key(and).
is_key(or).
is_key(mod).

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

is_int(String) :-
    atom_chars(String, Chars),
    is_int_chars(Chars).
is_int_chars([]) :- !.
is_int_chars([H|T]) :-
    char_type(H, digit),
    is_int_chars(T).

is_id(String) :-
    atom_chars(String, Chars),
    is_id_chars(Chars).
is_id_chars([]) :- !.
is_id_chars([H|T]) :-
    char_type(H, upper),
    is_id_chars(T).


% ******************************************************
% ******************** TOKENIZATION ********************
% ******************************************************

tokenize(InputStream, Tokens) :-
    get_char(InputStream, Char),
    tokenize(Char, InputStream, Tokens).

tokenize(end_of_file, _, []) :- !.

tokenize(Char, InputStream, Tokens) :-
    is_whitespace(Char),
    get_char(InputStream, NextChar),
    tokenize(NextChar, InputStream, Tokens).

tokenize(Char, InputStream, [TokensHead|TokensTail]) :-
    (
        is_separator(Char) ; Char = ':'
    ),
    get_char(InputStream, SecondChar),
    atom_chars(CombinedChars, [Char, SecondChar]),
    (
        is_separator(CombinedChars) ->
        (
            TokensHead = CombinedChars,
            get_char(InputStream, ThirdChar),
            tokenize(ThirdChar, InputStream, TokensTail)
        )
        ;
        (
            TokensHead = Char,
            tokenize(SecondChar, InputStream, TokensTail)
        )
    ).

tokenize(Char, InputStream, [Word|TokensTail]) :-
    check_char_and_read_word(Char, NextChar, Chars, InputStream),
    atom_chars(Word, Chars),
    tokenize(NextChar, InputStream, TokensTail).


check_char_and_read_word(end_of_file, _, [], _) :- !.
check_char_and_read_word(LastChar, LastChar, [], _) :-
    (
        is_whitespace(LastChar) ; is_separator(LastChar) ; LastChar = ':'
    ),
    !.
check_char_and_read_word(Char, LastChar, [Char|Chars], InputStream) :-
    get_char(InputStream, NextChar),
    check_char_and_read_word(NextChar, LastChar, Chars, InputStream).


% **************************************************************
% ******************** TOKEN CATEGORIZATION ********************
% **************************************************************

categorize_tokens([], []) :- !.

categorize_tokens([TokensHead|TokensTail], [key(TokensHead)|OutputTail]) :-
    is_key(TokensHead),
    categorize_tokens(TokensTail, OutputTail).

categorize_tokens([TokensHead|TokensTail], [sep(TokensHead)|OutputTail]) :-
    is_separator(TokensHead),
    categorize_tokens(TokensTail, OutputTail).

categorize_tokens([TokensHead|TokensTail], [int(TokensHead)|OutputTail]) :-
    is_int(TokensHead),
    categorize_tokens(TokensTail, OutputTail).

categorize_tokens([TokensHead|TokensTail], [id(TokensHead)|OutputTail]) :-
    is_id(TokensHead),
    categorize_tokens(TokensTail, OutputTail).

categorize_tokens([TokensHead|TokensTail], [unknown(TokensHead)|OutputTail]) :-
    categorize_tokens(TokensTail, OutputTail).


% *************************************************
% ******************** SCANNER ********************
% *************************************************

scanner(InputStream, Tokens) :-
    tokenize(InputStream, TokensWithoutCategories),
    categorize_tokens(TokensWithoutCategories, Tokens),
    !.
