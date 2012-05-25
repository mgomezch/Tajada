#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/VariableUse.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                VariableUse::VariableUse(
                        unsigned int p_scope_id,
                        std::string * p_name,
                        Tajada::Type::Type * p_type
                ):
                        Tajada::AST::Expression(p_type, true),
                        scope_id(p_scope_id),
                        name(p_name)
                {}

                std::string VariableUse::show(unsigned int depth) {
                        TAJADA_UNUSED_PARAMETER(depth);
                        return
                                *name
                                + u8"[[scope: "
                                + std::to_string(scope_id)
                                + u8"]]";
                }
        }
}
