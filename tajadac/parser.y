/* Para GNU Bison */

%require "2.5"

%language "C++"
%define namespace "Tajada::yy"

%debug
%defines
%error-verbose
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



%code {
#define TAJADA_CALL_UNARY(nombre, argumento, out, loc)                               \
        auto s = scope;                                                              \
        decltype(scope->functions.begin(scope->functions.bucket(std::string()))) it; \
        std::list<decltype(s->functions.begin()->second) *> candidates;              \
                                                                                     \
        while (s != nullptr) {                                                       \
                auto bucket = s->functions.bucket(*nombre);                          \
                                                                                     \
                bool go = true;                                                      \
                for (                                                                \
                        it = s->functions.begin(bucket);                             \
                        it != s->functions.end(bucket);                              \
                        ++it                                                         \
                ) {                                                                  \
                        if (*argumento->type == *std::get<0>(it->second)) {          \
                                go = false;                                          \
                                break;                                               \
                        }                                                            \
                        candidates.push_back(&it->second);                           \
                }                                                                    \
                if (!go) break;                                                      \
                                                                                     \
                s = s->parent;                                                       \
        }                                                                            \
                                                                                     \
        if (s == nullptr) {                                                          \
                error(                                                               \
                        loc,                                                         \
                        u8"attempt to use undeclared function “"                     \
                        + *nombre                                                    \
                        + u8"” taking “"                                             \
                        + argumento->type->show()                                    \
                        + u8"”"                                                      \
                );                                                                   \
                if (!candidates.empty()) {                                           \
                        error(                                                       \
                                loc,                                                 \
                                + u8"candidates are:"                                \
                        );                                                           \
                        std::for_each(                                               \
                                candidates.begin(),                                  \
                                candidates.end(),                                    \
                                [this](decltype(*candidates.begin()) c) {            \
                                        error(                                       \
                                                std::get<3>(*c),                     \
                                                u8"First declared here"              \
                                        );                                           \
                                }                                                    \
                        );                                                           \
                }                                                                    \
                YYERROR;                                                             \
        }                                                                            \
                                                                                     \
        out = new Tajada::AST::Call(                                                 \
                nombre,                                                              \
                std::get<2>(it->second),                                             \
                argumento,                                                           \
                std::get<1>(it->second)                                              \
        );

#define TAJADA_CALL_BINARY(nombre, l, r, out, loc)                                                        \
        auto argumento = new Tajada::AST::Literal::Tuple(                                                 \
                new std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *> {                 \
                        new std::tuple<Tajada::AST::Expression *, std::string *>(l, new std::string("")), \
                        new std::tuple<Tajada::AST::Expression *, std::string *>(r, new std::string("")), \
                }                                                                                         \
        );                                                                                                \
        TAJADA_CALL_UNARY(nombre, argumento, out, loc)
}



%parse-param { Tajada::lex::Scanner * scanner }
%lex-param   { Tajada::lex::Scanner * scanner }


