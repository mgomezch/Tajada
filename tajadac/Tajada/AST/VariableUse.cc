#include <string>

// Class:
#include "Tajada/AST/VariableUse.hh"

// Superclasses:
#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/AST.hh"

#include "Tajada/Type/Type.hh"
#include "Tajada/Code/Intermediate/Address/Variable.hh"

#include "scope.hh"

namespace Tajada {
        namespace AST {
                VariableUse::VariableUse(
                        Tajada::Scope      * p_scope,
                        std::string        * p_name ,
                        Tajada::Type::Type * p_type
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Expression(p_type, true),

                        scope(p_scope),
                        name(p_name)
                {}



                std::string VariableUse::show(unsigned int depth) {
                        TAJADA_UNUSED_PARAMETER(depth);

                        return
                                *this->name
                                + u8"[[scope: "
                                + std::to_string(this->scope->id)
                                + u8"]]"
                        ;
                }



                Tajada::Code::Intermediate::Address::Address * VariableUse::genl(
                        Tajada::Code::Block * b
                ) {
                        TAJADA_UNUSED_PARAMETER(b);

                        return new Tajada::Code::Intermediate::Address::Variable(
                                this->scope,
                                this->name
                        );
                }



                Tajada::Code::Intermediate::Address::Address * VariableUse::genr(
                        Tajada::Code::Block * b
                ) {
                        TAJADA_UNUSED_PARAMETER(b);

                        return new Tajada::Code::Intermediate::Address::Variable(
                                this->scope,
                                this->name
                        );
                }
        }
}
