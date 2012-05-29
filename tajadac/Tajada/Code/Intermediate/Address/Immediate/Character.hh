#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_IMMEDIATE_CHARACTER_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_IMMEDIATE_CHARACTER_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Immediate/Immediate.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                namespace Immediate {
                                        class Character:
                                                public virtual Tajada::Code::Intermediate::Address::Immediate::Immediate
                                        {
                                                public:
                                                        std::string * value;

                                                        Character(
                                                                std::string * p_value
                                                        );

                                                        virtual std::string show();
                                        };
                                }
                        }
                }
        }
}

#endif
