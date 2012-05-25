#include <string>

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Statement.hh"
#include "Tajada/AST/TypeAlias.hh"

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                TypeAlias::TypeAlias(
                        std::string        * p_name,
                        Tajada::Type::Type * p_type
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),

                        name(p_name),
                        type(p_type)
                {}


                std::string TypeAlias::show(unsigned int depth) {
                        return
                                *name
                                + std::string(u8" es dulce de ")
                                + type->show(depth)
                        ;
                }
        }
}
