#ifndef TAJADA_CODE_MIPS_ADDRESS_UNIMPLEMENTED_HH
#define TAJADA_CODE_MIPS_ADDRESS_UNIMPLEMENTED_HH

// TODO: remove this file once all intermediate addresses implement translation to MIPS

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Address/Address.hh"

#include "Tajada/Code/Intermediate/Address/Unimplemented.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Address {
                                class Unimplemented:
                                        public virtual Tajada::Code::MIPS::Address::Address
                                {
                                        public:
                                                Tajada::Code::Intermediate::Address::Address * unimplemented;

                                                Unimplemented(
                                                        Tajada::Code::Intermediate::Address::Address * p_unimplemented
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
