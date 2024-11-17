%option noyywrap

%{
%}

%%

\"[^\"]*\"  { ECHO; }
--.*        {}

%%

int main() {
    yyin = fopen("../tests/test2.adb", "r");
    yyout = fopen("out2.adb", "w");
    yylex();
}
