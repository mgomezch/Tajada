#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <tuple>
#include <vector>

#include <sysexits.h>
#include <re2/re2.h>

#include "tokens.hpp"

#define TOKEN_TAGS(tag, description, regex) tag,
enum class Token : unsigned int { TOKEN_DATA(TOKEN_TAGS) };
#undef TOKEN_TAGS

#define TOKEN_TUPLE_TYPES Token, char const *, char const *, char const *, re2::RE2 *
#define        TOKEN_ENUM(t) std::get<0>(t)
#define         TOKEN_TAG(t) std::get<1>(t)
#define TOKEN_DESCRIPTION(t) std::get<2>(t)
#define       TOKEN_REGEX(t) std::get<3>(t)
#define         TOKEN_RE2(t) std::get<4>(t)

#define TOKEN_TUPLES(tag, description, regex) std::make_tuple<TOKEN_TUPLE_TYPES>(Token :: tag, #tag, description, regex, NULL),
std::vector<std::tuple<TOKEN_TUPLE_TYPES>> ts = { TOKEN_DATA(TOKEN_TUPLES) };
#undef TOKEN_TUPLES

re2::RE2 * re_line;

struct scan_state {
        re2::StringPiece * in;
        int line;
        int col;
};

int yylex(YYSTYPE * s, YYLTYPE * l, struct scan_state * state) {
        unsigned int endline, endcol;
        std::string text_line;
        std::string text;
        int bytes;
        bool advanced = false;

        if (state->in->length() <= 0 || state->in->data()[0] == '\0') {
                std::cerr << "Done." << std::endl;
                return 0;
        }
        for (auto it = ts.begin(); it != ts.end(); ++it) {
                if (TOKEN_RE2(*it) == NULL || !re2::RE2::Consume(state->in, *TOKEN_RE2(*it), &text)) continue;
                advanced = true;

                endline = state->line;
                endcol  = state->col;

                {}{
                        re2::StringPiece textpiece(text);
                        while (re2::RE2::FindAndConsume(&textpiece, *re_line)) {
                                ++endline;
                                endcol = 0;
                        }
                        for (auto it = textpiece.begin(); it != textpiece.end(); ++it) {
                                if ((1 << 7) & *it) continue;
                                ++endcol;
                        }
                }

                std::cerr
                        << u8"Found token “"
                        << TOKEN_TAG(*it)
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

                state->line = endline;
                state->col  = endcol;
                break;
        }
        if (!advanced) {
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
                in.remove_prefix(bytes);
                std::cerr
                        << u8"’ at line "
                        << state->line
                        << u8", column "
                        << state->col
                        << u8"."
                        << std::endl;
                ++(state->col);
        }
}

int main(int argc, char * argv[]) {
        if (argc != 2) {
                std::cerr
                        << u8"Uso: " << (argc > 0 ? argv[0] : u8"tajadac") << u8" entrada\n"
                        << u8"• entrada: el nombre del programa a analizar.  Si es “-”, se leerá de la entrada estándar."
                        << std::endl;
                std::exit(EX_USAGE);
        }

        std::istream * in_file;
        if (std::string("-") == argv[1]) in_file = &std::cin;
        else {
                in_file = new std::ifstream(argv[1], std::ifstream::in);
                if (in_file->fail()) {
                        std::cerr << "No se pudo abrir el archivo a analizar." << std::endl;
                        std::exit(EX_NOINPUT);
                }
        }

        {}{
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
                        r = new re2::RE2(std::string(TOKEN_REGEX(*it)), o);
                        if (!r->ok()) {
                                std::cerr
                                        << u8"Skipping regexp for token “"
                                        << TOKEN_TAG(*it)
                                        << u8"” due to parse error: "
                                        << r->error()
                                        << std::endl;
                                delete r;
                                r = NULL;
                        } else {
#ifdef DEBUG_LEXER
                                std::cerr
                                        << u8"Parsed regexp for token “"
                                        << TOKEN_TAG(*it)
                                        << u8"”"
                                        << std::endl;
#endif
                        }
                        TOKEN_RE2(*it) = r;
                }

                re_line = new re2::RE2(std::string(u8"[" ENDLINES "]"), o);
        }

        // http://stackoverflow.com/a/2602060
        std::string in_s(
                (std::istreambuf_iterator<char>(*in_file)),
                (std::istreambuf_iterator<char>())
        );

        re2::StringPiece in(in_s);
        struct scan_state state = { &in, 1, 1 };
}
