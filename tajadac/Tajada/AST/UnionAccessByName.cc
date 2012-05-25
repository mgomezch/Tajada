#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/UnionAccessByName.hh"
#include "Tajada/Type/Union.hh"

namespace Tajada {
        namespace AST {
                UnionAccessByName::UnionAccessByName(
                        Tajada::AST::Expression * source,
                        std::string * field
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Union &>(*source->type)[*field], source->is_lvalue),
                        source(source),
                        field(field)
                {}

                std::string UnionAccessByName::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + std::string(u8" ⇒ ")
                                + *field;
                }
        }
}
