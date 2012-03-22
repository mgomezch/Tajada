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

        if (argc != 1 && argc != 2) {
                std::cerr
                        << u8"Uso: " << (argc > 0 ? argv[0] : u8"tajadac") << u8" [entrada]\n"
                        << u8"• entrada: el nombre del archivo a compilar.  Si no se especifica, se leerá de la entrada estándar."
                        << std::endl;
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
                        std::cerr << argv[0] << ": " << filename << ": error abriendo el archivo" << std::endl;
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
                Tajada::Scope scope(
                        nullptr,
                        Tajada::Scope::Type::global
                );

#define TAJADA_DEFINE_BUILTIN(name, type_i, type_o, evaluator) do {                                                                    \
        auto declaration   = new Tajada::AST::FunctionDeclaration(new std::string(u8"" #name), new std::string("$ñ"), type_i, type_o); \
        auto builtin       = new Tajada::AST::BuiltinFunction(declaration, evaluator);                                                 \
        auto function_ptr  = new Tajada::AST::Function * (builtin);                                                                    \
        Tajada::yy::location l;                                                                                                        \
        l.initialize(new std::string(__FILE__));                                                                                       \
        l.begin.line = l.end.line = __LINE__;                                                                                          \
        l.end.column = l.begin.column + 1;                                                                                             \
        scope.functions.insert(std::make_pair(std::string(u8"" #name), std::make_tuple(type_i, type_o, function_ptr, l)));             \
} while (0)

#define TAJADA_DEFINE_UNARY_BUILTIN(name, type_i, type_o, evaluator) do { \
        auto base_type_i   = new Tajada::Type::type_i();                  \
        auto base_type_o   = new Tajada::Type::type_o();                  \
        TAJADA_DEFINE_BUILTIN(name, base_type_i, base_type_o, evaluator); \
} while (0)

#define TAJADA_DEFINE_BINARY_BUILTIN(name, type_l, type_r, type_o, evaluator) do {                                                   \
        auto base_type_o   = new Tajada::Type::type_o();                                                                             \
        auto base_type_l   = new Tajada::Type::type_l();                                                                             \
        auto base_type_r   = new Tajada::Type::type_r();                                                                             \
        auto ingrediente_l = new std::tuple<Tajada::Type::Type *, std::string *>(std::make_tuple(base_type_l, new std::string(""))); \
        auto ingrediente_r = new std::tuple<Tajada::Type::Type *, std::string *>(std::make_tuple(base_type_r, new std::string(""))); \
        auto ingredientes  = new std::vector<std::tuple<Tajada::Type::Type *, std::string *> *> { ingrediente_l, ingrediente_r };    \
        auto domain        = new Tajada::Type::Tuple(ingredientes);                                                                  \
        TAJADA_DEFINE_BUILTIN(name, domain, base_type_o, evaluator);                                                                 \
} while (0)

#define  TAJADA_DEFINE_SIMPLE_UNARY_BUILTIN(name, type)  TAJADA_DEFINE_UNARY_BUILTIN(name, type, type,       nullptr);
#define TAJADA_DEFINE_SIMPLE_BINARY_BUILTIN(name, type) TAJADA_DEFINE_BINARY_BUILTIN(name, type, type, type, nullptr);

#define TAJADA_OPS(O) O(−)
#define TAJADA_DEFINE_FUNCTION_FOR_TYPE(name) TAJADA_DEFINE_SIMPLE_UNARY_BUILTIN(name, Boolean)
TAJADA_OPS(TAJADA_DEFINE_FUNCTION_FOR_TYPE)
#undef TAJADA_DEFINE_FUNCTION_FOR_TYPE
#undef TAJADA_OPS

#define TAJADA_OPS(O) O(+) O(×) O(~) O(=) O(≠)
#define TAJADA_DEFINE_FUNCTION_FOR_TYPE(name) TAJADA_DEFINE_SIMPLE_BINARY_BUILTIN(name, Boolean)
TAJADA_OPS(TAJADA_DEFINE_FUNCTION_FOR_TYPE)
#undef TAJADA_DEFINE_FUNCTION_FOR_TYPE
#undef TAJADA_OPS

#define TAJADA_OPS(O) O(−)
#define TAJADA_DEFINE_FUNCTION_FOR_TYPE(name) TAJADA_DEFINE_SIMPLE_UNARY_BUILTIN(name, Integer)
TAJADA_OPS(TAJADA_DEFINE_FUNCTION_FOR_TYPE)
#undef TAJADA_DEFINE_FUNCTION_FOR_TYPE
#undef TAJADA_OPS

#define TAJADA_OPS(O) O(−) O(+) O(×) O(÷) O(~) O(=) O(≠)
#define TAJADA_DEFINE_FUNCTION_FOR_TYPE(name) TAJADA_DEFINE_SIMPLE_BINARY_BUILTIN(name, Integer)
TAJADA_OPS(TAJADA_DEFINE_FUNCTION_FOR_TYPE)
#undef TAJADA_DEFINE_FUNCTION_FOR_TYPE
#undef TAJADA_OPS

#define TAJADA_OPS(O) O(−)
#define TAJADA_DEFINE_FUNCTION_FOR_TYPE(name) TAJADA_DEFINE_SIMPLE_UNARY_BUILTIN(name, Float)
TAJADA_OPS(TAJADA_DEFINE_FUNCTION_FOR_TYPE)
#undef TAJADA_DEFINE_FUNCTION_FOR_TYPE
#undef TAJADA_OPS

#define TAJADA_OPS(O) O(−) O(+) O(×) O(÷)
#define TAJADA_DEFINE_FUNCTION_FOR_TYPE(name) TAJADA_DEFINE_SIMPLE_BINARY_BUILTIN(name, Float)
TAJADA_OPS(TAJADA_DEFINE_FUNCTION_FOR_TYPE)
#undef TAJADA_DEFINE_FUNCTION_FOR_TYPE
#undef TAJADA_OPS

#undef TAJADA_DEFINE_SIMPLE_BINARY_BUILTIN
#undef TAJADA_DEFINE_BINARY_BUILTIN
#undef TAJADA_DEFINE_UNARY_BUILTIN
#undef TAJADA_DEFINE_BUILTIN

                Tajada::AST::AST * tree = nullptr;
                if (Tajada::yy::parser(&scanner, &scope, &tree, &filename).parse()) {
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