%code requires { #include "scope.hh" }
%parse-param { Tajada::Scope * scope }


%code requires { #include "ast.hh" }
%parse-param { Tajada::AST::AST ** tree }



%locations
%parse-param { std::string * filename }
%initial-action { @$.begin.filename = @$.end.filename = filename; };



%nonassoc CALL
%left     EXPR_LIST_SEP
%nonassoc OP_EQ OP_NEQ
%left     OP_PLUS OP_MINUS
%left     OP_MULT OP_DIV OP_MOD
%nonassoc TUPLE_ARROW
%nonassoc ARRAY_ACCESS_OP
%nonassoc PAREN_CL

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

%union { std::tuple<std::string *, Tajada::AST::Operator> * op; }
%type <op> operator

%union { Tajada::Type::Type * typespec; }
%type <typespec> typespec

%union { std::tuple<Tajada::Type::Type *, std::string *> * structure_typespec; }
%type <structure_typespec> structure_typespec

%union { std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> * structure_typespecs; }
%type <structure_typespecs> structure_typespecs structure_types

%union { Tajada::AST::VariableDefinition * var_def; }
%type <var_def> var_def

%union { Tajada::AST::Expression * expr; }
%type <expr> expr

%union { Tajada::AST::Literal::Integer * intlit; }
%type <intlit> intlit

%union { std::tuple<Tajada::AST::Expression *, std::string *> * tuple_elem; }
%type <tuple_elem> tuple_elem

%union { std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *> * tuple_elems; }
%type <tuple_elems> tuple_elems

%union {  std::tuple<Tajada::AST::FunctionDeclaration *, Tajada::AST::Function **> * func_spec; }
%type <func_spec> func_spec



%start tajada

%%



/* §3p1 */
tajada

: toplevels[statements] block[main]
{
        bool found_undefined = false;
        for (auto it = scope->functions.begin(); it != scope->functions.end(); ++it) {
                if (*std::get<2>(it->second) == nullptr) {
                        error(
                                @$,
                                std::string(u8"Missing definition for function “")
                                + it->first
                                + std::string(u8"” taking “")
                                + std::get<0>(it->second)->show()
                                + std::string(u8"” and returning “")
                                + std::get<1>(it->second)->show()
                                + std::string(u8"”")
                        );
                        error(
                                std::get<3>(it->second),
                                u8"First declared here"
                        );
                        found_undefined = true;
                }
        }

        if (found_undefined) YYERROR;

        *tree = $$ = new Tajada::AST::Program($[statements], $[main]);
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
                error(
                        @[identificador],
                        u8"Attempt to redefine type alias "
                        + *$[identificador]
                );
                YYERROR;
        }
        scope->aliases[*$[identificador]] = $[tipo];
        $$ = new Tajada::AST::TypeAlias($[identificador], $[tipo]);
}

/* §3.1.2p6, §3.1.3p6 */
| func_spec STMT_END
{
        $$ = std::get<0>(*$[func_spec]);
        delete $[func_spec];
}

/* §3.2.2p1, §3.2.3p1 */
| func_spec BLOCK_OP {
        auto ns = new Scope(
                scope,
                Tajada::Scope::Type::function,
                std::get<0>(*$[func_spec])
        );
        scope->children.insert(ns);
        scope = ns;
        scope->variables[*std::get<0>(*$[func_spec])->domain_name] = std::get<0>(*$[func_spec])->domain;
} blocklevels[statements] {
        scope = scope->parent;
} BLOCK_CL {
        auto ret = new Tajada::AST::FunctionDefinition(std::get<0>(*$[func_spec]), new Tajada::AST::Block($[statements]));

        *std::get<1>(*$[func_spec]) = ret;
        $$ = ret;
        delete $[func_spec];
}

;



func_spec

/* §3.1.2p5 */
: IDENT[nombre] ES UN PLATO DE typespec[dominio] IDENT[nombre_dominio] CON SALSA DE typespec[codominio]
{
        auto bucket = scope->functions.bucket(*$[nombre]);
        bool insert = true;

        auto it = scope->functions.begin(bucket);
        for (; it != scope->functions.end(bucket); ++it) {
                // TODO: ponerlo así para meterle polimorfismo más bonito
                // if (*$[dominio] != *std::get<0>(it->second) || *$[codominio] != *std::get<1>(it->second)) continue;
                if (*$[dominio] != *std::get<0>(it->second)) continue;
                if (*$[codominio] != *std::get<1>(it->second)) {
                        error(
                                @$,
                                u8"Conflicting types for “"
                                + *$[nombre]
                                + u8"” taking “"
                                + $[dominio]->show()
                                + u8"”"
                        );
                        error(
                                std::get<3>(it->second),
                                u8"First declared here"
                        );
                        YYERROR;
                }
                insert = false;
                break;
        }

        Tajada::AST::Function ** r;

        if (insert) {
                auto it = scope->functions.insert(
                        std::make_pair(
                                *$[nombre],
                                std::make_tuple(
                                        $[dominio],
                                        $[codominio],
                                        new Tajada::AST::Function * (nullptr),
                                        @$
                                )
                        )
                );
                r = std::get<2>(it->second);
        } else {
                r = std::get<2>(it->second);
        }

        $$ = new std::tuple<Tajada::AST::FunctionDeclaration *, Tajada::AST::Function **>(
                new Tajada::AST::FunctionDeclaration($[nombre], $[nombre_dominio], $[dominio], $[codominio]),
                r
        );
}

/* §3.1.3p5 */
| HAY UN CUBIERTO operator[operador] PARA typespec[dominio] IDENT[nombre_dominio] Y SALSA DE typespec[codominio]
{
        auto t = dynamic_cast<Tajada::Type::Tuple *>($[dominio]);

        if (!t) {
                error(
                        @[dominio],
                        u8"Domain of operator “"
                        + *std::get<0>(*$[operador])
                        + u8"” declared as non‐tuple type “"
                        + $[dominio]->show()
                        + u8"”"
                );
                YYERROR;
        }

        switch (t->elems->size()) {
                case 1:
                        switch (std::get<1>(*$[operador])) {
                                case Tajada::AST::Operator::minus:
                                        break;

                                default:
                                        error(
                                                @$,
                                                u8"Invalid unary operator “"
                                                + *std::get<0>(*$[operador])
                                                + u8"”"
                                        );
                                        YYERROR;
                        }
                        break;

                case 2:
                        switch (std::get<1>(*$[operador])) {
                                case Tajada::AST::Operator::minus:
                                case Tajada::AST::Operator::plus:
                                case Tajada::AST::Operator::mult:
                                case Tajada::AST::Operator::div:
                                case Tajada::AST::Operator::mod:
                                case Tajada::AST::Operator::eq:
                                case Tajada::AST::Operator::neq:
                                        break;

                                default:
                                        error(
                                                @$,
                                                u8"Invalid binary operator “"
                                                + *std::get<0>(*$[operador])
                                                + u8"”"
                                        );
                                        YYERROR;
                        }
                        break;

                default:
                        error(
                                @$,
                                u8"Operator “"
                                + *std::get<0>(*$[operador])
                                + u8"” declared with invalid arity "
                                + std::to_string(t->elems->size())
                        );
                        YYERROR;
        }

        auto bucket = scope->functions.bucket(*std::get<0>(*$[operador]));
        bool insert = true;

        auto it = scope->functions.begin(bucket);
        for (; it != scope->functions.end(bucket); ++it) {
                // TODO: ponerlo así para meterle polimorfismo más bonito
                // if (*$[dominio] != *std::get<0>(it->second) || *$[codominio] != *std::get<1>(it->second)) continue;
                if (*$[dominio] != *std::get<0>(it->second)) continue;
                if (*$[codominio] != *std::get<1>(it->second)) {
                        error(
                                @$,
                                u8"Conflicting return types for “"
                                + *std::get<0>(*$[operador])
                                + u8"” taking “"
                                + $[dominio]->show()
                                + u8"”"
                        );
                        YYERROR;
                }
                insert = false;
                break;
        }

        Tajada::AST::Function ** r;

        if (insert) {
                auto it = scope->functions.insert(
                        std::make_pair(
                                *std::get<0>(*$[operador]),
                                std::make_tuple(
                                        $[dominio],
                                        $[codominio],
                                        new Tajada::AST::Function * (nullptr),
                                        @$
                                )
                        )
                );
                r = std::get<2>(it->second);
        } else {
                r = std::get<2>(it->second);
        }

        $$ = new std::tuple<Tajada::AST::FunctionDeclaration *, Tajada::AST::Function **>(
                new Tajada::AST::FunctionDeclaration(std::get<0>(*$[operador]), $[nombre_dominio], $[dominio], $[codominio]),
                r
        );

        delete $[operador];
}



/* §3.2.1p4 */
var_def
: IDENT[nombre] ES typespec[tipo] STMT_END
{
        if (scope->variables.find(*$[nombre]) != scope->variables.end()) {
                error(
                        @$,
                        u8"redefinition of “"
                        + *$[nombre]
                        + u8"”"
                );
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

        while (s != nullptr) {
                if ((it = s->aliases.find(*$[nombre])) != s->aliases.end()) break;
                s = s->parent;
        }

        if (s == nullptr) {
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

/* §2.2 */
| AREPA structure_types[ingredientes]
{ $$ = new Tajada::Type::Tuple($[ingredientes]); }

/* §2.3p6 */
| CACHAPA CON structure_typespecs[ingredientes] O structure_typespec[ingrediente]
{
        $[ingredientes]->push_back($[ingrediente]);
        $$ = new Tajada::Type::Union($[ingredientes]);
}

/* §2.4p3 */
| ARROZ CON typespec[contenido]
{ $$ = new Tajada::Type::Array($[contenido]); }

/* §2.4p4 */
| intlit[longitud] TAZAS DE ARROZ CON typespec[contenido]
{ $$ = new Tajada::Type::Array($[contenido], $[longitud]->value); }

/* §2.5p4 */
| REF_OP typespec[referido]
{ $$ = new Tajada::Type::Reference($[referido]); }

;



/* §2.2p11, §2.3p6 */
structure_typespecs

: structure_typespecs[ingredientes] LIST_SEP structure_typespec[ingrediente]
{
        $[ingredientes]->push_back($[ingrediente]);
        $$ = $[ingredientes];
}

| structure_typespec[ingrediente]
{ $$ = new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *>(1, $[ingrediente]); }

;



structure_types

/* §2.2p8 */
: VIUDA
{ $$ = new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *>(); }

/* §2.2p9 */
| DE structure_typespec[ingrediente]
{
        $$ = new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *>({$[ingrediente]});
}

/* §2.2p12 */
| CON structure_typespecs[ingredientes] Y structure_typespec[ingrediente]
{
        $[ingredientes]->push_back($[ingrediente]);
        $$ = $[ingredientes];
}



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

/* §2.1.1p4, §3.4.1.1p2 */ /* TODO: CHECK LAST REF */
| TETERO
{ $$ = new Tajada::AST::Literal::Boolean(false); }

/* §2.1.1p4, §3.4.1.1p2 */ /* TODO: CHECK LAST REF */
| NEGRITO
{ $$ = new Tajada::AST::Literal::Boolean(true); }

/* §2.1.2p4, §3.4.1.1p3 */
| LIT_CHR[token]
{ $$ = new Tajada::AST::Literal::Character($[token]); }

/* §3.4.1.1p4 */
| intlit[literal]
{ $$ = $[literal]; }

/* old ref: §3.4.1.1p5, §2.1.4p4 */
/* §1.3.2p2 */
| LIT_INT[integer] FLOAT_SEP LIT_INT[fractional]
{ $$ = new Tajada::AST::Literal::Float($[integer], $[fractional]); }

/* §3.4.1.2p4 */
| TUPLE_OP TUPLE_CL
{ $$ = new Tajada::AST::Literal::Tuple(new std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *>()); }

/* §3.4.1.2p4 */
| TUPLE_OP tuple_elems TUPLE_CL
{ $$ = new Tajada::AST::Literal::Tuple($[tuple_elems]); }

/* §3.4.2p2                 */ |             IDENT[nombre]          CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) }
/* TODO: operadores unarios */ |          OP_MINUS[nombre]               expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) }
/* §3.4.3.2l1.1             */ | PAREN_OP OP_MINUS[nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_MINUS[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
/* §3.4.3.2l1.2             */ | PAREN_OP OP_PLUS [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_PLUS [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
/* §3.4.3.2l1.3             */ | PAREN_OP OP_MULT [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_MULT [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
/* §3.4.3.2l1.4             */ | PAREN_OP OP_DIV  [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_DIV  [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
/* §3.4.3.2l1.5             */ | PAREN_OP OP_MOD  [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_MOD  [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
/* §3.4.3.2l1.6             */ | PAREN_OP OP_EQ   [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_EQ   [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
/* §3.4.3.2l1.7             */ | PAREN_OP OP_NEQ  [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_NEQ  [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }

/* §3.4.4p2 */
| IDENT[nombre]
{
        auto s = scope;
        decltype(s->variables.begin()) it;

        while (s != nullptr) {
                if ((it = s->variables.find(*$[nombre])) != s->variables.end()) break;
                s = s->parent;
        }

        if (s == nullptr) {
                error(
                        @[nombre],
                        u8"“"
                        + *$[nombre]
                        + u8"” was not declared in this scope"
                );
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

        if (tp == nullptr) {
                error(@$, u8"Attempt to access numbered tuple field by number on expression of non‐tuple type");
                YYERROR;
        }

        if ((*tp)[$[field]->value] == nullptr) {
                error(@$, u8"Attempt to access nonexistent tuple field");
                YYERROR;
        }

        $$ = new Tajada::AST::TupleAccessByInteger($[source], $[field]);
}

/* §3.4.6p5 */
| expr[source] TUPLE_ARROW IDENT[field]
{
        auto tp = dynamic_cast<Tajada::Type::Tuple *>($[source]->type);

        if (tp == nullptr) {
                error(@$, u8"Attempt to access tuple field by name on expression of non‐tuple type");
                YYERROR;
        }

        if ((*tp)[*$[field]] == nullptr) {
                error(@$, u8"Attempt to access nonexistent named tuple field");
                YYERROR;
        }

        $$ = new Tajada::AST::TupleAccessByName($[source], $[field]);
}

/* §3.4.6p8 */
| expr[source] ARRAY_ACCESS_OP expr[position] ARRAY_ACCESS_CL
{
        auto ap = dynamic_cast<Tajada::Type::Array *>($[source]->type);

        if (ap == nullptr) {
                error(@$, u8"Attempt to access array element on expression of non‐array type");
                YYERROR;
        }

        auto ip = dynamic_cast<Tajada::Type::Integer *>($[position]->type);

        if (ip == nullptr) {
                error(@$, u8"Attempt to access array element on non‐integer position");
                YYERROR;
        }

        $$ = new Tajada::AST::ArrayAccess($[source], $[position]);
}

/* §3.4.6p10 */
| expr[l] EXPR_LIST_SEP expr[r]
{ $$ = new Tajada::AST::Sequence($[l], $[r]); }

;



intlit
: LIT_INT[token]
{ $$ = new Tajada::AST::Literal::Integer($[token]); }



operator

/* §3.4.3.2l1.1 */ : OP_MINUS[op] { $$ = new std::tuple<std::string *, Tajada::AST::Operator>($[op], Tajada::AST::Operator::minus); }
/* §3.4.3.2l1.2 */ | OP_PLUS [op] { $$ = new std::tuple<std::string *, Tajada::AST::Operator>($[op], Tajada::AST::Operator::plus ); }
/* §3.4.3.2l1.3 */ | OP_MULT [op] { $$ = new std::tuple<std::string *, Tajada::AST::Operator>($[op], Tajada::AST::Operator::mult ); }
/* §3.4.3.2l1.4 */ | OP_DIV  [op] { $$ = new std::tuple<std::string *, Tajada::AST::Operator>($[op], Tajada::AST::Operator::div  ); }
/* §3.4.3.2l1.5 */ | OP_MOD  [op] { $$ = new std::tuple<std::string *, Tajada::AST::Operator>($[op], Tajada::AST::Operator::mod  ); }
/* §3.4.3.2l1.6 */ | OP_EQ   [op] { $$ = new std::tuple<std::string *, Tajada::AST::Operator>($[op], Tajada::AST::Operator::eq   ); }
/* §3.4.3.2l1.7 */ | OP_NEQ  [op] { $$ = new std::tuple<std::string *, Tajada::AST::Operator>($[op], Tajada::AST::Operator::neq  ); }

;



/* §3.4.1.2p4 */
tuple_elems

: tuple_elems[xs] LIST_SEP tuple_elem[x]
{ $[xs]->push_back($[x]); $$ = $[xs]; }

| tuple_elem[x]
{ $$ = new std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *>(1, $[x]); }

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

: BLOCK_OP
{
        auto ns = new Scope(
                scope,
                scope->type == Tajada::Scope::Type::global
                ? Tajada::Scope::Type::main
                : Tajada::Scope::Type::unspecified
        );
        scope->children.insert(ns);
        scope = ns;
} blocklevels[statements] {
        scope = scope->parent;
} BLOCK_CL {
        $$ = new Tajada::AST::Block($[statements]);
}

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

/* TODO: check for bool condition */
/* §3.5.2.1p3 */
| IF PAREN_OP expr[condition] PAREN_CL body[body_true] ELSE body[body_false]
{ $$ = new Tajada::AST::If($[condition], $[body_true], $[body_false]); }

/* TODO: check for bool condition */
| IF PAREN_OP expr[condition] PAREN_CL body[body_true]
{ $$ = new Tajada::AST::If($[condition], $[body_true], new Tajada::AST::Block(new std::list<Tajada::AST::Statement *>())); }

/* TODO: check for bool condition */
/* §3.5.2.2p2 */
| WHILE PAREN_OP expr[condition] PAREN_CL body
{ $$ = new Tajada::AST::While($[condition], $[body]); }

/* TODO */
/* §3.5.2.3p4 */
/*| FOR IDENT IN PAREN_OP expr RANGE_SEP expr PAREN_CL body*/

/* §3.5.2.5p2 */
| RETURN expr[retornado] STMT_END
{
        if (
                scope->type == Tajada::Scope::Type::main
                || scope->type == Tajada::Scope::Type::main_intermediate
        ) {
                if (Tajada::Type::Integer() != *$[retornado]->type) {
                        error(
                                @$,
                                u8"returning “"
                                + $[retornado]->type->show()
                                + u8"” from main block; expected “"
                                + Tajada::Type::Integer().show()
                                + u8"”"
                        );
                        YYERROR;
                }
        } else if (
                scope->type == Tajada::Scope::Type::function
                || scope->type == Tajada::Scope::Type::function_intermediate
        ) {
                if (*scope->declaration->codomain != *$[retornado]->type) {
                        error(
                                @$,
                                u8"returning “"
                                + $[retornado]->type->show()
                                + u8"” from function declared as returning “"
                                + scope->declaration->codomain->show()
                                + u8"”"
                        );
                        YYERROR;
                }
        }
}

/* TODO: union switch/case */
/* TODO: fin/break */

;



body
: statement
{ $$ = $[statement]; }

| block
{ $$ = $[block]; }

;



%%



void Tajada::yy::parser::error(location_type const & l, std::string const & msg) {
        if (l.begin.filename) std::cerr << *l.begin.filename << u8":";
        if (l.begin.line == l.end.line) {
                if (l.begin.column == l.end.column - 1) {
                        std::cerr
                                << l.begin.line
                                << u8":"
                                << l.begin.column
                                << u8": ";
                } else {
                        std::cerr
                                << l.begin.line
                                << u8":"
                                << l.begin.column
                                << u8"–"
                                << l.end.column
                                << u8": ";
                }
        } else {
                std::cerr
                        << u8"("
                        << l.begin.line
                        << u8","
                        << l.begin.column
                        << u8")–("
                        << l.end.line
                        << u8","
                        << l.end.column
                        << u8"): ";
        }

        std::cerr << msg << std::endl;
}
