// TODO: remove this whole file once all subclasses implement translation to MIPS

// Class:
#include "Tajada/Code/Intermediate/Address/Address.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"

#include "Tajada/Code/MIPS/Address/Address.hh"
#include "Tajada/Code/MIPS/Address/Unimplemented.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                Tajada::Code::MIPS::Address::Address * Address::to_mips() {
                                        return new Tajada::Code::MIPS::Address::Unimplemented(this);
                                }
                        }
                }
        }
}
