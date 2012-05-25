#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Literal/Integer.hh"
#include "Tajada/Type/Integer.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        Integer::Integer(
                                std::string * p_value
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Integer(), false),
                                value(std::stoi(*p_value))
                        {}

                        std::string Integer::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return std::to_string(value);
                        }
                }
        }
}
