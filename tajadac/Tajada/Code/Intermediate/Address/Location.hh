#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_LOCATION_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_LOCATION_HH

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                class Location:
                                        public virtual Tajada::Code::Intermediate::Address::Address
                                {
                                        public:
                                                unsigned int offset;

                                                Location(
                                                        unsigned int p_offset = 0
                                                );
                                };
                        }
                }
        }
}

#endif
