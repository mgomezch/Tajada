#include <string>

// Class:
#include "Tajada/Code/MIPS/Address/Immediate/Integer.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/MIPS/Address/Address.hh"
#include "Tajada/Code/MIPS/Address/Immediate/Immediate.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Address {
                                namespace Immediate {
                                        Integer::Integer(
                                                unsigned int p_value
                                        ):
                                                Tajada::Code::Address(),
                                                Tajada::Code::MIPS::Address::Address(),
                                                Tajada::Code::MIPS::Address::Immediate::Immediate(),

                                                value(p_value)
                                        {}



                                        std::string Integer::show() {
                                                return std::to_string(this->value);
                                        }
                                }
                        }
                }
        }
}
