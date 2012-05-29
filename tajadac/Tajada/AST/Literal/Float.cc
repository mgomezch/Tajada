#include <cassert>
#include <string>

// Class:
#include "Tajada/AST/Literal/Float.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Expression.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Immediate/Float.hh"
#include "Tajada/Type/Float.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        Float::Float(
                                std::string * p_integer,
                                std::string * p_fractional
                        ):
                                Tajada::AST::AST(),
                                Tajada::AST::Expression(new Tajada::Type::Float(), false),

                                value(std::stof(*p_integer + "." + *p_fractional))
                        {}



                        std::string Float::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);
                                return
                                        std::string(u8"papelón(")
                                        + std::to_string(value)
                                        + std::string(u8")");
                        }



                        Tajada::Code::Intermediate::Address::Address * Float::genl(
                                Tajada::Code::Block * b
                        ) {
                                TAJADA_UNUSED_PARAMETER(b);

                                assert(false);

                                return nullptr;
                        }



                        Tajada::Code::Intermediate::Address::Address * Float::genr(
                                Tajada::Code::Block * b
                        ) {
                                TAJADA_UNUSED_PARAMETER(b);

                                return new Tajada::Code::Intermediate::Address::Immediate::Float(
                                        this->value
                                );
                        }
                }
        }
}
