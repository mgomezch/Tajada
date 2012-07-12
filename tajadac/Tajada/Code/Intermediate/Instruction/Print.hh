#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_PRINT_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_PRINT_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                class Print:
                                        public virtual Tajada::Code::Intermediate::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::Intermediate::Address::Address * src;

                                                Print(
                                                        Tajada::Code::Intermediate::Address::Address * p_src
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
