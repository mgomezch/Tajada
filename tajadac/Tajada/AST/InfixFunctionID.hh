#ifndef TAJADA_AST_INFIXFUNCTIONID_HH
#define TAJADA_AST_INFIXFUNCTIONID_HH

#include <string>

// Superclasses:
#include "Tajada/AST/FunctionID.hh"

#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Associativity.hh"

namespace Tajada {
        namespace AST {
                class InfixFunctionID:
                        public virtual Tajada::AST::FunctionID
                {
                        public:

                                InfixFunctionID(
                                        std::string * p_name
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
