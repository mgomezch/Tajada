#ifndef TAJADA_CODE_MIPS_INSTRUCTION_SYSCALL_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_SYSCALL_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class syscall:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                syscall();

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
