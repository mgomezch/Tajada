#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_UNIMPLEMENTED_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_UNIMPLEMENTED_HH

// TODO: remove this file once all subclasses have their implementation of genl/genr

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                class Unimplemented:
                                        public virtual Tajada::Code::Intermediate::Address::Address
                                {
                                        public:
                                                Unimplemented();

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
