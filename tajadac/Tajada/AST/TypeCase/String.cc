#include <string>

// Class:
#include "Tajada/AST/TypeCase/String.hh"

// Superclasses:
#include "Tajada/AST/TypeCase/TypeCase.hh"

#include "Tajada/AST/Statement.hh"

namespace Tajada {
        namespace AST {
                namespace TypeCase {
                        String::String(
                                std::string * p_index,
                                Tajada::AST::Statement * p_body
                        ):
                                Tajada::AST::TypeCase::TypeCase(p_body),
                                index(p_index)
                        {}

                        std::string String::show(unsigned int depth) {
                                return
                                        *index
                                        + u8" ∶ "
                                        + body->show(depth)
                                ;
                        }
                }
        }
}
