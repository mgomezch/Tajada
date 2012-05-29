#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_IMMEDIATE_INTEGER_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_IMMEDIATE_INTEGER_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Immediate/Immediate.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                namespace Immediate {
                                        class Integer:
                                                public virtual Tajada::Code::Intermediate::Address::Immediate::Immediate
                                        {
                                                public:
                                                        unsigned int value;

                                                        Integer(
                                                                unsigned int p_value
                                                        );

                                                        virtual std::string show();
                                        };
                                }
                        }
                }
        }
}

#endif
