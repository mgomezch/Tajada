#include <cassert>
#include <string>

// Class:
#include "Tajada/AST/Call.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Expression.hh"

#include "Tajada/AST/BuiltinFunction.hh"
#include "Tajada/AST/Function.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Unimplemented.hh" // TODO: remove this once funcion calls are completely implemented
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                Call::Call(
                        std::string              * p_name          ,
                        Tajada::AST::Function   ** p_definition_ptr,
                        Tajada::AST::Expression  * p_argument      ,
                        Tajada::Type::Type       * p_return_type
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Expression(p_return_type, false),

                        name          (p_name          ),
                        definition_ptr(p_definition_ptr),
                        argument      (p_argument      )
                {}



                std::string Call::show(unsigned int depth) {
                        return
                                *name
                                + u8" $ "
                                + argument->show(depth)
                        ;
                }



                Tajada::Code::Intermediate::Address::Address * Call::genl(
                        Tajada::Code::Block * b
                ) {
                        TAJADA_UNUSED_PARAMETER(b);

                        assert(false);

                        return nullptr;
                }



                Tajada::Code::Intermediate::Address::Address * Call::genr(
                        Tajada::Code::Block * b
                ) {
                        if (auto bf = dynamic_cast<Tajada::AST::BuiltinFunction *>(*this->definition_ptr)) {
                                return bf->generator(this, b);
                        }

                        return new Tajada::Code::Intermediate::Address::Unimplemented();
                }
        }
}
