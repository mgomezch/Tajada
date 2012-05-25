#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Literal/Float.hh"
#include "Tajada/Type/Float.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        Float::Float(
                                std::string * p_integer,
                                std::string * p_fractional
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Float(), false),
                                value(std::stof(*p_integer + "." + *p_fractional))
                        {}

                        std::string Float::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return
                                        std::string(u8"papelón(")
                                        + std::to_string(value)
                                        + std::string(u8")");
                        }
                }
        }
}
