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
: typedef
| var_def
| func_spec STMT_END
| overload_spec STMT_END
| func_spec block
| overload_spec block
;

/* §3.1.1p4 */
typedef
: IDENT[identificador] ES DULCE DE typespec[tipo] STMT_END
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

/* TODO: sección de dulces */
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
| LIT_INT
| LIT_CHR
| LIT_STR
| LIT_INT FLOAT_SEP LIT_INT
| TETERO
| NEGRITO
| arg OP_PLUS  arg
| arg OP_MINUS arg
| arg OP_DIV   arg
| arg OP_MOD   arg
| arg OP_EQ    arg
| arg OP_NEQ   arg
| PAREN_OP OP_PLUS  PAREN_CL arg arg
| PAREN_OP OP_MINUS PAREN_CL arg arg
| PAREN_OP OP_DIV   PAREN_CL arg arg
| PAREN_OP OP_MOD   PAREN_CL arg arg
| PAREN_OP OP_EQ    PAREN_CL arg arg
| PAREN_OP OP_NEQ   PAREN_CL arg arg
| TUPLE_OP tuple_elems TUPLE_CL
| TUPLE_OP TUPLE_CL
| PAREN_OP expr PAREN_CL
;

tuple_elems
: expr
| tuple_elems LIST_SEP expr
;

arg
: expr
;

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

%%

