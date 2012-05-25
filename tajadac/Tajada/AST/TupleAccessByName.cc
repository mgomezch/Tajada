#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/TupleAccessByName.hh"
#include "Tajada/Type/Tuple.hh"

namespace Tajada {
        namespace AST {
                TupleAccessByName::TupleAccessByName(
                        Tajada::AST::Expression * source,
                        std::string * field
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Tuple &>(*source->type)[*field], source->is_lvalue),
                        source(source),
                        field(field)
                {}

                std::string TupleAccessByName::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + std::string(u8" → ")
                                + *field;
                }
        }
}
