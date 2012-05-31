#include <string>

// Class:
#include "Tajada/AST/ExpressionStatement.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                ExpressionStatement::ExpressionStatement(
                        Tajada::AST::Expression * expression
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),

                        expression(expression)
                {}



                std::string ExpressionStatement::show(unsigned int depth) {
                        return
                                expression->show(depth)
                        ;
                }



                void ExpressionStatement::gen(
                        Tajada::Code::Block * b
                ) {
                        this->expression->genr(b);
                }
        }
}
