#include <string>

// Class:
#include "Tajada/Code/MIPS/Address/Label.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/MIPS/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Address {
                                Label::Label(
                                        std::string p_label
                                ):
                                        Tajada::Code::Address(),
                                        Tajada::Code::MIPS::Address::Address(),

                                        label(p_label)
                                {}



                                std::string Label::show() {
                                        return this->label;
                                }
                        }
                }
        }
}
