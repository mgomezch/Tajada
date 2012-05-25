#include <string>

#include "Tajada/AST/Assignment.hh"
#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                Assignment::Assignment(
                        Tajada::AST::Expression * lhs,
                        Tajada::AST::Expression * rhs
                ):
                        lhs(lhs),
                        rhs(rhs)
                {}

                std::string Assignment::show(unsigned int depth) {
                        return
                                lhs->show(depth)
                                + std::string(u8" ≔ ")
                                + rhs->show(depth);
                }
        }
}
