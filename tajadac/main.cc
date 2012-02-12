#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <streambuf>

#include <sysexits.h>
#include <re2/re2.h>

#include "parser.tab.hh"
#include "tokens.hh"
#include "lex.hh"

// Aquí porque no sé dónde ponerla:
void tajada::yy::parser::error(location_type const & l, std::string const & msg) {
        if (l.begin.line == l.end.line) {
                if (l.begin.column == l.end.column - 1) {
                        std::cerr << u8"At line " << l.begin.line << u8", column " << l.begin.column;
                } else {
                        std::cerr
                                << u8"At line " << l.begin.line
                                << u8", columns " << l.begin.column << u8"–" << l.end.column;
                }
        } else {
                std::cerr
                        << u8"Between line " << l.begin.line << u8", column " << l.begin.column
                        << u8" and line "    << l.end  .line << u8", column " << l.end  .column;
        }

        std::cerr << u8": " << msg << std::endl;
}

int main(int argc, char * argv[]) {
        tajada::lex::init();

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

        // http://stackoverflow.com/a/2602060
        std::string in_s(
                (std::istreambuf_iterator<char>(*in_file)),
                (std::istreambuf_iterator<char>())
        );

        {
                re2::StringPiece in(in_s);
                tajada::lex::scanner s = { &in };
                std::cout << (tajada::yy::parser(&s).parse() ? "Parse error." : "Successfully parsed.") << std::endl;
        }
}
