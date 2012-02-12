#ifndef TAJADA_LEX_HH
#define TAJADA_LEX_HH

#include <tuple>
#include <vector>

#include <re2/re2.h>

#include "parser.tab.hh"
#include "tokens.hh"

#define TAJADA_TOKEN_TUPLE_TYPES Token, unsigned int, char const *, char const *, char const *, re2::RE2 *
#define        TAJADA_TOKEN_ENUM(t) std::get<0>(t)
#define  TAJADA_TOKEN_BISON_ENUM(t) std::get<1>(t)
#define         TAJADA_TOKEN_TAG(t) std::get<2>(t)
#define TAJADA_TOKEN_DESCRIPTION(t) std::get<3>(t)
#define       TAJADA_TOKEN_REGEX(t) std::get<4>(t)
#define         TAJADA_TOKEN_RE2(t) std::get<5>(t)


namespace tajada {
        namespace lex {
#define TAJADA_TOKEN_TAGS(tag, description, regex, type) tag,
                enum class Token : unsigned int { TAJADA_TOKEN_DATA(TAJADA_TOKEN_TAGS) };
#undef TAJADA_TOKEN_TAGS

                extern std::vector<std::tuple<TAJADA_TOKEN_TUPLE_TYPES>> ts;

                extern re2::RE2 * re_line;
                extern re2::RE2 * re_int;

                struct scanner {
                        re2::StringPiece * in;

                        unsigned int line;
                        unsigned int col;
                        unsigned int errors;

                        scanner(re2::StringPiece * in);
                };

                int yylex(tajada::yy::parser::semantic_type * s, tajada::yy::parser::location_type * l, tajada::lex::scanner * state);

                void init(void);
        }
}

#endif
