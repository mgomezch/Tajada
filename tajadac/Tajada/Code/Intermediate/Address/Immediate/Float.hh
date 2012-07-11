#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_IMMEDIATE_FLOAT_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_IMMEDIATE_FLOAT_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Immediate/Immediate.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                namespace Immediate {
                                        class Float:
                                                public virtual Tajada::Code::Intermediate::Address::Immediate::Immediate
                                        {
                                                public:
                                                        float value;

                                                        Float(
                                                                float p_value
                                                        );

                                                        virtual std::string show();

                                                        virtual Tajada::Code::MIPS::Address::Address * to_mips();
                                        };
                                }
                        }
                }
        }
}

#endif
