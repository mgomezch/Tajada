%{
int yylex(void);
void yyerror(char const *);
%}

%define    api.pure
%defines   "parser.hpp
%language  "C++"
%locations
%verbose

%tokens

%%

tajada : dulces decl_funciones variables def_funciones main
       ;

dulces : IDENT ES DULCE DE IDENT STOP

%%

