#include <cstdlib>
#include <iostream>
#include <re2/re2.h>
#include <sysexits.h>
#include <tuple>
#include <vector>

#define TOKEN_TUPLE_TYPES Token, char const *, char const *, char const *, re2::RE2 *

#define   TOKEN_TAGS(tag, description, regex) tag,
#define TOKEN_TUPLES(tag, description, regex) std::make_tuple<TOKEN_TUPLE_TYPES>(Token :: tag, #tag, description, regex, NULL),

#define        TOKEN_ENUM(t) std::get<0>(t)
#define         TOKEN_TAG(t) std::get<1>(t)
#define TOKEN_DESCRIPTION(t) std::get<2>(t)
#define       TOKEN_REGEX(t) std::get<3>(t)
#define         TOKEN_RE2(t) std::get<4>(t)

#define RESERVED_WORD(TOKEN, tag, word)                                                                                         \
        TOKEN(                                                                                                                  \
                tag,                                                                                                            \
                u8"palabra reservada “" word u8"”",                                                                             \
                u8"(" word u8")"                                                                                                \
        )

#define TOKEN_DATA(TOKEN)                                                                                                       \
        /* §1.1 */                                                                                                              \
        TOKEN(                                                                                                                  \
                LIT_STR,                                                                                                        \
                u8"literal de cadena de caracteres",                                                                            \
                u8R"#((“([^”\\]|\\.)*”))#"                                                                                      \
        )                                                                                                                       \
                                                                                                                                \
        /* §1.2 */                                                                                                              \
        TOKEN(                                                                                                                  \
                IGNORE,                                                                                                         \
                u8"espacio en blanco",                                                                                          \
                u8"("                                                                                                           \
                        /* §1.2.1p4 */                                                                                          \
                        u8"‹[^›]*›|"                                                                                            \
                                                                                                                                \
                        /* §1.2.2p4 */                                                                                          \
                        u8"⫽[^\u000A\u000B\u000C\u000D\u0085\u2028\u2029]*[\u000A\u000B\u000C\u000D\u0085\u2028\u2029]|"        \
                                                                                                                                \
                        /* §1.2.2p5 */                                                                                          \
                        u8"\u000A|"                                                                                             \
                        u8"\u000B|"                                                                                             \
                        u8"\u000C|"                                                                                             \
                        u8"\u000D|"                                                                                             \
                        u8"\u0085|"                                                                                             \
                        u8"\u2028|"                                                                                             \
                        u8"\u2029|"                                                                                             \
                                                                                                                                \
                        /* §1.2.3p1 */                                                                                          \
                        /* re2 does not currently support the White_Space property, so "\\p{WS}" won’t work. :( */              \
                        u8"[\u0009-\u000D\u0020\u0085\u00A0\u1680\u180E\u2000-\u200A\u2028\u2029\u202F\u205F\u3000]"            \
                u8")"                                                                                                           \
        )                                                                                                                       \
                                                                                                                                \
        /* §1.3.1p2 */                                                                                                          \
        TOKEN(                                                                                                                  \
                LIT_INT,                                                                                                        \
                u8"literal entero",                                                                                             \
                u8R"#(([0-9]+))#"                                                                                               \
        )                                                                                                                       \
                                                                                                                                \
        /* §1.3.2p1 */                                                                                                          \
        TOKEN(                                                                                                                  \
                LIT_FLOAT,                                                                                                      \
                u8"literal de punto flotante",                                                                                  \
                u8R"#(([0-9]+·[0-9]+))#"                                                                                        \
        )                                                                                                                       \
                                                                                                                                \
        /* §2.1.1p1 */                                                                                                          \
        RESERVED_WORD(TOKEN, BOOL , u8"café"   )                                                                                \
        RESERVED_WORD(TOKEN, TRUE , u8"tetero" )                                                                                \
        RESERVED_WORD(TOKEN, FALSE, u8"negrito")                                                                                \
                                                                                                                                \
        /* §2.1.2p1 */                                                                                                          \
        RESERVED_WORD(TOKEN, CHAR , u8"caraota")                                                                                \
                                                                                                                                \
        /* TODO: sección */                                                                                                     \
        TOKEN(                                                                                                                  \
                PAREN_OP,                                                                                                       \
                u8"inicio de paréntesis",                                                                                       \
                u8R"#((\())#"                                                                                                   \
        )                                                                                                                       \
                                                                                                                                \
        /* TODO: sección */                                                                                                     \
        TOKEN(                                                                                                                  \
                PAREN_CL,                                                                                                       \
                u8"fin de paréntesis",                                                                                          \
                u8R"#((\)))#"                                                                                                   \
        )                                                                                                                       \

enum class Token : unsigned int { TOKEN_DATA(TOKEN_TAGS) };

int main(int argc, char * argv[]) {
        std::vector<std::tuple<TOKEN_TUPLE_TYPES>> ts = { TOKEN_DATA(TOKEN_TUPLES) };

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
                                std::cerr
                                        << u8"Parsed regexp for token “"
                                        << TOKEN_TAG(*it)
                                        << u8"”"
                                        << std::endl;
                        }
                        TOKEN_RE2(*it) = r;
                }
        }

        re2::StringPiece in(argv[1]);
        std::string text;
        bool advanced;
        unsigned int pos = 0, line = 1, col = 1;
        int bytes;
        while (true) {
                if (in.length() <= 0 || in[0] == '\0') break;
                advanced = false;
                for (auto it = ts.begin(); it != ts.end(); ++it) {
                        if (TOKEN_RE2(*it) == NULL || !re2::RE2::Consume(&in, *TOKEN_RE2(*it), &text)) continue;
                        advanced = true;
                        std::cout
                                << u8"Found token “"
                                << TOKEN_TAG(*it)
                                << u8"” matching text “"
                                << text
                                << "”"
                                << std::endl;
                        // TODO: increment line/col!
                        break;
                }
                if (!advanced) {
                        for (bytes = 1; bytes < 8; ++bytes) {
                                std::cout << u8"El bit " << bytes << " es " << ((in[0] >> (8 - bytes)) & 1) << std::endl;
                                if (!((in[0] >> (8 - bytes)) & 1)) {
                                        if (bytes > 1) --bytes;
                                        break;
                                }
                        }
                        std::cerr
                                << u8"Skipping unrecognized "
                                << bytes
                                << "‐byte character ‘";
                        for (int i = 0; i < bytes; ++i) std::cerr << in.data()[i];
                        std::cerr
                                << u8"’ at position "
                                << pos
                                << u8"; remaining input is “"
                                << ((char const *)in.data() + bytes)
                                << u8"”"
                                << std::endl;
                        in.remove_prefix(bytes);
                        ++pos;
                }
        }
}
