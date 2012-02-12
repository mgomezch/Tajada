#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include <re2/re2.h>
#include <sysexits.h>

#include "lex.hh"
#include "parser.tab.hh"
#include "tokens.hh"

#define TAJADA_DEBUG_LEXER 1

#define TAJADA_SCANNER_INIT_FIXED_REGEX(var, str)                                         \
        do {                                                                              \
                var = new re2::RE2(std::string(str), o);                                  \
                if (!var->ok()) {                                                         \
                        std::cerr                                                         \
                                << u8"Parse error in regex " #var ": "                    \
                                << r->error()                                             \
                                << std::endl;                                             \
                        std::exit(EX_SOFTWARE);                                           \
                }                                                                         \
                {}{                                                                       \
                        int n = var->NumberOfCapturingGroups();                           \
                        if (n < 1) {                                                      \
                                std::cerr                                                 \
                                        << u8"Error in regex “"                           \
                                        << #var                                           \
                                        << u8"”: at least one capture group is required." \
                                        << std::endl;                                     \
                                std::exit(EX_SOFTWARE);                                   \
                        }                                                                 \
                        nmatch = std::max(nmatch, n);                                     \
                }                                                                         \
        } while (0)

namespace tajada {
        namespace lex {
                int nmatch = -1;

#define TAJADA_TOKEN_TUPLES(tag, description, regex, type) std::make_tuple<TAJADA_TOKEN_TUPLE_TYPES>(Token::tag, yy::parser::token::tag, #tag, description, regex, NULL),
                std::vector<std::tuple<TAJADA_TOKEN_TUPLE_TYPES>> ts = { TAJADA_TOKEN_DATA(TAJADA_TOKEN_TUPLES) };
#undef TAJADA_TOKEN_TUPLES

                re2::RE2 * re_line;
                re2::RE2 * re_int;

                scanner::scanner(re2::StringPiece * in):
                        in(in),
                        line(1),
                        col(1),
                        errors(0)
                {
                        if (nmatch > 0) {
                                match = new re2::StringPiece[nmatch];
                                // TODO: check for error
                        } else match = NULL;
                }

                scanner::~scanner() {
                        if (match != NULL) delete [] match;
                }

