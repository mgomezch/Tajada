#ifndef TAJADA_AST_ASSOCIATIVITY_HH
#define TAJADA_AST_ASSOCIATIVITY_HH

namespace Tajada {
        namespace AST {
                enum class Associativity : unsigned int {
                        none ,
                        left ,
                        right
                };
        }
}

#endif
