#include <string>

// Class:
#include "Tajada/Code/MIPS/Address/Immediate/Float.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/MIPS/Address/Address.hh"
#include "Tajada/Code/MIPS/Address/Immediate/Immediate.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Address {
                                namespace Immediate {
                                        Float::Float(
                                                float p_value
                                        ):
                                                Tajada::Code::Address(),
                                                Tajada::Code::MIPS::Address::Address(),
                                                Tajada::Code::MIPS::Address::Immediate::Immediate(),

                                                value(p_value)
                                        {}



                                        std::string Float::show() {
                                                return std::to_string(this->value);
                                        }
                                }
                        }
                }
        }
}
