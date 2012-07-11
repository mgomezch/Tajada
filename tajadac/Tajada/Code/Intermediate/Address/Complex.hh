#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_COMPLEX_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_COMPLEX_HH

#include <vector>
#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Address.hh"

#include "Tajada/Type/Tuple.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                class Complex:
                                        public virtual Tajada::Code::Intermediate::Address::Address
                                {
                                        public:
                                                std::vector<Tajada::Code::Intermediate::Address::Address *> elems;
                                                Tajada::Type::Tuple * type;

                                                Complex(
                                                        Tajada::Type::Tuple * p_type
                                                );

                                                virtual std::string show();

                                                virtual Tajada::Code::MIPS::Address::Address * to_mips();
                                };
                        }
                }
        }
}

#endif
