%{
int yylex(void);
void yyerror(char const *);
%}

%locations
%define api.pure
%defines parser.hpp
%language C++
%verbose

%tokens

%%

%%

