#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Literal/String.hh"
#include "Tajada/Type/Array.hh"
#include "Tajada/Type/Character.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        String::String(
                                std::string * value
                        ):
                                Tajada::AST::Expression(new Tajada::Type::Array(new Tajada::Type::Character()), false),
                                value(value)
                        {}

                        std::string String::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return
                                        std::string(u8"“")
                                        + *value
                                        + std::string(u8"”");
                        }
                }
        }
}
