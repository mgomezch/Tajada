#include <string>

// Class:
#include "Tajada/AST/Expression.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"

#include "Tajada/Type/Type.hh"
#include "Tajada/Code/Intermediate/Location/Location.hh"

// TODO: remove this once all subclasses have their implementation of genl/genr
namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Location {
                                class Unimplemented:
                                        public virtual Tajada::Code::Intermediate::Location::Location
                                {
                                        std::string show() {
                                                return u8"‹UNIMPLEMENTED›";
                                        }
                                };
                        }
                }
        }
}

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
                Tajada::Code::Intermediate::Location::Location * Expression::genl(
                        Tajada::Code::Block * b
                ) {
                        TAJADA_UNUSED_PARAMETER(b);

                        return new Tajada::Code::Intermediate::Location::Unimplemented();
                }



                // TODO: delete this implementation once all subclasses have their own
                Tajada::Code::Intermediate::Location::Location * Expression::genr(
                        Tajada::Code::Block * b
                ) {
                        TAJADA_UNUSED_PARAMETER(b);

                        return new Tajada::Code::Intermediate::Location::Unimplemented();
                }
        }
}
