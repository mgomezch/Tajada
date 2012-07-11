#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_ADDRESS_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_ADDRESS_HH

// Superclasses:
#include "Tajada/Code/Address.hh"

#include "Tajada/Code/MIPS/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                class Address:
                                        public virtual Tajada::Code::Address
                                {
                                        public:
                                                // TODO: make this pure virtual once all subclasses implement translation to MIPS
                                                virtual Tajada::Code::MIPS::Address::Address * to_mips();
                                };
                        }
                }
        }
}

#endif
