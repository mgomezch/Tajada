#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <new>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <boost/algorithm/string/join.hpp>
#include <re2/re2.h>
#include <sysexits.h>

#include "Tajada/AST/Associativity.hh"

#include "debug.hh"
#include "lex.hh"
#include "parser.tab.hh"
#include "tokens.hh"



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
                                << var->error()                                           \
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

                re2::RE2::Options o;

                re2::RE2 * re_line;



                Scanner::Scanner(
                        re2::StringPiece * p_in
                ):
                        ts {
#define TAJADA_TOKEN_TUPLES(tag, description, regex, type) \
        std::make_tuple<TAJADA_TOKEN_TUPLE_TYPES>(         \
                Tajada::lex::Token::tag,                   \
                yy::parser::token::tag,                    \
                #tag,                                      \
                description,                               \
                regex,                                     \
                nullptr                                    \
        ),
                                TAJADA_TOKEN_DATA(TAJADA_TOKEN_TUPLES)
#undef TAJADA_TOKEN_TUPLES
                        },
                        reserved_symbols{    },
                        in              {p_in},
                        line            {1   },
                        col             {1   },
                        errors          {0   },
                        ident_piece     {    }
                {
                        match =
                                (nmatch > 0)
                                ? new re2::StringPiece[nmatch + 1]
                                : nullptr
                        ;

#define TAJADA_INFIX_INITIALIZER(tag, description, regex, type)             \
        infix_ops[static_cast<unsigned int>(Tajada::lex::Token::tag)] = {};
                        TAJADA_INFIX_DATA(TAJADA_INFIX_INITIALIZER)
#undef TAJADA_INFIX_INITIALIZER
                }


                Scanner::~Scanner() {
                        if (match != nullptr) delete [] match;
                }



                int yylex(yy::parser::semantic_type * s, yy::parser::location_type * l, Scanner * scanner) {
                        unsigned int endline, endcol;
                        int bytes;

                        if (scanner->in->length() <= 0 || scanner->in->data()[0] == '\0') {
                                TAJADA_DEBUG_LEXER_PRINT("Done.");
                                return 0;
                        }

                        for (
                                auto it = scanner->ts.begin();
                                it != scanner->ts.end();
                                ++it
                        ) {
                                if (
                                        // Ignore that silly token for identifiers; we don’t actually need to check its regular expression as identifiers are constructed one character at a time, and it’s only in the token list because we want its enum to exist and such.  This could also be achieved by stopping at `--ts.end()`, but maybe I’ll just arrange for it to be excluded from `ts` in the first place.
                                        TAJADA_TOKEN_ENUM(*it) == Tajada::lex::Token::IDENT


                                        // If we’re in the process of reading an identifier, any symbols recognized should be considered part of the identifier, not as separate tokens; this applies for numbers, so we can have identifiers with numbers in them (which is very nice) and for reserved words (so we can have identifiers that include reserved words in them).
                                        || (
                                                scanner->ident_piece != ""
                                                && (
                                                        TAJADA_TOKEN_ENUM(*it) == Tajada::lex::Token::LIT_INT
                                                        || (
                                                                *TAJADA_TOKEN_REGEX(*it) != '\0'
                                                                && TAJADA_TOKEN_REGEX(*it)[0] != '('
                                                        )
                                                )
                                        )


                                        // If we failed compiling the regular expression, ignore it.  This is probably no longer necessary and those failures should become fatal errors.
                                        || TAJADA_TOKEN_RE2(*it) == nullptr


                                        // If the token we’re going to check for is some class of infix operator and none has been defined with its precedence and associativity, skip it; we don’t want to try matching an empty regular expression.
                                        || (
                                                *TAJADA_TOKEN_REGEX(*it) == '\0'
                                                && scanner->infix_ops[static_cast<unsigned int>(TAJADA_TOKEN_ENUM(*it))].empty()
                                        )


                                        // Finally, skip this token if the input doesn’t match its compiled regular expression.
                                        || !TAJADA_TOKEN_RE2(*it)->Match(
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
                                        re2::StringPiece textpiece(
                                                scanner->ident_piece != ""
                                                ? scanner->ident_piece
                                                : scanner->match[1]
                                        );
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

                                if (
                                        scanner->ident_piece == ""
                                        && TAJADA_TOKEN_ENUM(*it) != Tajada::lex::Token::IGNORE
                                ) {
                                        TAJADA_DEBUG_LEXER_DO(
                                                std::cerr
                                                        << u8"Found token “"
                                                        << TAJADA_TOKEN_TAG(*it)
                                                        << u8"” "
                                                ;
                                                if (
                                                        scanner->line == endline
                                                        && scanner->col == endcol - 1
                                                ) {
                                                        std::cerr
                                                                << u8"at line "
                                                                << scanner->line
                                                                << u8", column "
                                                                << scanner->col
                                                                << u8" matching character “"
                                                                << scanner->match[1]
                                                                << u8"”"
                                                        ;
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
                                                                << scanner->match[1]
                                                        ;
                                                }
                                                std::cerr << std::endl;
                                        );
                                }

                                l->begin.line   = scanner->line;
                                l->begin.column = scanner->col ;
                                l->end  .line   = endline      ;
                                l->end  .column = endcol       ;

                                scanner->line = endline;
                                scanner->col  = endcol ;

                                if (scanner->ident_piece != "") {
                                        // TODO: make this token print debug info too
                                        s->IDENT = new std::string(scanner->ident_piece);
                                        scanner->ident_piece = "";
                                        return yy::parser::token::IDENT;
                                }

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

                                        case Tajada::lex::Token::LIT_INT:
                                                s->LIT_INT = new std::string(scanner->match[1].ToString());
                                                break;

#if 0
                                        // TODO: comment out the old identifier code
                                        case Tajada::lex::Token::IDENT:
                                                s->IDENT = new std::string(scanner->match[1].ToString());
                                                break;
#endif

#define TAJADA_INFIX_CASE(tag, description, regex, type) case Tajada::lex::Token::tag:
                                        TAJADA_INFIX_DATA(TAJADA_INFIX_CASE)
#undef TAJADA_INFIX_CASE
                                                s->infix_op = new std::string(scanner->match[1].ToString());
                                                break;

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

#if 0
                        std::cerr
                                << u8"Unrecognized "
                                << bytes
                                << u8"‐byte character ‘"
                        ;
                        for (int i = 0; i < bytes; ++i) std::cerr << scanner->in->data()[i];
                        std::cerr
                                << u8"’ at line "
                                << scanner->line
                                << u8", column "
                                << scanner->col
                                << u8"."
                                << std::endl
                        ;

                        // TODO: handle lexical errors (at least check the error count in scanner at the end)
                        // TODO: log errors in scanner

                        scanner->in->remove_prefix(bytes);
                        ++(scanner->errors);
                        ++(scanner->col);
#endif

                        for (int i = 0; i < bytes; ++i) scanner->ident_piece += scanner->in->data()[i];
                        scanner->in->remove_prefix(bytes);

                        TAJADA_DEBUG_LEXER_PRINT(
                                "Encontré un pedazo de identificador; mide "
                                << bytes
                                << " byte"
                                << (bytes == 1 ? "" : "s")
                                << " y ahora el acumulado dice "
                                << scanner->ident_piece
                        );

                        return yylex(s, l, scanner);
                }



                void Scanner::build() {
                        int n;
                        re2::RE2 * r;

                        reserved_symbols.clear();

                        for (auto it = ts.begin(); it != ts.end(); ++it) {
                                assert(TAJADA_TOKEN_REGEX(*it) != nullptr);

                                if (*TAJADA_TOKEN_REGEX(*it) == '\0') {
                                        // Infix operator
                                        if (TAJADA_TOKEN_RE2(*it)) delete TAJADA_TOKEN_RE2(*it);

                                        assert(infix_ops.find(static_cast<unsigned int>(TAJADA_TOKEN_ENUM(*it))) != infix_ops.end());

                                        r = new re2::RE2(
                                                u8"("
                                                + boost::algorithm::join(
                                                        infix_ops[static_cast<unsigned int>(TAJADA_TOKEN_ENUM(*it))],
                                                        "|"
                                                )
                                                + u8")",
                                                o
                                        );
                                } else if (TAJADA_TOKEN_REGEX(*it)[0] != '(') {
                                        // Reserved word
                                        if (TAJADA_TOKEN_RE2(*it)) delete TAJADA_TOKEN_RE2(*it);

                                        r = new re2::RE2(
                                                u8"("
                                                + std::string(TAJADA_TOKEN_REGEX(*it))
                                                + u8")(?:"
                                                + boost::algorithm::join(reserved_symbols, "|")
                                                + u8"|$)",
                                                o
                                        );
                                } else {
                                        // Reserved symbol
                                        reserved_symbols.insert(TAJADA_TOKEN_REGEX(*it));

                                        if (TAJADA_TOKEN_RE2(*it)) continue;

                                        r = new re2::RE2(
                                                "("
                                                + std::string(TAJADA_TOKEN_REGEX(*it))
                                                + ")",
                                                o
                                        );
                                }

                                if (!r->ok()) {
                                        std::cerr
                                                << u8"Skipping regexp for token “"
                                                << TAJADA_TOKEN_TAG(*it)
                                                << u8"” due to parse error: "
                                                << r->error()
                                                << std::endl
                                        ;
                                        delete r;
                                        r = nullptr;
                                } else {
                                        n = r->NumberOfCapturingGroups();

                                        if (n < 1) {
                                                std::cerr
                                                        << u8"Error in regex for token “"
                                                        << TAJADA_TOKEN_TAG(*it)
                                                        << u8"”: at least one capture group is required."
                                                        << std::endl
                                                ;
                                                std::exit(EX_SOFTWARE);
                                        }
                                        nmatch = std::max(nmatch, n);

                                        TAJADA_DEBUG_LEXER_PRINT(u8"Parsed regexp for token “" << TAJADA_TOKEN_TAG(*it) << u8"”");
                                }
                                TAJADA_TOKEN_RE2(*it) = r;
                        }
                }



                void init() {
                        o.set_encoding      (re2::RE2::Options::Encoding::EncodingUTF8);
                        o.set_posix_syntax  (false);
                        o.set_longest_match (false);
                        o.set_log_errors    (true );
                        o.set_literal       (false);
                        o.set_never_nl      (false);
                        o.set_case_sensitive(true );

                        TAJADA_SCANNER_INIT_FIXED_REGEX(re_line, u8"([" TAJADA_ENDLINES "])");
                }



                // add the identifier to the appropriate member of scanner->infix_ops and scanner->reserved_start, and then call Tajada::lex::init()
                void add_infix(
                        Tajada::lex::Scanner       * scanner      ,
                        std::string                  identifier   ,
                        Tajada::AST::Associativity   associativity,
                        unsigned int                 precedence
                ) {
                        Tajada::lex::Token token;

#define TAJADA_INFIX_LEVELS(F, T) F(T, 0) F(T, 1) F(T, 2) F(T, 3) F(T, 4) F(T, 5) F(T, 6) F(T, 7) F(T, 8) F(T, 9)

#define TAJADA_INFIX_CASE(t, n)                   \
        case n:                                   \
                token = Tajada::lex::Token::t##n; \
                break;

#define TAJADA_INFIX_ASSOC_CASE(a, e)              \
        case Tajada::AST::Associativity::a:        \
                switch (precedence) {              \
                        default:                   \
                                assert(false);     \
                                break;             \
                                                   \
                        TAJADA_INFIX_LEVELS(       \
                                TAJADA_INFIX_CASE, \
                                e                  \
                        )                          \
                }                                  \
                break;

                        switch (associativity) {
                                default:
                                        assert(false);
                                        break;

                                TAJADA_INFIX_ASSOC_CASE(left , INFIXL);
                                TAJADA_INFIX_ASSOC_CASE(none , INFIX );
                                TAJADA_INFIX_ASSOC_CASE(right, INFIXR);
                        }

                        scanner->infix_ops[static_cast<unsigned int>(token)].insert(re2::RE2::QuoteMeta(identifier));

                        scanner->build();
                }
        }
}
