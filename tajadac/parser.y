%require "2.5"

%language "C++"
%define namespace "tajada::yy"
//%name-prefix "tajada::lex::yy"

%debug
%defines
%error-verbose
%locations
%verbose

%code {
        namespace tajada {
                namespace lex {
#undef yylex
                        int yylex(tajada::yy::parser::semantic_type * s, tajada::yy::parser::location_type * l, tajada::lex::scanner * state);
#define yylex tajada::lex::yylex
                }
        }
}

%code requires {
        namespace tajada {
                namespace lex {
                        struct scanner;
                }
        }
}

%parse-param { tajada::lex::scanner * s }
%lex-param   { tajada::lex::scanner * s }

%nonassoc OP_EQ OP_NEQ
%left OP_PLUS OP_MINUS
%left OP_MULT OP_DIV OP_MOD
%nonassoc TUPLE_ARROW
%nonassoc ARRAY_ACCESS_OP
%nonassoc PAREN_CL

%tokens

%token END 0 "fin del documento"

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
| LIT_INT TAZAS DE ARROZ CON typespec

;



/* §2.2p11, §2.3p6 */
structure_typespecs
: structure_typespecs LIST_SEP typespec IDENT
| structure_typespecs LIST_SEP typespec
| typespec IDENT
| typespec
;

operator
: OP_PLUS
| OP_MINUS
| OP_MULT
| OP_DIV
| OP_MOD
| OP_EQ
| OP_NEQ
;

block
: BLOCK_OP blocklevels BLOCK_CL
;

blocklevels
: blocklevels blocklevel
|
;

blocklevel
: var_def
| stmt STMT_END
| block
;

stmt
: lvalue ASSIGN expr
;

lvalue
: IDENT
;



expr
: IDENT

/* §3.4.1.1p1 */
| LIT_STR

/* §3.4.1.1p2 */
| TETERO
| NEGRITO

/* §3.4.1.1p3 */
| LIT_CHR

/* §3.4.1.1p4 */
| LIT_INT

/* §3.4.1.1p5, §2.1.4p4 */
| LIT_INT FLOAT_SEP LIT_INT

/* §3.4.2p4 */
| TUPLE_OP TUPLE_CL
| TUPLE_OP tuple_elems TUPLE_CL

/* §3.4.3 */
/* TODO: arreglar el peo del pasaje por referenca y detallar los párrafos en las referencias de esto */
| expr OP_PLUS  expr
| expr OP_MINUS expr
| expr OP_DIV   expr
| expr OP_MOD   expr
| expr OP_EQ    expr
| expr OP_NEQ   expr
| PAREN_OP OP_PLUS  PAREN_CL expr expr
| PAREN_OP OP_MINUS PAREN_CL expr expr
| PAREN_OP OP_DIV   PAREN_CL expr expr
| PAREN_OP OP_MOD   PAREN_CL expr expr
| PAREN_OP OP_EQ    PAREN_CL expr expr
| PAREN_OP OP_NEQ   PAREN_CL expr expr

/* §3.4.3 */
/* TODO: organizar la sección de “otras” y detallar los párrafos en las referencias de esto */
| PAREN_OP expr PAREN_CL
| expr TUPLE_ARROW LIT_INT
| expr TUPLE_ARROW IDENT
| expr ARRAY_ACCESS_OP expr ARRAY_ACCESS_CL
;



/* §3.4.2p4 */
tuple_elems
: tuple_elems LIST_SEP tuple_elem
| tuple_elem
;

/* §3.4.2p4 */
tuple_elem
: expr LABEL_ARROW IDENT
| expr
;



/* Pasaje por referencia que no funciona */
/*
arg
: expr
;

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

%%

