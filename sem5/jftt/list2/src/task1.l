%option noyywrap

%{
    int lineCount = 0;
    int wordCount = 0;
%}

%%

^[[:blank:]]*\n  {}
[[:blank:]]+$    {}
^[[:blank:]]+    {}
[[:blank:]]+     { fprintf(yyout, " "); }
[^[:blank:]\n]+  { wordCount++; ECHO; }
\n               { lineCount++; fprintf(yyout, "\n"); }
<<EOF>>          { lineCount++; return 0; }

%%

int main() {
    yyin = fopen("../tests/test1a.txt", "r");
    yyout = fopen("out1.txt", "w");
    yylex();

    printf("Amount of lines: %d\n", lineCount);
    printf("Amount of words: %d\n", wordCount);
}
