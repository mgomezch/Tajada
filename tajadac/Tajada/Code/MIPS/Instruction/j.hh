#ifndef TAJADA_CODE_MIPS_INSTRUCTION_J_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_J_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class j:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                std::string label;

                                                j(
                                                        std::string p_label
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
