#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_COMPLEX_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_COMPLEX_HH

#include <vector>
#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                class Complex:
                                        public virtual Tajada::Code::Intermediate::Address::Address
                                {
                                        public:
                                                std::vector<Tajada::Code::Intermediate::Address::Address *> elems;

                                                Complex();

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
