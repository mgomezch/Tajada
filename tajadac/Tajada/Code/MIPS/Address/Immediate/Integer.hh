#ifndef TAJADA_CODE_MIPS_ADDRESS_IMMEDIATE_INTEGER_HH
#define TAJADA_CODE_MIPS_ADDRESS_IMMEDIATE_INTEGER_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Address/Immediate/Immediate.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Address {
                                namespace Immediate {
                                        class Integer:
                                                public virtual Tajada::Code::MIPS::Address::Immediate::Immediate
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
