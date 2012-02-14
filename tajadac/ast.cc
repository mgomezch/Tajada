#include <string>

#include "ast.hh"

namespace Tajada {
        namespace AST {
                Expression::Expression(Tajada::types::Type * type):
                        type(type)
                {}

                Expression::~Expression() {}

                BooleanLiteral::BooleanLiteral():
                        Expression(new Tajada::types::Boolean())
                {}

                BooleanLiteral::~BooleanLiteral() {
                        delete type;
                }

                TrueLiteral ::TrueLiteral () {}
                FalseLiteral::FalseLiteral() {}
        }
}
