#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Sequence.hh"

namespace Tajada {
        namespace AST {
                Sequence::Sequence(
                        Tajada::AST::Expression * first,
                        Tajada::AST::Expression * second
                ):
                        Tajada::AST::Expression(second->type, second->is_lvalue),
                        first(first),
                        second(second)
                {}

                std::string Sequence::show(unsigned int depth) {
                        return
                                first->show(depth)
                                + std::string(u8", ")
                                + second->show(depth);
                }
        }
}
