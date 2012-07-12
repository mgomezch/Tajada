#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <streambuf>

#include <re2/re2.h>
#include <sysexits.h>

#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Program.hh"

//#include "Tajada/Type.hh"

#include "lex.hh"
#include "parser.tab.hh"
#include "scope.hh"
#include "tokens.hh"

int main(int argc, char * argv[]) {
        if (argc != 1 && argc != 2) {
                std::cerr
                        << u8"Uso: " << (argc > 0 ? argv[0] : u8"tajadac") << u8" [entrada]\n"
                        << u8"• entrada: el nombre del archivo a compilar.  Si no se especifica, se leerá de la entrada estándar."
                        << std::endl
                ;
                std::exit(EX_USAGE);
        }

        std::istream * in_file;
        std::string filename {""};
        if (argc == 1) {
                in_file = &std::cin;
        } else {
                filename = argv[1];
                in_file = new std::ifstream(argv[1], std::ifstream::in);
                if (in_file->fail()) {
                        std::cerr
                                << argv[0]
                                << ": "
                                << filename
                                << ": error abriendo el archivo"
                                << std::endl
                        ;
                        std::exit(EX_NOINPUT);
                }
        }

        // http://stackoverflow.com/a/2602060
        std::string in_s(
                (std::istreambuf_iterator<char>(*in_file)),
                (std::istreambuf_iterator<char>())
        );

        {}{
                re2::StringPiece in(in_s);

                Tajada::lex::init();
                Tajada::lex::Scanner scanner { &in };
                scanner.build();

                Tajada::Scope scope(
                        nullptr,
                        Tajada::Scope::Type::global
                );

                Tajada::AST::AST * tree = nullptr;
                if (Tajada::yy::parser(&scanner, &scope, &tree, &filename).parse()) {
                        std::cerr << u8"Parse error." << std::endl;
                        std::exit(EX_DATAERR);
                } else {
                        std::cout
                                << u8"Successful parse:\n"
                                << tree->show()
                                << u8"\n\n"
                                << u8"Symbol tables:\n"
                                << scope.show()
                                << std::endl
                        ;

                        if (auto p = dynamic_cast<Tajada::AST::Program *>(tree)) {
                                auto code = p->gen();

                                std::cout
                                        << u8"Code:\n"
                                        << code->show_all()
                                ;

                                auto mips = code->to_mips_all();

                                std::cout
                                        << u8"\n\n\nMIPS:\n"
                                        << mips
                                ;

                                if (filename != "") std::ofstream(filename + u8".s") << mips;
                        }

                        std::exit(EX_OK);
                }
        }
}
