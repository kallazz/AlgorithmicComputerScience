%option noyywrap

%{
    #include "parser.tab.hpp"
    #include <string.h>
%}

%%

^#(.|\\\n)*\n   { /* Ignore comments */ }
\\\n            { /* Ignore line continuation */ }
[[:blank:]]+    { /* Ignore whitespace */ }
\n              { return EOL; }
[[:digit:]]+    { yylval = atoi(yytext); return NUM; }
"+"             { return ADD; }
"-"             { return SUB; }
"*"             { return MUL; }
"/"             { return DIV; }
"^"             { return POW; }
"("             { return LPAREN; }
")"             { return RPAREN; }
.               { return INVALID; }

%%
