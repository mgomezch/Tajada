#ifndef TAJADA_AST_STATEMENT_HH
#define TAJADA_AST_STATEMENT_HH

// Superclasses:
#include "Tajada/AST/AST.hh"

#include "Tajada/Code/Block.hh"

namespace Tajada {
        namespace AST {
                class Statement : public virtual Tajada::AST::AST {
                        public:
                                // TODO: make this pure virtual once all subclasses have their implementation
                                virtual Tajada::Code::Block * gen(
                                        Tajada::Code::Block * b
                                );
                };
        }
}

#endif
