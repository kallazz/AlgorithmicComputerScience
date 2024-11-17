%option noyywrap

%{
    #include <stdbool.h>

    bool shouldKeepDocs = false;
%}

INCLUDE #include.*$
QUOTES \"[^\"]*\"

DOC_COMMENT \/\/(\/|!)(.|\\\n)*$
MULTILINE_DOC_COMMENT \/\*(\*|!)([^/]|[^*]\/)*\*\/

COMMENT \/\/(.|\\\n)*$
MULTILINE_COMMENT \/\*([^/]|[^*]\/)*\*\/

%%

{INCLUDE}                { ECHO; }
{QUOTES}                 { ECHO; }

{DOC_COMMENT}            { if (shouldKeepDocs) ECHO; else fprintf(yyout, " "); }
{MULTILINE_DOC_COMMENT}  { if (shouldKeepDocs) ECHO; else fprintf(yyout, " "); }

{COMMENT}                { fprintf(yyout, " "); }
{MULTILINE_COMMENT}      { fprintf(yyout, " "); }

%%

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "--keep-docs") == 0) {
        shouldKeepDocs = true;
    }

    yyin = fopen("../tests/test3.cpp", "r");
    yyout = fopen("out3.cpp", "w");
    yylex();
}
