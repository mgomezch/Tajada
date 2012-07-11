// TODO: remove this file once all intermediate addresses implement translation to MIPS

// Class:
#include "Tajada/Code/MIPS/Address/Unimplemented.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/MIPS/Address/Address.hh"

#include "Tajada/Code/Intermediate/Address/Unimplemented.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Address {
                                Unimplemented::Unimplemented(
                                        Tajada::Code::Intermediate::Address::Address * p_unimplemented
                                ):
                                        Tajada::Code::Address(),
                                        Tajada::Code::MIPS::Address::Address(),

                                        unimplemented(p_unimplemented)
                                {}

                                std::string Unimplemented::show() {
                                        return u8"# UNIMPLEMENTED INTERMEDIATE ADDRESS: " + unimplemented->show();
                                }
                        }
                }
        }
}
