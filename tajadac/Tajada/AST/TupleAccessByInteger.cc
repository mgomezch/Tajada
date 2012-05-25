#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Literal/Integer.hh"
#include "Tajada/AST/TupleAccessByInteger.hh"
#include "Tajada/Type/Tuple.hh"

namespace Tajada {
        namespace AST {
                TupleAccessByInteger::TupleAccessByInteger(
                        Tajada::AST::Expression * source,
                        Tajada::AST::Literal::Integer * field
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Tuple &>(*source->type)[field->value], source->is_lvalue),
                        source(source),
                        field(field)
                {}

                std::string TupleAccessByInteger::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + std::string(u8" → ")
                                + field->show(depth);
                }
        }
}
