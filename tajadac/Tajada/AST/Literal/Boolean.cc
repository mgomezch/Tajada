#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Literal/Boolean.hh"
#include "Tajada/Type/Boolean.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        Boolean::Boolean(
                                bool p_value
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Boolean(), false),
                                value(p_value)
                        {}

                        std::string Boolean::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return value ? std::string(u8"negrito") : std::string(u8"tetero");
                        }
                }
        }
}
