#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/ExpressionStatement.hh"

namespace Tajada {
        namespace AST {
                ExpressionStatement::ExpressionStatement(
                        Tajada::AST::Expression * expression
                ):
                        expression(expression)
                {}

                std::string ExpressionStatement::show(unsigned int depth) {
                        return
                                expression->show(depth);
                }
        }
}
