#include <string>

#include "Tajada/AST/AST.hh"
#include "Tajada/AST/FunctionID.hh"

namespace Tajada {
        namespace AST {
                FunctionID::FunctionID(
                        std::string * p_name
                ):
                        Tajada::AST::AST(),

                        name(p_name)
                {}


                std::string FunctionID::show(unsigned int depth) {
                        TAJADA_UNUSED_PARAMETER(depth);
                        return *name;
                }
        }
}
