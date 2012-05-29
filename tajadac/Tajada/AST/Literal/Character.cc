#include <cassert>
#include <string>

// Class:
#include "Tajada/AST/Literal/Character.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Expression.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Immediate/Character.hh"
#include "Tajada/Type/Character.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        Character::Character(
                                std::string * value
                        ):
                                Tajada::AST::AST(),
                                Tajada::AST::Expression(new Tajada::Type::Character(), false),

                                value(value)
                        {}



                        std::string Character::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return
                                        std::string(u8"caraota(")
                                        + *value
                                        + std::string(u8")");
                        }



                        Tajada::Code::Intermediate::Address::Address * Character::genl(
                                Tajada::Code::Block * b
                        ) {
                                TAJADA_UNUSED_PARAMETER(b);

                                assert(false);

                                return nullptr;
                        }



                        Tajada::Code::Intermediate::Address::Address * Character::genr(
                                Tajada::Code::Block * b
                        ) {
                                TAJADA_UNUSED_PARAMETER(b);

                                return new Tajada::Code::Intermediate::Address::Immediate::Character(
                                        this->value
                                );
                        }
                }
        }
}
