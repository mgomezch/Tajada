#include <string>

// Class:
#include "Tajada/AST/InfixFunctionID.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/FunctionID.hh"

#include "Tajada/AST/Associativity.hh"

namespace Tajada {
        namespace AST {
                InfixFunctionID::InfixFunctionID(
                        std::string * p_name
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::FunctionID(p_name)
                {}


                std::string InfixFunctionID::show(unsigned int depth) {
                        return
                                FunctionID::show(depth)
                        ;
                }
        }
}
