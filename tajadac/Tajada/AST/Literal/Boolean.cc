#include <cassert>
#include <string>

// Class:
#include "Tajada/AST/Literal/Boolean.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Expression.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Immediate/Boolean.hh"
#include "Tajada/Type/Boolean.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        Boolean::Boolean(
                                bool p_value
                        ):
                                Tajada::AST::AST(),
                                Tajada::AST::Expression(new Tajada::Type::Boolean(), false),

                                value(p_value)
                        {}



                        std::string Boolean::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);

                                return
                                        value
                                        ? u8"negrito"
                                        : u8"tetero"
                                ;
                        }



                        Tajada::Code::Intermediate::Address::Address * Boolean::genl(
                                Tajada::Code::Block * b
                        ) {
                                TAJADA_UNUSED_PARAMETER(b);

                                assert(false);

                                return nullptr;
                        }



                        Tajada::Code::Intermediate::Address::Address * Boolean::genr(
                                Tajada::Code::Block * b
                        ) {
                                TAJADA_UNUSED_PARAMETER(b);

                                return new Tajada::Code::Intermediate::Address::Immediate::Boolean(
                                        this->value
                                );
                        }
                }
        }
}
