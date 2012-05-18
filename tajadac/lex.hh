#ifndef TAJADA_LEX_HH
#define TAJADA_LEX_HH

#include <tuple>
#include <unordered_set>
#include <vector>

#include <re2/re2.h>

#include "parser.tab.hh"
#include "tokens.hh"
#include "ast.hh"



#define TAJADA_TOKEN_TUPLE_TYPES \
        Tajada::lex::Token  ,    \
        unsigned int        ,    \
        char const         *,    \
        char const         *,    \
        char const         *,    \
        re2::RE2           *
#define        TAJADA_TOKEN_ENUM(t) std::get<0>(t)
#define  TAJADA_TOKEN_BISON_ENUM(t) std::get<1>(t)
#define         TAJADA_TOKEN_TAG(t) std::get<2>(t)
#define TAJADA_TOKEN_DESCRIPTION(t) std::get<3>(t)
#define       TAJADA_TOKEN_REGEX(t) std::get<4>(t)
#define         TAJADA_TOKEN_RE2(t) std::get<5>(t)



namespace Tajada {
        namespace lex {
                // Tamaño del arreglo de grupos de captura necesario para el conjunto de expresiones regulares usado.
                extern int nmatch;

                enum class Token : unsigned int {
#define TAJADA_TOKEN_TAGS(tag, description, regex, type) tag,
                        TAJADA_TOKEN_DATA(TAJADA_TOKEN_TAGS)
#undef TAJADA_TOKEN_TAGS
                };

                extern re2::RE2 * re_line;

                class Scanner {
                        public:
                                std::vector<std::tuple<TAJADA_TOKEN_TUPLE_TYPES>> ts;
                                std::unordered_set<std::string> reserved_symbols;
                                std::string reserved_symbols_string;

                                re2::StringPiece * in;
                                re2::StringPiece * match;

                                unsigned int line;
                                unsigned int col;
                                unsigned int errors;

                                std::unordered_map<
                                        unsigned int,
                                        std::unordered_set<std::string>
                                > infix_ops;

                                Scanner(re2::StringPiece * p_in);
                                ~Scanner();

                                void build();

                                std::string ident_piece;
                };

                int yylex(
                        Tajada::yy::parser::semantic_type * s      ,
                        Tajada::yy::parser::location_type * l      ,
                        Tajada::lex::Scanner              * scanner
                );

                void init();

                // TODO: add forward-declaration of this function to parser.y
                void add_infix(
                        Tajada::lex::Scanner       * scanner      ,
                        std::string                  identifier   ,
                        Tajada::AST::Associativity   associativity,
                        unsigned int                 predecende
                );
        }
}

#endif
