#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Literal/Integer.hh"
#include "Tajada/AST/UnionAccessByInteger.hh"
#include "Tajada/Type/Union.hh"

namespace Tajada {
        namespace AST {
                UnionAccessByInteger::UnionAccessByInteger(
                        Tajada::AST::Expression * source,
                        Tajada::AST::Literal::Integer * field
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Union &>(*source->type)[field->value], source->is_lvalue),
                        source(source),
                        field(field)
                {}

                std::string UnionAccessByInteger::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + std::string(u8" → ")
                                + field->show(depth);
                }
        }
}
