#ifndef TAJADA_CODE_MIPS_INSTRUCTION_BEQZ_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_BEQZ_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class beqz:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::MIPS::Address::Register * condition;
                                                std::string                             label    ;

                                                beqz(
                                                        Tajada::Code::MIPS::Address::Register * p_condition,
                                                        std::string                             p_label
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
