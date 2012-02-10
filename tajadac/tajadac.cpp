#include <cstdlib>
#include <iostream>
#include <re2/re2.h>
#include <sysexits.h>
#include <tuple>
#include <vector>

#include "macros.hpp"
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

int main(int argc, char * argv[]) {
        re2::RE2 * re_line;

        if (argc < 2) exit(EX_USAGE);

        {
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

                re_line = new re2::RE2(std::string(u8"[" STRINGIFY(ENDLINES) "]"), o);
        }

        re2::StringPiece in(argv[1]);
        std::string text;
        std::string text_line;
        bool advanced;
        unsigned int line = 1, col = 1;
        unsigned int endline, endcol;
        int bytes;
        while (true) {
                if (in.length() <= 0 || in[0] == '\0') break;
                advanced = false;
                for (auto it = ts.begin(); it != ts.end(); ++it) {
                        if (TOKEN_RE2(*it) == NULL || !re2::RE2::Consume(&in, *TOKEN_RE2(*it), &text)) continue;
                        advanced = true;

                        endline = line;
                        endcol = col;

                        {
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

                        std::cout
                                << u8"Found token “"
                                << TOKEN_TAG(*it)
                                << u8"” matching text “"
                                << text
                                << u8"” ";
                        if (line == endline && col == endcol - 1) {
                                std::cout
                                        << u8"at line "
                                        << line
                                        << u8", column "
                                        << col
                                        << std::endl;
                        } else {
                                std::cout
                                        << u8"spanning range ("
                                        << line
                                        << u8", "
                                        << col
                                        << u8")–("
                                        << endline
                                        << u8", "
                                        << endcol - 1
                                        << u8")"
                                        << std::endl;
                        }

                        line = endline;
                        col = endcol;
                        break;
                }
                if (!advanced) {
                        for (bytes = 1; bytes < 8; ++bytes) {
                                if (!((in[0] >> (8 - bytes)) & 1)) {
                                        if (bytes > 1) --bytes;
                                        break;
                                }
                        }
                        std::cerr
                                << u8"Skipping unrecognized "
                                << bytes
                                << u8"‐byte character ‘";
                        for (int i = 0; i < bytes; ++i) std::cerr << in.data()[i];
                        in.remove_prefix(bytes);
                        std::cerr
                                << u8"’ at line "
                                << line
                                << u8", column "
                                << col
                                << u8"; remaining input is “"
                                << in
                                << u8"”"
                                << std::endl;
                        ++col;
                }
        }
}
