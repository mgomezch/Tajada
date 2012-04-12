#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <new>
#include <string>
#include <tuple>
#include <vector>

#include <re2/re2.h>
#include <sysexits.h>

#include "lex.hh"
#include "parser.tab.hh"
#include "tokens.hh"
#include "debug.hh"

#ifdef TAJADA_DEBUG
#       define TAJADA_DEBUG_LEXER TAJADA_DEBUG
#else
#       define TAJADA_DEBUG_LEXER 0
#endif

#if TAJADA_DEBUG_LEXER
#       define TAJADA_DEBUG_LEXER_PRINT(x) TAJADA_DEBUG_PRINT(LEXER, x)
#       define TAJADA_DEBUG_LEXER_DO(x) TAJADA_DEBUG_DO(LEXER, x)
#else
#       define TAJADA_DEBUG_LEXER_PRINT(x)
#       define TAJADA_DEBUG_LEXER_DO(x)
#endif

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

namespace Tajada {
        namespace lex {
                int nmatch = -1;

#define TAJADA_TOKEN_TUPLES(tag, description, regex, type) \
        std::make_tuple<TAJADA_TOKEN_TUPLE_TYPES>(         \
                Token::tag,                                \
                yy::parser::token::tag,                    \
                #tag,                                      \
                description,                               \
                regex,                                     \
                NULL                                       \
        ),
                std::vector<std::tuple<TAJADA_TOKEN_TUPLE_TYPES>> ts = { TAJADA_TOKEN_DATA(TAJADA_TOKEN_TUPLES) };
#undef TAJADA_TOKEN_TUPLES

                re2::RE2 * re_line;

                Scanner::Scanner(re2::StringPiece * p_in):
                        in    (p_in),
                        line  (1   ),
                        col   (1   ),
                        errors(0   )
                {
                        if (nmatch > 0) {
                                match = new (std::nothrow) re2::StringPiece[nmatch + 1];
                                if (match == NULL) {
                                        std::cerr << "Coundn’t allocate memory for lexer." << std::endl;
                                        std::exit(EX_OSERR);
                                }
                        } else match = NULL;
                }

                Scanner::~Scanner() {
                        if (match != NULL) delete [] match;
                }

