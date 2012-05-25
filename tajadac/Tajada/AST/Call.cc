#include <string>

#include "Tajada/AST/Call.hh"
#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Function.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                Call::Call(
                        std::string * p_name,
                        Tajada::AST::Function ** p_definition_ptr,
                        Tajada::AST::Expression * p_argument,
                        Tajada::Type::Type * p_return_type
                ):
                        Tajada::AST::Expression(p_return_type, false),
                        name(p_name),
                        definition_ptr(p_definition_ptr),
                        argument(p_argument)
                {}

                std::string Call::show(unsigned int depth) {
                        return
                                *name
                                + u8" $ "
                                + argument->show(depth)
                        ;
                }
        }
}
