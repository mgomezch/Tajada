#include <string>

// Class:
#include "Tajada/AST/Expression.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Unimplemented.hh" // TODO: remove this once all subclasses have their implementation of genl/genr
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                Expression::Expression(
                        Tajada::Type::Type * p_type,
                        bool p_is_lvalue
                ):
                        Tajada::AST::AST(),

                        type     (p_type     ),
                        is_lvalue(p_is_lvalue)
                {}



                // TODO: delete this implementation once all subclasses have their own
                Tajada::Code::Intermediate::Address::Address * Expression::genl(
                        Tajada::Code::Block * b
                ) {
                        TAJADA_UNUSED_PARAMETER(b);

                        return new Tajada::Code::Intermediate::Address::Unimplemented();
                }



                // TODO: delete this implementation once all subclasses have their own
                Tajada::Code::Intermediate::Address::Address * Expression::genr(
                        Tajada::Code::Block * b
                ) {
                        TAJADA_UNUSED_PARAMETER(b);

                        return new Tajada::Code::Intermediate::Address::Unimplemented();
                }
        }
}
