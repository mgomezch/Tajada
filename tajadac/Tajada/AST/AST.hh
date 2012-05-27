#ifndef TAJADA_AST_AST_HH
#define TAJADA_AST_AST_HH

#include <string>

#include "Tajada/Code/Block.hh"

namespace Tajada {
        namespace AST {
                class AST {
                        public:
                                virtual std::string show(unsigned int depth = 0) = 0;

                                virtual Tajada::Code::Block * gen(
                                        Tajada::Code::Block * b
                                );

                                virtual ~AST() = 0;
                };
        }
}

#endif
