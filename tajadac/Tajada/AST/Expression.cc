#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                Expression::Expression(
                        Tajada::Type::Type * p_type,
                        bool p_is_lvalue
                ):
                        type(p_type),
                        is_lvalue(p_is_lvalue)
                {}



                Tajada::Code::Block * Expression::genl(
                        Tajada::Code::Block * b
                ) {
                        // TODO: delete this implementation once all subclasses have their own
                        return b;
                }



                Tajada::Code::Block * Expression::genr(
                        Tajada::Code::Block * b
                ) {
                        // TODO: delete this implementation once all subclasses have their own
                        return b;
                }
        }
}