                int yylex(yy::parser::semantic_type * s, yy::parser::location_type * l, scanner * state) {
                        unsigned int endline, endcol;
                        std::string text_line;
                        std::string text;
                        int bytes;

                        if (state->in->length() <= 0 || state->in->data()[0] == '\0') {
#if TAJADA_DEBUG_LEXER
                                std::cerr << "Done." << std::endl;
#endif
                                return 0;
                        }
                        for (auto it = ts.begin(); it != ts.end(); ++it) {
                                if (
                                        TAJADA_TOKEN_RE2(*it) == NULL ||
                                        !TAJADA_TOKEN_RE2(*it)->Match(
                                                *state->in,
                                                0,
                                                state->in->length(),
                                                re2::RE2::ANCHOR_START,
                                                state->match,
                                                1 + TAJADA_TOKEN_RE2(*it)->NumberOfCapturingGroups()
                                        )
                                ) continue;

                                endline = state->line;
                                endcol  = state->col;

                                {}{
                                          re2::StringPiece textpiece(state->match[1]);
                                          while (re2::RE2::FindAndConsume(&textpiece, *re_line)) {
                                                  ++endline;
                                                  endcol = 0;
                                          }
                                          for (auto it = textpiece.begin(); it != textpiece.end(); ++it) {
                                                  if ((1 << 7) & *it) continue;
                                                  ++endcol;
                                          }
                                }

#if TAJADA_DEBUG_LEXER
                                std::cerr
                                        << u8"Found token “"
                                        << TAJADA_TOKEN_TAG(*it)
                                        << u8"” matching text “"
                                        << text
                                        << u8"” ";
                                if (state->line == endline && state->col == endcol - 1) {
                                        std::cerr
                                                << u8"at line "
                                                << state->line
                                                << u8", column "
                                                << state->col
                                                << std::endl;
                                } else {
                                        std::cerr
                                                << u8"spanning range ("
                                                << state->line
                                                << u8", "
                                                << state->col
                                                << u8")–("
                                                << endline
                                                << u8", "
                                                << endcol - 1
                                                << u8")"
                                                << std::endl;
                                }
#endif

                                l->begin.line   = state->line;
                                l->begin.column = state->col;
                                l->end.line     = endline;
                                l->end.column   = endcol;

                                state->line = endline;
                                state->col  = endcol;

                                // TODO: set s
                                switch (TAJADA_TOKEN_ENUM(*it)) {
                                        case tajada::lex::Token::IGNORE:
                                                return yylex(s, l, state);
                                        case tajada::lex::Token::LIT_STR:
                                                // TODO: eliminar delimitadores del string y backslashes escapadores
                                                s->LIT_STR = new std::string(text);
                                                break;
                                        case tajada::lex::Token::LIT_CHR:
                                                s->LIT_CHR = new std::string(text.substr(1));
                                                break;
                                        case tajada::lex::Token::LIT_INT:
                                                RE2::FullMatch(text, *re_int, &s->LIT_INT);
                                                break;
                                        default:
                                                break;
                                }

                                return TAJADA_TOKEN_BISON_ENUM(*it);
                        }

                        for (bytes = 1; bytes < 8; ++bytes) {
                                if (!((state->in->data()[0] >> (8 - bytes)) & 1)) {
                                        if (bytes > 1) --bytes;
                                        break;
                                }
                        }
                        std::cerr
                                << u8"Skipping unrecognized "
                                << bytes
                                << u8"‐byte character ‘";
                        for (int i = 0; i < bytes; ++i) std::cerr << state->in->data()[i];
                        std::cerr
                                << u8"’ at line "
                                << state->line
                                << u8", column "
                                << state->col
                                << u8"."
                                << std::endl;
                        // TODO: handle lexical errors

                        state->in->remove_prefix(bytes);
                        ++(state->errors);
                        ++(state->col);

                        return yylex(s, l, state);
                }



                void init(void) {
                        int n;

                        re2::RE2::Options o;
                        o.set_encoding      (re2::RE2::Options::Encoding::EncodingUTF8);
                        o.set_posix_syntax  (false);
                        o.set_longest_match (false);
                        o.set_log_errors    (true );
                        o.set_literal       (false);
                        o.set_never_nl      (false);
                        o.set_case_sensitive(true );

                        re2::RE2 * r;
                        for (auto it = ts.begin(); it != ts.end(); ++it) {
                                r = new re2::RE2(std::string(TAJADA_TOKEN_REGEX(*it)), o);
                                if (!r->ok()) {
                                        std::cerr
                                                << u8"Skipping regexp for token “"
                                                << TAJADA_TOKEN_TAG(*it)
                                                << u8"” due to parse error: "
                                                << r->error()
                                                << std::endl;
                                        delete r;
                                        r = NULL;
                                } else {
                                        n = r->NumberOfCapturingGroups();

                                        if (n < 1) {
                                                std::cerr
                                                        << u8"Error in regex for token “"
                                                        << TAJADA_TOKEN_TAG(*it)
                                                        << u8"”: at least one capture group is required."
                                                        << std::endl;
                                                std::exit(EX_SOFTWARE);
                                        }
                                        nmatch = std::max(nmatch, n);

#if TAJADA_DEBUG_LEXER
                                        std::cerr
                                                << u8"Parsed regexp for token “"
                                                << TAJADA_TOKEN_TAG(*it)
                                                << u8"”"
                                                << std::endl;
#endif

                                }
                                TAJADA_TOKEN_RE2(*it) = r;
                        }

                        TAJADA_SCANNER_INIT_FIXED_REGEX(re_line, u8"([" TAJADA_ENDLINES "])");
                        TAJADA_SCANNER_INIT_FIXED_REGEX(re_int , u8"([0-9]+)"               );
                }
        }
}
