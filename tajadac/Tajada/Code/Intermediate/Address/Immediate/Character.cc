#include <string>

// Class:
#include "Tajada/Code/Intermediate/Address/Immediate/Character.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Immediate/Immediate.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                namespace Immediate {
                                        Character::Character(
                                                std::string * p_value
                                        ):
                                                Tajada::Code::Address(),
                                                Tajada::Code::Intermediate::Address::Address(),
                                                Tajada::Code::Intermediate::Address::Immediate::Immediate(),

                                                value(p_value)
                                        {}



                                        std::string Character::show() {
                                                return
                                                        u8"'"
                                                        + *this->value
                                                        + u8"'"
                                                ;
                                        }
                                }
                        }
                }
        }
}
