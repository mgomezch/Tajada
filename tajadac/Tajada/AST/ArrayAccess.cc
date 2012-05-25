#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/ArrayAccess.hh"
#include "Tajada/Type/Array.hh"

namespace Tajada {
        namespace AST {
                ArrayAccess::ArrayAccess(
                        Tajada::AST::Expression * source,
                        Tajada::AST::Expression * position
                ):
                        Tajada::AST::Expression(dynamic_cast<Tajada::Type::Array &>(*source->type).contents, source->is_lvalue),
                        source(source),
                        position(position)
                {}

                std::string ArrayAccess::show(unsigned int depth) {
                        return
                                source->show(depth)
                                + std::string(u8"[")
                                + position->show(depth)
                                + std::string(u8"]");
                }
        }
}
