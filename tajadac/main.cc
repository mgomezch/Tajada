#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <streambuf>

#include <re2/re2.h>
#include <sysexits.h>

#include "ast.hh"
#include "lex.hh"
#include "parser.tab.hh"
#include "scope.hh"
#include "tokens.hh"
#include "type.hh"

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
                        std::cerr << argv[0] << ": " << argv[1] << ": error abriendo el archivo" << std::endl;
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

#define TAJADA_DEFINE_BINARY_BUILTIN(name, type_l, type_r, type_o, evaluator)                                                               \
{                                                                                                                                           \
        auto base_type_l   = new Tajada::Type::type_l();                                                                                    \
        auto base_type_r   = new Tajada::Type::type_r();                                                                                    \
        auto base_type_o   = new Tajada::Type::type_o();                                                                                    \
        auto ingrediente_l = new std::tuple<Tajada::Type::Type *, std::string *>(std::make_tuple(base_type_l, new std::string("")));        \
        auto ingrediente_r = new std::tuple<Tajada::Type::Type *, std::string *>(std::make_tuple(base_type_r, new std::string("")));        \
        auto ingredientes  = new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> { ingrediente_l, ingrediente_r };           \
        auto domain        = new Tajada::Type::Tuple(ingredientes);                                                                         \
        auto declaration   = new Tajada::AST::FunctionDeclaration(new std::string(u8"" #name), new std::string("$ñ"), domain, base_type_o); \
        auto builtin       = new Tajada::AST::BuiltinFunction(declaration, evaluator);                                                      \
        auto function_ptr  = new Tajada::AST::Function * (builtin);                                                                         \
                                                                                                                                            \
        Tajada::yy::location l;                                                                                                             \
        l.initialize(new std::string(__FILE__));                                                                                            \
        l.begin.line = l.end.line = __LINE__;                                                                                               \
        l.end.column = l.begin.column + 1;                                                                                                  \
        scope.functions.insert(std::make_pair(std::string(u8"" #name), std::make_tuple(domain, base_type_o, function_ptr, l)));             \
}
#define TAJADA_DEFINE_SIMPLE_BINARY_BUILTIN(name, type) TAJADA_DEFINE_BINARY_BUILTIN(name, type, type, type, nullptr)

#define TAJADA_OPS(O) O(+) O(×) O(~) O(=) O(≠)
#define TAJADA_DEFINE_BINARY_FUNCTION_FOR_TYPE(name) TAJADA_DEFINE_SIMPLE_BINARY_BUILTIN(name, Boolean)
TAJADA_OPS(TAJADA_DEFINE_BINARY_FUNCTION_FOR_TYPE)
#undef TAJADA_DEFINE_BINARY_FUNCTION_FOR_TYPE
#undef TAJADA_OPS

#define TAJADA_OPS(O) O(−) O(+) O(×) O(÷) O(~) O(=) O(≠)
#define TAJADA_DEFINE_BINARY_FUNCTION_FOR_TYPE(name) TAJADA_DEFINE_SIMPLE_BINARY_BUILTIN(name, Integer)
TAJADA_OPS(TAJADA_DEFINE_BINARY_FUNCTION_FOR_TYPE)
#undef TAJADA_DEFINE_BINARY_FUNCTION_FOR_TYPE
#undef TAJADA_OPS

#define TAJADA_OPS(O) O(−) O(+) O(×) O(÷)
#define TAJADA_DEFINE_BINARY_FUNCTION_FOR_TYPE(name) TAJADA_DEFINE_SIMPLE_BINARY_BUILTIN(name, Float)
TAJADA_OPS(TAJADA_DEFINE_BINARY_FUNCTION_FOR_TYPE)
#undef TAJADA_DEFINE_BINARY_FUNCTION_FOR_TYPE
#undef TAJADA_OPS

#undef TAJADA_DEFINE_SIMPLE_BINARY_BUILTIN
#undef TAJADA_DEFINE_BINARY_BUILTIN

                Tajada::AST::AST * tree = nullptr;
                if (Tajada::yy::parser(&scanner, &scope, &tree).parse()) {
                        std::cerr << u8"Parse error." << std::endl;
                } else {
                        std::cout
                                << u8"Successful parse:\n"
                                << tree->show()
                                << u8"\n"
                                << u8"Symbol tables:\n"
                                << scope.show()
                                << std::endl;
                }
        }
}
