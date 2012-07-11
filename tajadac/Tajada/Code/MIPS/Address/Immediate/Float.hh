#ifndef TAJADA_CODE_MIPS_ADDRESS_IMMEDIATE_FLOAT_HH
#define TAJADA_CODE_MIPS_ADDRESS_IMMEDIATE_FLOAT_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Address/Immediate/Immediate.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Address {
                                namespace Immediate {
                                        class Float:
                                                public virtual Tajada::Code::MIPS::Address::Immediate::Immediate
                                        {
                                                public:
                                                        float value;

                                                        Float(
                                                                float p_value
                                                        );

                                                        virtual std::string show();
                                        };
                                }
                        }
                }
        }
}

#endif
