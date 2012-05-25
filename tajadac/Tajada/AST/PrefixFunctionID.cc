#include <string>

#include "Tajada/AST/AST.hh"
#include "Tajada/AST/FunctionID.hh"
#include "Tajada/AST/PrefixFunctionID.hh"

namespace Tajada {
        namespace AST {
                PrefixFunctionID::PrefixFunctionID(
                        std::string * p_name
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::FunctionID(p_name)
                {}


                std::string PrefixFunctionID::show(unsigned int depth) {
                        return
                                Tajada::AST::FunctionID::show(depth)
                                + std::string(u8" es un plato")
                        ;
                }
        }
}
