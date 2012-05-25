#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Literal/Character.hh"
#include "Tajada/Type/Character.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        Character::Character(
                                std::string * value
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Character(), false),
                                value(value)
                        {}

                        std::string Character::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return
                                        std::string(u8"caraota(")
                                        + *value
                                        + std::string(u8")");
                        }
                }
        }
}
