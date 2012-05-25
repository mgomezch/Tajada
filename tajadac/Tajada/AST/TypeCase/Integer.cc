#include <string>

// Class:
#include "Tajada/AST/TypeCase/Integer.hh"

// Superclasses:
#include "Tajada/AST/TypeCase/TypeCase.hh"

#include "Tajada/AST/Statement.hh"

namespace Tajada {
        namespace AST {
                namespace TypeCase {
                        Integer::Integer(
                                std::string * p_index,
                                Tajada::AST::Statement * p_body
                        ):
                                Tajada::AST::TypeCase::TypeCase(p_body),
                                index(std::stoi(*p_index))
                        {}

                        std::string Integer::show(unsigned int depth) {
                                return
                                        std::to_string(index)
                                        + u8" ∶ "
                                        + body->show(depth)
                                ;
                        }
                }
        }
}
