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
        }
}
