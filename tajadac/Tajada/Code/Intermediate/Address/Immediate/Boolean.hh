#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_IMMEDIATE_BOOLEAN_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_IMMEDIATE_BOOLEAN_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Immediate/Immediate.hh"

#include "Tajada/Code/MIPS/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                namespace Immediate {
                                        class Boolean:
                                                public virtual Tajada::Code::Intermediate::Address::Immediate::Immediate
                                        {
                                                public:
                                                        bool value;

                                                        Boolean(
                                                                bool p_value
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
