/* Para GNU Bison */

%require "2.5"

%language "C++"
%define namespace "Tajada::yy"

%debug
%defines
%error-verbose
%verbose



%code {
        /* Forward‐declaration of lexer functions.  Don’t ask. */
        namespace Tajada {
                namespace lex {
#undef yylex
                        int yylex(
                                Tajada::yy::parser::semantic_type * s    ,
                                Tajada::yy::parser::location_type * l    ,
                                Tajada::lex::Scanner              * state
                        );

                        void add_infix(
                                Tajada::lex::Scanner       * scanner      ,
                                std::string                  identifier   ,
                                Tajada::AST::Associativity   associativity,
                                unsigned int                 precedence
                        );

#define yylex Tajada::lex::yylex
                }
        }
}

/* This doesn’t work.  We’d have to pollute the lexer code with forward‐declarations for …well, everything.  Fuck that. */
/* %name-prefix "Tajada::lex::yy" */


%code requires {
        /* Forward‐declaration of lexer class.  Don’t ask. */
        namespace Tajada {
                namespace lex {
                        class Scanner;
                }
        }
}

/* This doesn’t work.  We’d have to pollute the lexer code with forward‐declarations for …well, everything.  Fuck that. */
/* %code requires { #include "lex.hh" } */


%code requires {
        #include "Tajada/Type.hh"
        #include "Tajada/Builtins.hh"
}



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
                        if (it->first != *nombre) continue;                          \
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
        if (!s) {                                                                    \
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


%code requires { #include "scope.hh"   }
%parse-param   { Tajada::Scope * scope }


%code requires { #include "Tajada/AST.hh" }
%parse-param   { Tajada::AST::AST ** tree }



%locations
%parse-param    { std::string * filename                          }
%initial-action { @$.begin.filename = @$.end.filename = filename; }



%nonassoc CALL
%left     EXPR_LIST_SEP

%left INFIXL0 %nonassoc INFIX0 %right INFIXR0
%left INFIXL1 %nonassoc INFIX1 %right INFIXR1
%left INFIXL2 %nonassoc INFIX2 %right INFIXR2
%left INFIXL3 %nonassoc INFIX3 %right INFIXR3
%left INFIXL4 %nonassoc INFIX4 %right INFIXR4
%left INFIXL5 %nonassoc INFIX5 %right INFIXR5
%left INFIXL6 %nonassoc INFIX6 %right INFIXR6
%left INFIXL7 %nonassoc INFIX7 %right INFIXR7
%left INFIXL8 %nonassoc INFIX8 %right INFIXR8
%left INFIXL9 %nonassoc INFIX9 %right INFIXR9

%nonassoc TUPLE_ARROW
%nonassoc ARRAY_ACCESS_OP
%nonassoc PAREN_CL

%right ELSE



%token_data
%token END 0 "fin del documento"



%union { Tajada::AST::Program                                                     * tajada             ; } %type <tajada>              tajada
%union { std::list<Tajada::AST::Statement *>                                      * statements         ; } %type <statements>          toplevels blocklevels
%union { Tajada::AST::Statement                                                   * statement          ; } %type <statement>           toplevel blocklevel statement body
%union { Tajada::AST::Block                                                       * block              ; } %type <block>               block
%union { Tajada::Type::Type                                                       * typespec           ; } %type <typespec>            typespec
%union { std::tuple<Tajada::Type::Type *, std::string *>                          * structure_typespec ; } %type <structure_typespec>  structure_typespec
%union { std::vector<std::tuple<Tajada::Type::Type *, std::string *> *>           * structure_typespecs; } %type <structure_typespecs> structure_typespecs structure_types
%union { Tajada::AST::VariableDefinition                                          * var_def            ; } %type <var_def>             var_def
%union { Tajada::AST::Expression                                                  * expr               ; } %type <expr>                expr
%union { Tajada::AST::Literal::Integer                                            * intlit             ; } %type <intlit>              intlit
%union { std::tuple<Tajada::AST::Expression *, std::string *>                     * tuple_elem         ; } %type <tuple_elem>          tuple_elem
%union { std::vector<std::tuple<Tajada::AST::Expression *, std::string *> *>      * tuple_elems        ; } %type <tuple_elems>         tuple_elems
%union { std::tuple<Tajada::AST::FunctionDeclaration *, Tajada::AST::Function **> * func_spec          ; } %type <func_spec>           func_spec
%union { std::vector<Tajada::AST::TypeCase::TypeCase *>                           * cases              ; } %type <cases>               cases
%union { Tajada::AST::Expression                                                  * union_access       ; } %type <union_access>        union_access
%union { Tajada::AST::Associativity                                                 associativity      ; } %type <associativity>       associativity
%union { Tajada::AST::FunctionID                                                  * func_id            ; } %type <func_id>             func_id
%union { std::string                                                              * infix_op           ; } %type <infix_op>            infix_op



%start tajada

%%



/* §3p1 */
tajada

: toplevels[statements] block[main]
{
        bool found_undefined = false;
        for (auto it = scope->functions.begin(); it != scope->functions.end(); ++it) {
                if (!*std::get<2>(it->second)) {
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


/* TODO: sección */
| toplevels[xs] IDENT[nombre] ES INFIX associativity LIT_INT[precedence] STMT_END
{
        /* TODO: some error checking is in order here:
         *       *    the new operator becomes a reserved symbol, so bad things happen if its text is a substring of a reserved word.start with a code point that’s contained anywhere in any reserved word (otherwise the new lexer wouldn’t be able to lex those tokens anymore, as they’d get split up).
         *       *    it shouldn’t make the new lexer ambiguous
         *       *    we have to escape the operator string (it could contain special regex chars)
         */

        auto p = std::stoi(*$[precedence]);
        if (p < 0 || 9 < p) {
                error(
                        @[associativity],
                        u8"invalid precedence “"
                        + *$[precedence]
                        + u8"” specified for infix operator “"
                        + *$[nombre]
                        + u8"”"
                );
                YYERROR;
        }

        Tajada::lex::add_infix(
                scanner,
                *$[nombre],
                $[associativity],
                std::stoi(*$[precedence])
        );

        $$ = $[xs];
}


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
        scope->define_variable(
                *std::get<0>(*$[func_spec])->domain_name,
                std::get<0>(*$[func_spec])->domain
        );
} blocklevels[statements] {
        //scope = scope->parent;
} BLOCK_CL {
        auto ret = new Tajada::AST::FunctionDefinition(
                std::get<0>(*$[func_spec]),
                new Tajada::AST::Block($[statements], scope)
        );

        scope = scope->parent;

        *std::get<1>(*$[func_spec]) = ret;
        $$ = ret;
        delete $[func_spec];
}


/* TODO: sección */
| func_spec BUILTIN IDENT[nombre] STMT_END {
        unsigned int ncs = 0;
        std::string name = *$[nombre];

        auto bucket = Tajada::Builtins::builtins.bucket(*$[nombre]);

        auto it = Tajada::Builtins::builtins.begin(bucket);
        for (; it != Tajada::Builtins::builtins.end(bucket); ++it) {
                if (*$[nombre] == it->first) {
                        ++ncs;

                        if (
                                   *std::get<0>(*$[func_spec])->domain   == *std::get<0>(it->second)
                                && *std::get<0>(*$[func_spec])->codomain == *std::get<1>(it->second)
                        ) {
                                break;
                        }
                }
        }

        if (it == Tajada::Builtins::builtins.end(bucket)) {
                error(
                        @$,
                        u8"invalid definition of “"
                        + *std::get<0>(*$[func_spec])->id->name
                        + u8"” taking “"
                        + std::get<0>(*$[func_spec])->domain->show()
                        + u8"” and returning “"
                        + std::get<0>(*$[func_spec])->codomain->show()
                        + u8"” as builtin “"
                        + *$[nombre]
                        + u8"”"
                );
                if (!ncs) {
                        error(
                                @$,
                                u8"no builtins named “"
                                + *$[nombre]
                                + u8"”"
                        );
                } else {
                        error(
                                @$,
                                u8"candidates are:"
                        );
                        std::for_each(
                                Tajada::Builtins::builtins.begin(bucket),
                                Tajada::Builtins::builtins.end(bucket),
                                [this, &yyloc, &name](decltype(*Tajada::Builtins::builtins.end()) c) {
                                        if (name != c.first) return;
                                        error(
                                                @$,
                                                std::get<0>(c.second)->show()
                                                + u8" x con salsa de "
                                                + std::get<1>(c.second)->show()
                                        );
                                }
                        );
                }
                YYERROR;
        }

        auto ret = new Tajada::AST::BuiltinFunction(
                $[nombre],
                std::get<0>(*$[func_spec]),
                std::get<2>(it->second),
                std::get<3>(it->second)
        );

        $$ = *std::get<1>(*$[func_spec]) = ret;
        delete $[func_spec];
}


;



func_spec

/* TODO: sección; las viejas eran §3.1.2p5 y §3.1.3p5 */
: func_id DE typespec[dominio] IDENT[nombre_dominio] CON SALSA DE typespec[codominio]
{
        if (dynamic_cast<Tajada::AST::InfixFunctionID *>($[func_id])) {
                auto t = dynamic_cast<Tajada::Type::Tuple *>($[dominio]);

                if (!t) {
                        error(
                                @[dominio],
                                u8"Domain of infix function “"
                                + *$[func_id]->name
                                + u8"” declared as non‐tuple type “"
                                + $[dominio]->show()
                                + u8"”"
                        );
                        YYERROR;
                }

                if (t->elems->size() != 2) {
                        error(
                                @[dominio],
                                u8"Domain of infix function “"
                                + *$[func_id]->name
                                + u8"” declared as tuple of size "
                                + std::to_string(t->elems->size())
                                + u8"; expected size 2"
                        );
                        YYERROR;
                }
        }

        auto bucket = scope->functions.bucket(*$[func_id]->name);
        bool insert = true;

        auto it = scope->functions.begin(bucket);
        for (; it != scope->functions.end(bucket); ++it) {
                // TODO: ponerlo así para meterle sobrecarga más bonita
                // if (*$[dominio] != *std::get<0>(it->second) || *$[codominio] != *std::get<1>(it->second)) continue;
                if (*$[func_id]->name != it->first || *$[dominio] != *std::get<0>(it->second)) continue;

                if (*$[codominio] != *std::get<1>(it->second)) {
                        error(
                                @$,
                                u8"Conflicting types for “"
                                + *$[func_id]->name
                                + u8"” taking “"
                                + $[dominio]->show()
                                + u8"”"
                        );
                        error(
                                std::get<3>(it->second),
                                u8"“"
                                + it->first
                                + u8"” was first declared here"
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
                                *$[func_id]->name,
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
                new Tajada::AST::FunctionDeclaration(
                        $[func_id],
                        $[nombre_dominio],
                        $[dominio],
                        $[codominio]
                ),
                r
        );
}

;



func_id

/* TODO: sección */
: IDENT[nombre] ES UN PLATO { $$ = new Tajada::AST::PrefixFunctionID($[nombre]); }

/* TODO: sección */
| INFIXL0[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIX0[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIXR0[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); }
| INFIXL1[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIX1[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIXR1[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); }
| INFIXL2[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIX2[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIXR2[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); }
| INFIXL3[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIX3[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIXR3[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); }
| INFIXL4[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIX4[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIXR4[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); }
| INFIXL5[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIX5[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIXR5[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); }
| INFIXL6[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIX6[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIXR6[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); }
| INFIXL7[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIX7[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIXR7[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); }
| INFIXL8[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIX8[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIXR8[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); }
| INFIXL9[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIX9[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); } | INFIXR9[nombre] ES UN PLATO { $$ = new Tajada::AST::InfixFunctionID($[nombre]); }

;



/* TODO: sección */
associativity
: LEFT  { $$ = Tajada::AST::Associativity::left ; }
| RIGHT { $$ = Tajada::AST::Associativity::right; }
|       { $$ = Tajada::AST::Associativity::none ; }
;



/* §3.2.1p4 */
var_def
: IDENT[nombre] ES typespec[tipo] STMT_END
{
        if (scope->variable_type(*$[nombre])) {
                error(
                        @$,
                        u8"redefinition of “"
                        + *$[nombre]
                        + u8"”"
                );
                YYERROR;
        }
        scope->define_variable(*$[nombre], $[tipo]);
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

        if (!s) {
                error(
                        @[nombre],
                        std::string("type alias “")
                        + *$[nombre]
                        + "”"
                );
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
| REF_OP typespec[referido] REF_CL
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

/* TODO: sección */
|             IDENT[nombre]          CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) }
| PAREN_OP infix_op[nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) }

/* TODO: sección */
| expr[l] INFIXL0[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIX0[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIXR0[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
| expr[l] INFIXL1[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIX1[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIXR1[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
| expr[l] INFIXL2[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIX2[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIXR2[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
| expr[l] INFIXL3[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIX3[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIXR3[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
| expr[l] INFIXL4[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIX4[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIXR4[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
| expr[l] INFIXL5[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIX5[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIXR5[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
| expr[l] INFIXL6[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIX6[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIXR6[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
| expr[l] INFIXL7[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIX7[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIXR7[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
| expr[l] INFIXL8[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIX8[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIXR8[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }
| expr[l] INFIXL9[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIX9[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } | expr[l] INFIXR9[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) }

/* §3.4.2p2     */ /*|             IDENT[nombre]          CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) }                                                                                                 */
/* §3.4.3.2l1.1 */ /*| PAREN_OP OP_MINUS[nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_MINUS[nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } */
/* §3.4.3.2l1.2 */ /*| PAREN_OP OP_PLUS [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_PLUS [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } */
/* §3.4.3.2l1.3 */ /*| PAREN_OP OP_MULT [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_MULT [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } */
/* §3.4.3.2l1.4 */ /*| PAREN_OP OP_DIV  [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_DIV  [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } */
/* §3.4.3.2l1.5 */ /*| PAREN_OP OP_MOD  [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_MOD  [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } */
/* §3.4.3.2l1.6 */ /*| PAREN_OP OP_EQ   [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_EQ   [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } */
/* §3.4.3.2l1.7 */ /*| PAREN_OP OP_NEQ  [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_NEQ  [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } */
/* §3.4.3.2l1.8 */ /*| PAREN_OP OP_LT   [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_LT   [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } */
/* §3.4.3.2l1.9 */ /*| PAREN_OP OP_GT   [nombre] PAREN_CL CALL expr[argumento] { TAJADA_CALL_UNARY($[nombre], $[argumento], $$, @[nombre]) } | expr[l] OP_GT   [nombre] expr[r] { TAJADA_CALL_BINARY($[nombre], $[l], $[r], $$, @[nombre]) } */

/* §3.4.4p2 */
| IDENT[nombre]
{
        auto s = scope;
        Tajada::Type::Type * t;

        while (s != nullptr) {
                if ((t = s->variable_type(*$[nombre]))) break;
                s = s->parent;
        }

        if (!s) {
                error(
                        @[nombre],
                        u8"“"
                        + *$[nombre]
                        + u8"” was not declared in this scope"
                );
                YYERROR;
        }

        $$ = new Tajada::AST::VariableUse(s, $[nombre], t);
}

/* §3.4.6p3 */
| PAREN_OP expr[in] PAREN_CL
{ $$ = $[in]; }

/* §3.4.6p5 */
| expr[source] TUPLE_ARROW intlit[field]
{
        auto tp = dynamic_cast<Tajada::Type::Tuple *>($[source]->type);

        if (!tp) {
                error(@$, u8"Attempt to access numbered tuple field by number on expression of non‐tuple type");
                YYERROR;
        }

        if (!(*tp)[$[field]->value]) {
                error(@$, u8"Attempt to access nonexistent tuple field");
                YYERROR;
        }

        $$ = new Tajada::AST::TupleAccessByInteger($[source], $[field]);
}

/* §3.4.6p5 */
| expr[source] TUPLE_ARROW IDENT[field]
{
        auto tp = dynamic_cast<Tajada::Type::Tuple *>($[source]->type);

        if (!tp) {
                error(@$, u8"Attempt to access tuple field by name on expression of non‐tuple type");
                YYERROR;
        }

        if (!(*tp)[*$[field]]) {
                error(@$, u8"Attempt to access nonexistent named tuple field");
                YYERROR;
        }

        $$ = new Tajada::AST::TupleAccessByName($[source], $[field]);
}

/* §3.4.6p8 */
| expr[source] ARRAY_ACCESS_OP expr[position] ARRAY_ACCESS_CL
{
        auto ap = dynamic_cast<Tajada::Type::Array *>($[source]->type);

        if (!ap) {
                error(@$, u8"Attempt to access array element on expression of non‐array type");
                YYERROR;
        }

        auto ip = dynamic_cast<Tajada::Type::Integer *>($[position]->type);

        if (!ip) {
                error(@$, u8"Attempt to access array element on non‐integer position");
                YYERROR;
        }

        $$ = new Tajada::AST::ArrayAccess($[source], $[position]);
}

/* §3.4.6p10 */
| expr[l] EXPR_LIST_SEP expr[r]
{ $$ = new Tajada::AST::Sequence($[l], $[r]); }

;



/* TODO: sección.
 *       old refs:
 *           §3.4.3.2l1.1
 *           §3.4.3.2l1.2
 *           §3.4.3.2l1.3
 *           §3.4.3.2l1.4
 *           §3.4.3.2l1.5
 *           §3.4.3.2l1.6
 *           §3.4.3.2l1.7
 *           §3.4.3.2l1.8
 *           §3.4.3.2l1.9
 */
infix_op
: INFIXL0 | INFIX0 | INFIXR0
| INFIXL1 | INFIX1 | INFIXR1
| INFIXL2 | INFIX2 | INFIXR2
| INFIXL3 | INFIX3 | INFIXR3
| INFIXL4 | INFIX4 | INFIXR4
| INFIXL5 | INFIX5 | INFIXR5
| INFIXL6 | INFIX6 | INFIXR6
| INFIXL7 | INFIX7 | INFIXR7
| INFIXL8 | INFIX8 | INFIXR8
| INFIXL9 | INFIX9 | INFIXR9
;



intlit
: LIT_INT[token]
{ $$ = new Tajada::AST::Literal::Integer($[token]); }



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
        //scope = scope->parent;
} BLOCK_CL {
        $$ = new Tajada::AST::Block($[statements], scope);

        scope = scope->parent;
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
| expr[l] ASSIGN expr[r] STMT_END
{
        if (!$[l]->is_lvalue) {
                error(
                        @$,
                        u8"lvalue required as left operand of assignment");
                YYERROR;
        }

        if (*$[l]->type != *$[r]->type) {
                error(
                        @$,
                        u8"incompatible types in assignment"
                );
                std::cerr << "lhs is " << $[l]->type->show() << std::endl;
                std::cerr << "rhs is " << $[r]->type->show() << std::endl;
                YYERROR;
        }

        $$ = new Tajada::AST::Assignment($[l], $[r]);
}

/* §3.5.1p7 */
| union_access[l] ASSIGN expr[r] STMT_END
{
        if (!$[l]->is_lvalue) {
                error(
                        @$,
                        u8"lvalue required as left operand of assignment");
                YYERROR;
        }

        if (*$[l]->type != *$[r]->type) {
                error(
                        @$,
                        u8"incompatible types in assignment"
                );
                std::cerr << "lhs is " << $[l]->type->show() << std::endl;
                std::cerr << "rhs is " << $[r]->type->show() << std::endl;
                YYERROR;
        }

        $$ = new Tajada::AST::Assignment($[l], $[r]);
}

/* §3.5.2.1p3 */
| IF PAREN_OP expr[condition] PAREN_CL body[cuerpo_positivo] ELSE body[cuerpo_negativo]
{
        if (*$[condition]->type != Tajada::Type::Boolean()) {
                error(
                        @[condition],
                        u8"condition requires boolean, but has type “"
                        + $[condition]->type->show()
                        + u8"”"
                );
                YYERROR;
        }

        $$ = new Tajada::AST::If($[condition], $[cuerpo_positivo], $[cuerpo_negativo]);
}

| IF PAREN_OP expr[condition] PAREN_CL body[cuerpo]
{
        if (*$[condition]->type != Tajada::Type::Boolean()) {
                error(
                        @[condition],
                        u8"condition requires boolean, but has type “"
                        + $[condition]->type->show()
                        + u8"”"
                );
                YYERROR;
        }

        $$ = new Tajada::AST::If($[condition], $[cuerpo], nullptr);
}

/* §3.5.2.2p2 */
| WHILE PAREN_OP expr[condition] PAREN_CL {
        if (*$[condition]->type != Tajada::Type::Boolean()) {
                error(
                        @[condition],
                        u8"condition requires boolean, but has type “"
                        + $[condition]->type->show()
                        + u8"”"
                        + u8"; condition is “"
                        + $[condition]->show()
                        + u8"”"
                );
                YYERROR;
        }

        auto ns = new Scope(scope);
        scope->children.insert(ns);
        scope = ns;
} body[cuerpo] {
        scope = scope->parent;

        $$ = new Tajada::AST::While($[condition], $[cuerpo]);
}

/* §3.5.2.3p4 */
| FOR IDENT[contador] IN PAREN_OP expr[inicio] RANGE_SEP expr[fin] PAREN_CL {
        if (*$[inicio]->type != Tajada::Type::Integer()) {
                error(
                        @[inicio],
                        u8"range start requires integer, but has type “"
                        + $[inicio]->type->show()
                        + u8"”"
                );
                YYERROR;
        }

        if (*$[fin]->type != Tajada::Type::Integer()) {
                error(
                        @[fin],
                        u8"range end requires integer, but has type “"
                        + $[fin]->type->show()
                        + u8"”"
                );
                YYERROR;
        }

        auto ns = new Scope(scope);
        scope->children.insert(ns);
        scope = ns;

        scope->define_variable(*$[contador], new Tajada::Type::Integer());

        scope->structure = new Tajada::AST::For($[contador], $[inicio], $[fin], nullptr);
} body[cuerpo] {
        auto ret = dynamic_cast<Tajada::AST::For *>(scope->structure);
        scope = scope->parent;

        ret->body = $[cuerpo];
        $$ = ret;
}

/* §3.5.2.4p4 */
| expr[fuente] SWITCH IDENT[variable] BLOCK_OP {
        auto u = dynamic_cast<Tajada::Type::Union *>($[fuente]->type);
        if (!u) {
                error(
                        @$,
                        u8"type selection source requires union, but has type “"
                        + $[fuente]->type->show()
                        + u8"”"
                );
                YYERROR;
        }

        scope->switch_parameter = $[variable];
        scope->switch_union     = u;
} cases[casos] {
        scope->switch_union     = nullptr;
        scope->switch_parameter = nullptr;

        // TODO: check for repeated cases
} BLOCK_CL {
        $$ = new Tajada::AST::TypeSelection($[fuente], $[variable], $[casos]);
}

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

        $$ = new Tajada::AST::Return($[retornado]);
}

/* §3.5.2.6p2 */
| BREAK STMT_END
{
        if (!scope->structure) {
                error(
                        @$,
                        u8"break statement occurs outside of control structure"
                );
                YYERROR;
        }
        $$ = new Tajada::AST::Break(scope->structure);
}

;



cases

: cases[cs] LIT_INT[caso] CASE {
        auto ns = new Scope(scope);
        scope->children.insert(ns);
        scope = ns;

        auto case_type = (*scope->parent->switch_union)[std::stod(*$[caso])];

        if (!case_type) {
                error(
                        @$,
                        std::string(u8"case index “")
                        + *$[caso]
                        + u8"” is out of bounds for the type of the expression in its type selection: “"
                        + scope->parent->switch_union->show()
                        + u8"”"
                );
                YYERROR;
        }

        scope->define_variable(*scope->parent->switch_parameter, case_type);
} body[cuerpo] {
        scope = scope->parent;

        $[cs]->push_back(new Tajada::AST::TypeCase::Integer($[caso], $[cuerpo]));

        $$ = $[cs];
}

| cases[cs] IDENT[caso] CASE {
        auto ns = new Scope(scope);
        scope->children.insert(ns);
        scope = ns;

        auto case_type = (*scope->parent->switch_union)[*$[caso]];
        if (!case_type) {
                error(
                        @$,
                        std::string(u8"case label “")
                        + *$[caso]
                        + u8"” is not a member of the type of the expression in its type selection: “"
                        + scope->parent->switch_union->show()
                        + u8"”"
                );
                YYERROR;
        }
        scope->define_variable(*scope->parent->switch_parameter, case_type);
} body[cuerpo] {
        scope = scope->parent;

        $[cs]->push_back(new Tajada::AST::TypeCase::String($[caso], $[cuerpo]));

        $$ = $[cs];
}

|
{ $$ = new std::vector<Tajada::AST::TypeCase::TypeCase *>{}; }

;



body
: statement
{ $$ = $[statement]; }

| block
{ $$ = $[block]; }

;



union_access

/* §3.4.6p12 */
: expr[source] UNION_ARROW intlit[field]
{
        auto tp = dynamic_cast<Tajada::Type::Union *>($[source]->type);

        if (!tp) {
                error(@$, u8"Attempt to access numbered union field by number on expression of non‐union type");
                YYERROR;
        }

        if (!(*tp)[$[field]->value]) {
                error(@$, u8"Attempt to access nonexistent union field");
                YYERROR;
        }

        $$ = new Tajada::AST::UnionAccessByInteger($[source], $[field]);
}

/* §3.4.6p12 */
| expr[source] UNION_ARROW IDENT[field]
{
        auto tp = dynamic_cast<Tajada::Type::Union *>($[source]->type);

        if (!tp) {
                error(@$, u8"Attempt to access union field by name on expression of non‐union type");
                YYERROR;
        }

        if (!(*tp)[*$[field]]) {
                error(@$, u8"Attempt to access nonexistent named union field");
                YYERROR;
        }

        $$ = new Tajada::AST::UnionAccessByName($[source], $[field]);
}



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
