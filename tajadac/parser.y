/* Para GNU Bison */

%require "2.5"

%language "C++"
%define namespace "Tajada::yy"

%debug
%defines
%error-verbose
%locations
%verbose



%code {
        /* Forward‐declaration of lexer function.  Don’t ask. */
        namespace Tajada {
                namespace lex {
#undef yylex
                        int yylex(Tajada::yy::parser::semantic_type * s, Tajada::yy::parser::location_type * l, Tajada::lex::Scanner * state);
#define yylex Tajada::lex::yylex
                }
        }
}

/* This doesn’t work.  We’d have to pollute the lexer code with forward‐declarations for …well, everything.  Fuck that. */
/* %name-prefix "Tajada::lex::yy" */


%code requires {
        /* Forward‐declaration of lexer data structure.  Don’t ask. */
        namespace Tajada {
                namespace lex {
                        struct Scanner;
                }
        }
}

/* This doesn’t work.  We’d have to pollute the lexer code with forward‐declarations for …well, everything.  Fuck that. */
/* %code requires { #include "lex.hh" } */

%parse-param { Tajada::lex::Scanner * scanner }
%lex-param   { Tajada::lex::Scanner * scanner }


%code requires { #include "scope.hh" }
%parse-param { Tajada::Scope * scope }


%code requires { #include "ast.hh" }
%parse-param { Tajada::AST::AST ** tree }



%nonassoc CALL
%left     EXPR_LIST_SEP
%nonassoc OP_EQ OP_NEQ
%left     OP_PLUS OP_MINUS
%left     OP_MULT OP_DIV OP_MOD
%nonassoc TUPLE_ARROW
%nonassoc ARRAY_ACCESS_OP
%nonassoc PAREN_CL
%nonassoc REF_MARK

%right ELSE



%token_data
%token END 0 "fin del documento"



%union { Tajada::AST::Program * tajada; }
%type <tajada> tajada

%union { std::list<Tajada::AST::Statement *> * statements; }
%type <statements> toplevels blocklevels

%union { Tajada::AST::Statement * statement; }
%type <statement> toplevel blocklevel statement body

%union { Tajada::AST::Block * block; }
%type <block> block

%union { std::string * op; }
%type <op> operator

%union { Tajada::Type::Type * typespec; }
%type <typespec> typespec

%union { std::tuple<Tajada::Type::Type *, std::string *> * structure_typespec; }
%type <structure_typespec> structure_typespec

%union { std::list<std::tuple<Tajada::Type::Type *, std::string *> *> * structure_typespecs; }
%type <structure_typespecs> structure_typespecs

%union { Tajada::AST::VariableDefinition * var_def; }
%type <var_def> var_def

%union { Tajada::AST::Expression * expr; }
%type <expr> expr

%union { Tajada::AST::Literal::Integer * intlit; }
%type <intlit> intlit

%union { std::tuple<Tajada::AST::Expression *, std::string *> * tuple_elem; }
%type <tuple_elem> tuple_elem

%union { std::list<std::tuple<Tajada::AST::Expression *, std::string *> *> * tuple_elems; }
%type <tuple_elems> tuple_elems



%start tajada

%%



/* §3p1 */
tajada

: toplevels[statements] block[main]
{
        bool found_undefined = false;
        for (auto it = scope->functions.begin(); it != scope->functions.end(); ++it) {
                if (std::get<2>(it->second) == NULL) {
                        error(
                                @[main],
                                std::string(u8"Function ")
                                + it->first
                                + std::string(u8" was declared for type “")
                                + std::get<0>(it->second)->show()
                                + std::string(u8"”, returning “")
                                + std::get<1>(it->second)->show()
                                + std::string(u8"”, but it was never defined")
                        );
                        found_undefined = true;
                }
        }

        if (found_undefined) YYERROR;

        *tree = new Tajada::AST::Program($[statements], $[main]);
}

;



/* §3p1 */
toplevels

: toplevels[xs] toplevel[x]
{
        $[xs]->push_back($[x]);
        $$ = $[xs];
}

|
{ $$ = new std::list<Tajada::AST::Statement *>(); }

;



/* §3p1 */
toplevel
: var_def[def]
{ $$ = $[def]; }

/* §3.1.1p4 */
| IDENT[identificador] ES DULCE DE typespec[tipo] STMT_END
{
        if (scope->aliases.find(*$[identificador]) != scope->aliases.end()) {
                error(@[identificador], "Attempt to redefine a type alias");
                YYERROR;
        }
        scope->aliases[*$[identificador]] = $[tipo];
        $$ = new Tajada::AST::TypeAlias($[identificador], $[tipo]);
}

/* §3.1.2p5,6 */
| IDENT[nombre] ES UN PLATO DE typespec[dominio] IDENT[nombre_dominio] CON SALSA DE typespec[codominio] STMT_END
{
        auto bucket = scope->functions.bucket(*$[nombre]);
        bool insert = true;

        for (auto it = scope->functions.begin(bucket); it != scope->functions.end(bucket); ++it) {
                if (*$[dominio] != *std::get<0>(it->second) || *$[codominio] != *std::get<1>(it->second)) continue;
                insert = false;
                break;
        }

        if (insert) {
                scope->functions.insert(
                        std::make_pair(
                                *$[nombre],
                                std::make_tuple(
                                        $[dominio],
                                        $[codominio],
                                        reinterpret_cast<Tajada::AST::FunctionDefinition *>(NULL)
                                )
                        )
                );
        }

        $$ = new Tajada::AST::FunctionDeclaration($[nombre], $[dominio], $[codominio]);
}

| IDENT[nombre] ES UN PLATO DE typespec[dominio] CON SALSA DE typespec[codominio] STMT_END
{
        auto bucket = scope->functions.bucket(*$[nombre]);
        bool insert = true;

        for (auto it = scope->functions.begin(bucket); it != scope->functions.end(bucket); ++it) {
                if (*$[dominio] != *std::get<0>(it->second) || *$[codominio] != *std::get<1>(it->second)) continue;
                insert = false;
                break;
        }

        if (insert) {
                scope->functions.insert(
                        std::make_pair(
                                *$[nombre],
                                std::make_tuple(
                                        $[dominio],
                                        $[codominio],
                                        reinterpret_cast<Tajada::AST::FunctionDefinition *>(NULL)
                                )
                        )
                );
        }

        $$ = new Tajada::AST::FunctionDeclaration($[nombre], $[dominio], $[codominio]);
}

/* §3.1.3p5,6 */
| HAY UN CUBIERTO operator[nombre] PARA typespec[dominio] Y SALSA DE typespec[codominio] STMT_END
{
        auto bucket = scope->functions.bucket(*$[nombre]);
        bool insert = true;

        for (auto it = scope->functions.begin(bucket); it != scope->functions.end(bucket); ++it) {
                if (*$[dominio] != *std::get<0>(it->second) || *$[codominio] != *std::get<1>(it->second)) continue;
                insert = false;
                break;
        }

        if (insert) {
                scope->functions.insert(
                        std::make_pair(
                                *$[nombre],
                                std::make_tuple(
                                        $[dominio],
                                        $[codominio],
                                        reinterpret_cast<Tajada::AST::FunctionDefinition *>(NULL)
                                )
                        )
                );
        }

        $$ = new Tajada::AST::FunctionDeclaration($[nombre], $[dominio], $[codominio]);
}

/* §3.2.2p1 */
| IDENT[nombre] ES UN PLATO DE typespec[dominio] IDENT[nombre_dominio] CON SALSA DE typespec[codominio] block[body]
{
        auto bucket = scope->functions.bucket(*$[nombre]);
        bool insert = true;

        auto it = scope->functions.begin(bucket);
        for (; it != scope->functions.end(bucket); ++it) {
                if (*$[dominio] != *std::get<0>(it->second) || *$[codominio] != *std::get<1>(it->second)) continue;
                insert = false;
                break;
        }

        auto ret = new Tajada::AST::FunctionDefinition($[nombre], $[nombre_dominio], $[dominio], $[codominio], $[body]);

        if (insert) scope->functions.insert(std::make_pair(*$[nombre], std::make_tuple($[dominio], $[codominio], ret)));
        else std::get<2>(it->second) = ret;

        $$ = ret;
}

| IDENT[nombre] ES UN PLATO DE typespec[dominio] CON SALSA DE typespec[codominio] block[body]
{
        auto bucket = scope->functions.bucket(*$[nombre]);
        bool insert = true;

        auto it = scope->functions.begin(bucket);
        for (; it != scope->functions.end(bucket); ++it) {
                if (*$[dominio] != *std::get<0>(it->second) || *$[codominio] != *std::get<1>(it->second)) continue;
                insert = false;
                break;
        }

        auto ret = new Tajada::AST::FunctionDefinition($[nombre], new std::string(), $[dominio], $[codominio], $[body]);

        if (insert) scope->functions.insert(std::make_pair(*$[nombre], std::make_tuple($[dominio], $[codominio], ret)));
        else std::get<2>(it->second) = ret;

        $$ = ret;
}

/* §3.2.3p1 */
| HAY UN CUBIERTO operator[nombre] PARA typespec[dominio] Y SALSA DE typespec[codominio] block[body]
{
        auto bucket = scope->functions.bucket(*$[nombre]);
        bool insert = true;

        auto it = scope->functions.begin(bucket);
        for (; it != scope->functions.end(bucket); ++it) {
                if (*$[dominio] != *std::get<0>(it->second) || *$[codominio] != *std::get<1>(it->second)) continue;
                insert = false;
                break;
        }

        auto ret = new Tajada::AST::FunctionDefinition($[nombre], new std::string(), $[dominio], $[codominio], $[body]);

        if (insert) scope->functions.insert(std::make_pair(*$[nombre], std::make_tuple($[dominio], $[codominio], ret)));
        else std::get<2>(it->second) = ret;

        $$ = ret;
}

;



/* §3.2.1p4 */
var_def
: IDENT[nombre] ES typespec[tipo] STMT_END
{
        if (scope->variables.find(*$[nombre]) != scope->variables.end()) {
                error(@[nombre], "Attempt to redefine a variable");
                YYERROR;
        }
        scope->variables[*$[nombre]] = $[tipo];
        $$ = new Tajada::AST::VariableDefinition($[nombre], $[tipo]);
}

;



typespec

/* §3.1.1p5 */
: IDENT[nombre]
{
        auto s = scope;
        decltype(s->aliases.begin()) it;

        while (s != NULL) {
                if ((it = s->aliases.find(*$[nombre])) != s->aliases.end()) break;
                s = s->parent;
        }

        if (s == NULL) {
                error(@[nombre], "Attempt to use an undefined type alias");
                YYERROR;
        }

        $$ = it->second;
}

/* §2.1.1p5 */
| CAFE
{ $$ = new Tajada::Type::Boolean(); }

/* §2.1.2p3 */
| CARAOTA
{ $$ = new Tajada::Type::Character(); }

/* §2.1.3p3 */
| QUESO
{ $$ = new Tajada::Type::Integer(); }

/* §2.1.4p3 */
| PAPELON
{ $$ = new Tajada::Type::Float(); }

/* §2.2p7 */
| AREPA VIUDA
{ $$ = new Tajada::Type::Tuple(new std::list<std::tuple<Tajada::Type::Type *, std::string *> *>()); }

/* §2.2p8 */
| AREPA DE structure_typespec[ingrediente]
{
        auto ret = new Tajada::Type::Tuple(new std::list<std::tuple<Tajada::Type::Type *, std::string *> *>());
        ret->elems->push_back($[ingrediente]);
        $$ = ret;
}

/* §2.2p11 */
| AREPA CON structure_typespecs[ingredientes] Y structure_typespec[ingrediente]
{
        auto ret = new Tajada::Type::Tuple($[ingredientes]);
        ret->elems->push_back($[ingrediente]);
        $$ = ret;
}

/* §2.3p6 */
| CACHAPA CON structure_typespecs[ingredientes] O structure_typespec[ingrediente]
{
        auto ret = new Tajada::Type::Union();
        $[ingredientes]->push_back($[ingrediente]);
        ret->elems = $[ingredientes];
        $$ = ret;
}

/* §2.4p3 */
| ARROZ CON typespec[contenido]
{ $$ = new Tajada::Type::Array($[contenido]); }

/* §2.4p4 */
/* TODO: Y con el tamaño ¿qué hago?  Hay que definir todo eso mejor. */
| intlit TAZAS DE ARROZ CON typespec[contenido]
{ $$ = new Tajada::Type::Array($[contenido]); }

;



/* §2.2p11, §2.3p6 */
structure_typespecs

: structure_typespecs[ingredientes] LIST_SEP structure_typespec[ingrediente]
{
        $[ingredientes]->push_back($[ingrediente]);
        $$ = $[ingredientes];
}

| structure_typespec[ingrediente]
{ $$ = new std::list<std::tuple<Tajada::Type::Type *, std::string *> *>(1, $[ingrediente]); }


;



/* §2.2p2 */
structure_typespec

: typespec[tipo]
{ $$ = new std::tuple<Tajada::Type::Type *, std::string *>($[tipo], new std::string()); }

| PAREN_OP typespec[tipo] IDENT[nombre] PAREN_CL
{ $$ = new std::tuple<Tajada::Type::Type *, std::string *>($[tipo], $[nombre]); }

;



expr

/* §3.4.1.1p1 */
: LIT_STR[token]
{ $$ = new Tajada::AST::Literal::String($[token]); }

/* §3.4.1.1p2 */
| TETERO
{ $$ = new Tajada::AST::Literal::False(); }

/* §3.4.1.1p2 */
| NEGRITO
{ $$ = new Tajada::AST::Literal::True(); }

/* §3.4.1.1p3 */
| LIT_CHR[token]
{ $$ = new Tajada::AST::Literal::Character($[token]); }

/* §3.4.1.1p4 */
| intlit[literal]
{ $$ = $[literal]; }

/* §3.4.1.1p5, §2.1.4p4 */
| LIT_INT[integer] FLOAT_SEP LIT_INT[fractional]
{ $$ = new Tajada::AST::Literal::Float($[integer], $[fractional]); }

/* §3.4.1.2p4 */
| TUPLE_OP TUPLE_CL
{ $$ = new Tajada::AST::Literal::Tuple(new std::list<std::tuple<Tajada::AST::Expression *, std::string *> *>()); }

/* §3.4.1.2p4 */
| TUPLE_OP tuple_elems TUPLE_CL
{ $$ = new Tajada::AST::Literal::Tuple($[tuple_elems]); }

/* TODO: arreglar el peo del pasaje por referenca */

/* §3.4.2p2 */
| IDENT[nombre] CALL expr[argumento]
| IDENT[nombre] CALL REF_MARK expr[argumento]
{
        auto s = scope;
        decltype(s->functions.begin()) it;

        while (s != NULL) {
                if (
                        (it = s->functions.find(*$[nombre])) != s->functions.end()
                        && *$[argumento]->type == *std::get<0>(it->second)
                ) break;
                s = s->parent;
        }

        if (s == NULL) {
                error(@[nombre], "Attempt to use an undefined function");
                YYERROR;
        }

        $$ = new Tajada::AST::Call($[nombre], &it->second, $[argumento]);
}

/* TODO: operadores unarios */
| OP_MINUS expr
| OP_MINUS REF_OP expr REF_CL

/* §3.4.3.2l1.1 */
|        expr[l]        OP_MINUS        expr[r]
| REF_OP expr[l] REF_CL OP_MINUS        expr[r]
|        expr[l]        OP_MINUS REF_OP expr[r] REF_CL
| REF_OP expr[l] REF_CL OP_MINUS REF_OP expr[r] REF_CL
| PAREN_OP OP_MINUS PAREN_CL        expr[parametros]
| PAREN_OP OP_MINUS PAREN_CL REF_OP expr[parametros] REF_CL
/*| ref expr[l] OP_MINUS ref expr[r]*/
/*| PAREN_OP OP_MINUS PAREN_CL ref expr[parametros]*/

/* §3.4.3.2l1.2 */
|        expr[l]        OP_PLUS        expr[r]
| REF_OP expr[l] REF_CL OP_PLUS        expr[r]
|        expr[l]        OP_PLUS REF_OP expr[r] REF_CL
| REF_OP expr[l] REF_CL OP_PLUS REF_OP expr[r] REF_CL
| PAREN_OP OP_PLUS PAREN_CL        expr[parametros]
| PAREN_OP OP_PLUS REF_CL PAREN_OP expr[parametros] REF_CL

/* §3.4.3.2l1.3 */
/*| ref expr[l] OP_MULT ref expr[r]*/
/*| PAREN_OP OP_MULT PAREN_CL ref expr[parametros]*/

/* §3.4.3.2l1.4 */
/*| ref expr[l] OP_DIV ref expr[r]*/
/*| PAREN_OP OP_DIV PAREN_CL ref expr[parametros]*/

/* §3.4.3.2l1.5 */
/*| ref expr[l] OP_MOD ref expr[r]*/
/*| PAREN_OP OP_MOD PAREN_CL ref expr[parametros]*/

/* §3.4.3.2l1.6 */
/*| ref expr[l] OP_EQ ref expr[r]*/
/*| PAREN_OP OP_EQ PAREN_CL ref expr[parametros]*/

/* §3.4.3.2l1.7 */
/*| ref expr[l] OP_NEQ ref expr[r]*/
/*| PAREN_OP OP_NEQ PAREN_CL ref expr[parametros]*/

/* §3.4.4p2 */
| IDENT[nombre]
{
        auto s = scope;
        decltype(s->variables.begin()) it;

        while (s != NULL) {
                if ((it = s->variables.find(*$[nombre])) != s->variables.end()) break;
                s = s->parent;
        }

        if (s == NULL) {
                error(@[nombre], "Attempt to use an undefined variable");
                YYERROR;
        }

        $$ = new Tajada::AST::VariableUse($[nombre], it->second);
}

/* §3.4.6p3 */
| PAREN_OP expr[in] PAREN_CL
{ $$ = $[in]; }

/* §3.4.6p5 */
| expr[source] TUPLE_ARROW intlit[field]
{
        auto tp = dynamic_cast<Tajada::Type::Tuple *>($[source]->type);

        if (tp == NULL) {
                error(@$, u8"Attempt to access numbered tuple field by number on expression of non‐tuple type");
                YYERROR;
        }

        if ((*tp)[$[field]->value] == NULL) {
                error(@$, u8"Attempt to access nonexistent tuple field");
                YYERROR;
        }

        $$ = new Tajada::AST::TupleAccessByInteger($[source], $[field]);
}

/* §3.4.6p5 */
| expr[source] TUPLE_ARROW IDENT[field]
{
        auto tp = dynamic_cast<Tajada::Type::Tuple *>($[source]->type);

        if (tp == NULL) {
                error(@$, u8"Attempt to access tuple field by name on expression of non‐tuple type");
                YYERROR;
        }

        if ((*tp)[*$[field]] == NULL) {
                error(@$, u8"Attempt to access nonexistent named tuple field");
                YYERROR;
        }

        $$ = new Tajada::AST::TupleAccessByName($[source], $[field]);
}

/* §3.4.6p8 */
| expr[source] ARRAY_ACCESS_OP expr[position] ARRAY_ACCESS_CL
{
        auto ap = dynamic_cast<Tajada::Type::Array *>($[source]->type);

        if (ap == NULL) {
                error(@$, u8"Attempt to access array element on expression of non‐array type");
                YYERROR;
        }

        auto ip = dynamic_cast<Tajada::Type::Integer *>($[position]->type);

        if (ip == NULL) {
                error(@$, u8"Attempt to access array element on non‐integer position");
                YYERROR;
        }

        $$ = new Tajada::AST::ArrayAccess($[source], $[position]);
}

/* §3.4.6p10 */
| expr[l] EXPR_LIST_SEP expr[r]
{ $$ = new Tajada::AST::Sequence($[l], $[r]); }

;



ref
: REF_MARK
|
;



intlit
: LIT_INT[token]
{ $$ = new Tajada::AST::Literal::Integer($[token]); }



operator

/* §3.4.3.2l1.1 */
: OP_MINUS[op]
{ $$ = $[op]; }

/* §3.4.3.2l1.2 */
| OP_PLUS[op]
{ $$ = $[op]; }

/* §3.4.3.2l1.3 */
| OP_MULT[op]
{ $$ = $[op]; }

/* §3.4.3.2l1.4 */
| OP_DIV[op]
{ $$ = $[op]; }

/* §3.4.3.2l1.5 */
| OP_MOD[op]
{ $$ = $[op]; }

/* §3.4.3.2l1.6 */
| OP_EQ[op]
{ $$ = $[op]; }

/* §3.4.3.2l1.7 */
| OP_NEQ[op]
{ $$ = $[op]; }

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

: BLOCK_OP { auto ns = new Scope(scope); scope->children.insert(ns); scope = ns; } blocklevels[statements] { scope = scope->parent; } BLOCK_CL
{ $$ = new Tajada::AST::Block($[statements]); }

;


blocklevels

: blocklevels[xs] blocklevel[x]
{
        $[xs]->push_back($[x]);
        $$ = $[xs];
}

|
{ $$ = new std::list<Tajada::AST::Statement *>(); }

;


blocklevel

: var_def
{ $$ = $[var_def]; }

| statement
{ $$ = $[statement]; }

| block
{ $$ = $[block]; }

;



statement

/* §3.5.1p1 */
: expr[expression] STMT_END
{ $$ = new Tajada::AST::ExpressionStatement($[expression]); }

/* §3.5.1p7 */
/* TODO: check for lvalue in action */
| expr[l] ASSIGN expr[r] STMT_END
{
        if (!$[l]->is_lvalue) {
                error(@$, u8"Attempt to assign to expression without l‐value");
                YYERROR;
        }

        if (*$[l]->type != *$[r]->type) {
                error(@$, u8"Attempt to assign with incompatible types");
                std::cerr << "lhs is " << $[l]->type->show() << std::endl;
                std::cerr << "rhs is " << $[r]->type->show() << std::endl;
                YYERROR;
        }

        $$ = new Tajada::AST::Assignment($[l], $[r]);
}

/* §3.5.2.1p3 */
| IF PAREN_OP expr[condition] PAREN_CL body[body_true] ELSE body[body_false]
{ $$ = new Tajada::AST::If($[condition], $[body_true], $[body_false]); }

| IF PAREN_OP expr[condition] PAREN_CL body[body_true]
{ $$ = new Tajada::AST::If($[condition], $[body_true], new Tajada::AST::Block(new std::list<Tajada::AST::Statement *>())); }

/* §3.5.2.2p2 */
| WHILE PAREN_OP expr[condition] PAREN_CL body
{ $$ = new Tajada::AST::While($[condition], $[body]); }

/* §3.5.2.3p4 */
/*| FOR IDENT IN PAREN_OP expr RANGE_SEP expr PAREN_CL body*/

;



body
: statement
{ $$ = $[statement]; }

| block
{ $$ = $[block]; }

;



%%



void Tajada::yy::parser::error(location_type const & l, std::string const & msg) {
        if (l.begin.line == l.end.line) {
                if (l.begin.column == l.end.column - 1) {
                        std::cerr << u8"At line " << l.begin.line << u8", column " << l.begin.column;
                } else {
                        std::cerr
                                << u8"At line " << l.begin.line
                                << u8", columns " << l.begin.column << u8"–" << l.end.column;
                }
        } else {
                std::cerr
                        << u8"Between line " << l.begin.line << u8", column " << l.begin.column
                        << u8" and line "    << l.end  .line << u8", column " << l.end  .column;
        }

        std::cerr << u8": " << msg << std::endl;
}
