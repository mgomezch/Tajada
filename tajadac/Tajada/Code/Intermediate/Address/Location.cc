// Class:
#include "Tajada/Code/Intermediate/Address/Location.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                Location::Location(
                                        unsigned int p_offset
                                ):
                                        Tajada::Code::Address(),
                                        Tajada::Code::Intermediate::Address::Address(),

                                        offset(p_offset)
                                {}
                        }
                }
        }
}
