#include <string>

// Class:
#include "Tajada/Code/Intermediate/Address/Temporary.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"

#include "scope.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                unsigned long int Temporary::next_id = 0;

                                Temporary::Temporary():
                                        Tajada::Code::Address(),
                                        Tajada::Code::Intermediate::Address::Address(),

                                        id(++Tajada::Code::Intermediate::Address::Temporary::next_id)
                                {}



                                std::string Temporary::show() {
                                        return
                                                u8"$t"
                                                + std::to_string(this->id)
                                        ;
                                }
                        }
                }
        }
}
