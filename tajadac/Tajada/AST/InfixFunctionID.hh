#ifndef TAJADA_AST_INFIXFUNCTIONID_HH
#define TAJADA_AST_INFIXFUNCTIONID_HH

#include <string>

// Superclasses:
#include "Tajada/AST/FunctionID.hh"

#include "Tajada/AST/Associativity.hh"
#include "Tajada/AST/AST.hh"

namespace Tajada {
        namespace AST {
                class InfixFunctionID : public virtual Tajada::AST::FunctionID {
                        public:
                                unsigned int               precedence   ;
                                Tajada::AST::Associativity associativity;

                                InfixFunctionID(
                                        std::string                * p_name         ,
                                        std::string                * p_precedence   ,
                                        Tajada::AST::Associativity   p_associativity
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
