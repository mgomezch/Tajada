#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <streambuf>

#include <re2/re2.h>
#include <sysexits.h>

#include "lex.hh"
#include "parser.tab.hh"
#include "scope.hh"
#include "tokens.hh"

int main(int argc, char * argv[]) {
        Tajada::lex::init();

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
                Tajada::lex::Scanner scanner = { &in };
                Tajada::Scope scope;
                // TODO: insert builtin symbols into scope function table
                Tajada::AST::AST * tree = NULL;
                if (Tajada::yy::parser(&scanner, &scope, &tree).parse()) {
                        std::cout << u8"Parse error." << std::endl;
                } else {
                        std::cout
                                << u8"Successfully parsed:\n"
                                << tree->show()
                                << u8"\n"
                                << u8"Symbol tables:\n"
                                << scope.show()
                                << std::endl;
                }
        }
}
