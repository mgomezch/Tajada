#include <cassert>
#include <string>

// Class:
#include "Tajada/AST/Literal/Integer.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Expression.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Immediate/Integer.hh"
#include "Tajada/Type/Integer.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        Integer::Integer(
                                std::string * p_value
                        ):
                                Tajada::AST::AST(),
                                Tajada::AST::Expression(new Tajada::Type::Integer(), false),

                                value(std::stoi(*p_value))
                        {}



                        std::string Integer::show(unsigned int depth) {
                                TAJADA_UNUSED_PARAMETER(depth);

                                return std::to_string(value);
                        }



                        Tajada::Code::Intermediate::Address::Address * Integer::genl(
                                Tajada::Code::Block * b
                        ) {
                                TAJADA_UNUSED_PARAMETER(b);

                                assert(false);

                                return nullptr;
                        }



                        Tajada::Code::Intermediate::Address::Address * Integer::genr(
                                Tajada::Code::Block * b
                        ) {
                                TAJADA_UNUSED_PARAMETER(b);

                                return new Tajada::Code::Intermediate::Address::Immediate::Integer(
                                        this->value
                                );
                        }
                }
        }
}
