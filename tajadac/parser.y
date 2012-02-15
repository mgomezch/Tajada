/* Para GNU Bison */

%require "2.5"

%language "C++"
%define namespace "Tajada::yy"

%debug
%defines
%error-verbose
%locations
%verbose



//%name-prefix "Tajada::lex::yy"

%code {
        namespace Tajada {
                namespace lex {
#undef yylex
                        int yylex(Tajada::yy::parser::semantic_type * s, Tajada::yy::parser::location_type * l, Tajada::lex::Scanner * state);
#define yylex Tajada::lex::yylex
                }
        }
}



%code requires {
        namespace Tajada {
                namespace lex {
                        struct Scanner;
                }
        }
}

%parse-param { Tajada::lex::Scanner * scanner }
%lex-param   { Tajada::lex::Scanner * scanner }



%code requires { #include "scope.hh" }
%parse-param { Tajada::Scope * scope }



%nonassoc CALL
%left EXPR_LIST_SEP
%nonassoc OP_EQ OP_NEQ
%left OP_PLUS OP_MINUS
%left OP_MULT OP_DIV OP_MOD
%nonassoc TUPLE_ARROW
%nonassoc ARRAY_ACCESS_OP
%nonassoc PAREN_CL

%right ELSE



%token_data
%token END 0 "fin del documento"



/* %type <list> toplevels structure_typespecs tuple_elems blocklevels */

%union { Tajada::AST::Expression * expr; }
%type <expr> expr

%union { Tajada::AST::Literal::Integer * intlit; }
%type <intlit> intlit

%union { std::tuple<Tajada::AST::Expression *, std::string *> * tuple_elem; }
%type <tuple_elem> tuple_elem

%union { std::list<std::tuple<Tajada::AST::Expression *, std::string *> *> * tuple_elems; }
%type <tuple_elems> tuple_elems

/* %type <yarrst> tajada toplevel func_spec overload_spec var_def typespec structure_typespec expr operator tuple_elem block blocklevel stmt body */

%code requires { #include "ast.hh" }
%start tajada



%%



/* §3p1 */
tajada
: toplevels block
;

/* §3p1 */
toplevels
: toplevels toplevel
|
;



/* §3p1 */
toplevel
: var_def

/* §3.1.1p4 */
| IDENT[identificador] ES DULCE DE typespec[tipo] STMT_END

/* §3.1.2p6 */
| func_spec STMT_END

/* §3.1.3p6 */
| overload_spec STMT_END

/* §3.2.2p1 */
| func_spec block

/* §3.2.3p1 */
| overload_spec block

;



/* §3.1.2p5,6 */
func_spec
: IDENT[nombre] ES UN PLATO DE typespec[dominio] IDENT[nombre_dominio] CON SALSA DE typespec[rango]
| IDENT[nombre] ES UN PLATO DE typespec[dominio]                       CON SALSA DE typespec[rango]
;

/* §3.1.3p5,6 */
overload_spec
: HAY UN CUBIERTO operator PARA typespec[dominio] Y SALSA DE typespec[rango]
;

/* §3.2.1p4 */
var_def
: IDENT[nombre] ES typespec[tipo] STMT_END
;



typespec

/* §3.1.1p5 */
: IDENT

/* §2.1.1p5 */
| CAFE

/* §2.1.2p3 */
| CARAOTA

/* §2.1.3p3 */
| QUESO

/* §2.1.4p3 */
| PAPELON

/* §2.2p7 */
| AREPA VIUDA

/* §2.2p8 */
| AREPA DE typespec

/* §2.2p11 */
| AREPA CON structure_typespecs Y typespec

/* §2.3p6 */
| CACHAPA CON structure_typespecs O typespec

/* §2.4p3 */
| ARROZ CON typespec

/* §2.4p4 */
| intlit TAZAS DE ARROZ CON typespec

;



/* §2.2p11, §2.3p6 */
structure_typespecs
: structure_typespecs LIST_SEP structure_typespec
| structure_typespec
;

structure_typespec
: typespec IDENT
| typespec
;



expr[lhs]

/* §3.4.1.1p1 */
: LIT_STR[token]
{ $$ = new Tajada::AST::Literal::String($[token]); }

/* §3.4.1.1p2 */
| TETERO
{ $$ = new Tajada::AST::Literal::True(); }

/* §3.4.1.1p2 */
| NEGRITO
{ $$ = new Tajada::AST::Literal::False(); }

/* §3.4.1.1p3 */
| LIT_CHR[token]
{ $$ = new Tajada::AST::Literal::Character($[token]); }

/* §3.4.1.1p4 */
| intlit

/* §3.4.1.1p5, §2.1.4p4 */
| LIT_INT[integer] FLOAT_SEP LIT_INT[fractional]
{ $$ = new Tajada::AST::Literal::Float($[integer], $[fractional]); }

/* §3.4.1.2p4 */
| TUPLE_OP TUPLE_CL
{ $$ = new Tajada::AST::Literal::Tuple(); }

/* §3.4.1.2p4 */
| TUPLE_OP tuple_elems TUPLE_CL
{ $$ = new Tajada::AST::Literal::Tuple($[tuple_elems]); }

/* TODO: arreglar el peo del pasaje por referenca */

/* §3.4.2p5 */
| IDENT CALL expr

/* TODO: operadores unarios */

/* §3.4.3.2l1.1 */
| expr[l] OP_MINUS expr[r]
| PAREN_OP OP_MINUS PAREN_CL expr[l] expr[r]

/* §3.4.3.2l1.2 */
| expr[l] OP_PLUS expr[r]
| PAREN_OP OP_PLUS PAREN_CL expr[l] expr[r]

/* §3.4.3.2l1.3 */
| expr[l] OP_MULT expr[r]
| PAREN_OP OP_MULT PAREN_CL expr[l] expr[r]

/* §3.4.3.2l1.4 */
| expr[l] OP_DIV expr[r]
| PAREN_OP OP_DIV PAREN_CL expr[l] expr[r]

/* §3.4.3.2l1.5 */
| expr[l] OP_MOD expr[r]
| PAREN_OP OP_MOD PAREN_CL expr[l] expr[r]

/* §3.4.3.2l1.6 */
| expr[l] OP_EQ expr[r]
| PAREN_OP OP_EQ PAREN_CL expr[l] expr[r]

/* §3.4.3.2l1.7 */
| expr[l] OP_NEQ expr[r]
| PAREN_OP OP_NEQ PAREN_CL expr[l] expr[r]

/* §3.4.4p2 */
| IDENT

/* §3.4.5p3 */
| PAREN_OP expr[in] PAREN_CL
{ $$ = $[in]; }

/* §3.4.5p5 */
| expr[source] TUPLE_ARROW intlit[field]
{
        auto tp = dynamic_cast<Tajada::Type::Tuple *>($[source]->type);
        if (tp == NULL) YYERROR;
        if (tp->elems.size() <= static_cast<long int>($[field]->value)) YYERROR;
        $$ = new Tajada::AST::TupleAccessByInteger($[source], $[field]);
}

/* §3.4.5p5 */
| expr[source] TUPLE_ARROW IDENT[pos]

/* §3.4.5p8 */
| expr[source] ARRAY_ACCESS_OP expr[pos] ARRAY_ACCESS_CL

/* §3.4.5p10 */
| expr[l] EXPR_LIST_SEP expr[r]
;



intlit
: LIT_INT[token]
{ $$ = new Tajada::AST::Literal::Integer($[token]); }



operator

/* §3.4.3.2l1.1 */
: OP_MINUS

/* §3.4.3.2l1.2 */
| OP_PLUS

/* §3.4.3.2l1.3 */
| OP_MULT

/* §3.4.3.2l1.4 */
| OP_DIV

/* §3.4.3.2l1.5 */
| OP_MOD

/* §3.4.3.2l1.6 */
| OP_EQ

/* §3.4.3.2l1.7 */
| OP_NEQ
;



/* §3.4.1.2p4 */
tuple_elems

: tuple_elems[xs] LIST_SEP tuple_elem[x]
{ $[xs]->push_back($[x]); $$ = $[xs]; }

| tuple_elem[x]
{ $$ = new std::list<std::tuple<Tajada::AST::Expression *, std::string *> *>(1, $[x]); }

;



/* §3.4.1.2p4 */
tuple_elem

: expr LABEL_ARROW IDENT[name]
{ $$ = new std::tuple<Tajada::AST::Expression *, std::string *>($[expr], $[name]); }

| expr
{ $$ = new std::tuple<Tajada::AST::Expression *, std::string *>($[expr], new std::string("")); }

;



/* §3.3p3 */
block
: BLOCK_OP blocklevels BLOCK_CL
;

/* §3.3p3 */
blocklevels
: blocklevels blocklevel
|
;

/* §3.3p3 */
blocklevel
: var_def
| stmt
| block
;



stmt

/* §3.5.1p1 */
: expr STMT_END

/* §3.5.1p7 */
/* TODO: check for lvalue in action */
| expr ASSIGN expr STMT_END

/* §3.5.2.1p3 */
| IF PAREN_OP expr PAREN_CL body ELSE body
| IF PAREN_OP expr PAREN_CL body

/* §3.5.2.2p2 */
| WHILE PAREN_OP expr PAREN_CL body

/* §3.5.2.3p4 */
| FOR IDENT IN PAREN_OP expr RANGE_SEP expr PAREN_CL body
;



body
: stmt
| block
;



/* TODO: Pasaje por referencia que no funciona */
/*
arg
: expr
| REF_MARK expr
| TUPLE_OP arg_tuple_elems TUPLE_CL
;

arg_tuple_elems
: REF_MARK expr
| arg_tuple_elems   LIST_SEP expr
| mixed_tuple_elems LIST_SEP REF_MARK expr
;

mixed_tuple_elems
: mixed_tuple_elem
| mixed_tuple_elems LIST_SEP mixed_tuple_elem
;

mixed_tuple_elem
: expr
| REF_MARK expr
;
*/
