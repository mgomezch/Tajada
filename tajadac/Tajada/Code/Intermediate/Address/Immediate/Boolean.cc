#include <string>

// Class:
#include "Tajada/Code/Intermediate/Address/Immediate/Boolean.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Immediate/Immediate.hh"

#include "Tajada/Code/MIPS/Address/Address.hh"
#include "Tajada/Code/MIPS/Address/Immediate/Integer.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                namespace Immediate {
                                        Boolean::Boolean(
                                                bool p_value
                                        ):
                                                Tajada::Code::Address(),
                                                Tajada::Code::Intermediate::Address::Address(),
                                                Tajada::Code::Intermediate::Address::Immediate::Immediate(),

                                                value(p_value)
                                        {}



                                        std::string Boolean::show() {
                                                return
                                                        std::to_string(this->value)
                                                        + u8"[B]"
                                                ;
                                        }



                                        Tajada::Code::MIPS::Address::Address * Boolean::to_mips() {
                                                return new Tajada::Code::MIPS::Address::Immediate::Integer(value);
                                        }
                                }
                        }
                }
        }
}
