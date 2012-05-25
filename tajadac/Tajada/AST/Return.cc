#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Return.hh"

namespace Tajada {
        namespace AST {
                Return::Return(
                        Tajada::AST::Expression * expression
                ):
                        expression(expression)
                {}

                std::string Return::show(unsigned int depth) {
                        return
                                u8"retorna "
                                + expression->show(depth);
                }
        }
}
