#include <cstdlib>
#include <iostream>
#include <re2/re2.h>
#include <sysexits.h>
#include <tuple>
#include <vector>

#define TOKEN(name, regex) std::make_tuple<const char *, const char *, re2::RE2 *>(name, regex, NULL)

int main(int argc, char *argv[]) {
        std::vector<std::tuple<const char *, std::string, re2::RE2 *>> ts = {
                TOKEN("FOO"  , u8R"#((foo))#"),
                TOKEN("BAR"  , u8R"#((bar))#"),
                TOKEN("BAZ"  , u8R"#((baz))#"),
                TOKEN("PAREN", u8R"#((\())#" )
        };

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
                        r = new re2::RE2(std::string(std::get<1>(*it)), o);
                        if (!r->ok()) {
                                std::cerr
                                        << u8"Skipping regexp “"
                                        << std::get<1>(*it)
                                        << u8"” for token “"
                                        << std::get<0>(*it)
                                        << u8"” due to parse error: "
                                        << r->error()
                                        << std::endl;
                                delete r;
                                r = NULL;
                        }
                        std::get<2>(*it) = r;
                }
        }

        re2::StringPiece in(argv[1]);
        std::string text;
        bool advanced;
        unsigned int pos = 0;
        while (true) {
                if (in.length() <= 0 || in[0] == '\0') break;
                advanced = false;
                for (auto it = ts.begin(); it != ts.end(); ++it) {
                        if (std::get<2>(*it) == NULL || !re2::RE2::Consume(&in, *std::get<2>(*it), &text)) continue;
                        advanced = true;
                        std::cout
                                << u8"Found token “"
                                << std::get<0>(*it)
                                << u8"” matching text “"
                                << text
                                << u8"” against regex “"
                                << std::get<1>(*it)
                                << "”"
                                << std::endl;
                        break;
                }
                if (!advanced) {
                        // FIXME: this fails with multibyte encodings!
                        // It actualy skips bytes, not characters.
                        // Solution: skip N bytes if next UTF-8 character has N bytes; deduce N from bit pattern.
                        std::cerr
                                << u8"Skipping unrecognized character ‘"
                                << in[0]
                                << u8"’ at position "
                                << pos
                                << u8"; remaining input is “"
                                << in
                                << u8"”"
                                << std::endl;
                        in.remove_prefix(1);
                        ++pos;
                }
        }
}
