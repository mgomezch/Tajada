// TODO: remove this file once all subclasses have their implementation of genl/genr

// Class:
#include "Tajada/Code/Intermediate/Address/Unimplemented.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                Unimplemented::Unimplemented():
                                        Tajada::Code::Address(),
                                        Tajada::Code::Intermediate::Address::Address()
                                {}

                                std::string Unimplemented::show() {
                                        return u8"‹UNIMPLEMENTED›";
                                }
                        }
                }
        }
}