                int yylex(yy::parser::semantic_type * s, yy::parser::location_type * l, Scanner * scanner) {
                        unsigned int endline, endcol;
                        int bytes;

                        if (scanner->in->length() <= 0 || scanner->in->data()[0] == '\0') {
                                TAJADA_DEBUG_LEXER_PRINT("Done.");
                                return 0;
                        }

                        for (auto it = ts.begin(); it != ts.end(); ++it) {
                                if (
                                        TAJADA_TOKEN_RE2(*it) == NULL ||
                                        !TAJADA_TOKEN_RE2(*it)->Match(
                                                *scanner->in,
                                                0,
                                                scanner->in->length(),
                                                re2::RE2::ANCHOR_START,
                                                scanner->match,
                                                TAJADA_TOKEN_RE2(*it)->NumberOfCapturingGroups() + 1
                                        )
                                ) continue;

                                endline = scanner->line;
                                endcol  = scanner->col;

                                {}{
                                        re2::StringPiece textpiece(scanner->match[1]);
                                        while (re2::RE2::FindAndConsume(&textpiece, *re_line)) {
                                                ++endline;
                                                endcol = 1;
                                        }
                                        for (auto it = textpiece.begin(); it != textpiece.end(); it += bytes) {
                                                for (bytes = 1; bytes < 8; ++bytes) {
                                                        if (!((*it >> (8 - bytes)) & 1)) {
                                                                if (bytes > 1) --bytes;
                                                                break;
                                                        }
                                                }

                                                ++endcol;
                                        }
                                }

                                if (TAJADA_TOKEN_ENUM(*it) != Tajada::lex::Token::IGNORE) {
                                        TAJADA_DEBUG_LEXER_DO(
                                                std::cerr
                                                        << u8"Found token “"
                                                        << TAJADA_TOKEN_TAG(*it)
                                                        << u8"” ";
                                                if (scanner->line == endline && scanner->col == endcol - 1) {
                                                        std::cerr
                                                                << u8"at line "
                                                                << scanner->line
                                                                << u8", column "
                                                                << scanner->col
                                                                << u8" matching character “"
                                                                << scanner->match[1]
                                                                << u8"”";
                                                } else {
                                                        std::cerr
                                                                << u8"spanning range ("
                                                                << scanner->line
                                                                << u8", "
                                                                << scanner->col
                                                                << u8")–("
                                                                << endline
                                                                << u8", "
                                                                << endcol - 1
                                                                << u8") matching text"
                                                                << (scanner->line == endline ? u8": " : u8" on next line:\n")
                                                                << scanner->match[1];
                                                }
                                                std::cerr << std::endl;
                                        );
                                }

                                l->begin.line   = scanner->line;
                                l->begin.column = scanner->col;
                                l->end.line     = endline;
                                l->end.column   = endcol;

                                scanner->line = endline;
                                scanner->col  = endcol;

                                // TODO: set s
                                switch (TAJADA_TOKEN_ENUM(*it)) {
                                        case Tajada::lex::Token::IGNORE:
                                                scanner->in->remove_prefix(scanner->match[1].length());
                                                return yylex(s, l, scanner);

                                        case Tajada::lex::Token::LIT_STR:
                                                // TODO: eliminar delimitadores del string con un método menos caimán, y quitar escapadores
                                                s->LIT_STR = new std::string(scanner->match[1].ToString().substr(3, scanner->match[1].length() - 6));
                                                TAJADA_DEBUG_LEXER_PRINT("Encontré un string y su contenido sin las comillas es:\n" << s->LIT_STR);
                                                break;

                                        case Tajada::lex::Token::LIT_CHR:
                                                s->LIT_CHR = new std::string(scanner->match[1].ToString().substr(1));
                                                break;

#define TAJADA_CASE_STRING(token)                                         \
        case Tajada::lex::Token::token:                                   \
                s->token = new std::string(scanner->match[1].ToString()); \
                break;
                                        TAJADA_CASE_STRING(LIT_INT )
                                        TAJADA_CASE_STRING(OP_MINUS)
                                        TAJADA_CASE_STRING(OP_PLUS )
                                        TAJADA_CASE_STRING(OP_MULT )
                                        TAJADA_CASE_STRING(OP_DIV  )
                                        TAJADA_CASE_STRING(OP_MOD  )
                                        TAJADA_CASE_STRING(OP_EQ   )
                                        TAJADA_CASE_STRING(OP_NEQ  )
                                        TAJADA_CASE_STRING(IDENT   )
#undef TAJADA_CASE_STRING

                                        default:
                                                break;
                                }

                                scanner->in->remove_prefix(scanner->match[1].length());

                                return TAJADA_TOKEN_BISON_ENUM(*it);
                        }

                        for (bytes = 1; bytes < 8; ++bytes) {
                                if (!((scanner->in->data()[0] >> (8 - bytes)) & 1)) {
                                        if (bytes > 1) --bytes;
                                        break;
                                }
                        }
                        std::cerr
                                << u8"Unrecognized "
                                << bytes
                                << u8"‐byte character ‘";
                        for (int i = 0; i < bytes; ++i) std::cerr << scanner->in->data()[i];
                        std::cerr
                                << u8"’ at line "
                                << scanner->line
                                << u8", column "
                                << scanner->col
                                << u8"."
                                << std::endl;
                        // TODO: handle lexical errors

                        scanner->in->remove_prefix(bytes);
                        ++(scanner->errors);
                        ++(scanner->col);

                        return yylex(s, l, scanner);
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

                                        TAJADA_DEBUG_LEXER_PRINT(u8"Parsed regexp for token “" << TAJADA_TOKEN_TAG(*it) << u8"”");
                                }
                                TAJADA_TOKEN_RE2(*it) = r;
                        }

                        TAJADA_SCANNER_INIT_FIXED_REGEX(re_line, u8"([" TAJADA_ENDLINES "])");
                }
        }
}
