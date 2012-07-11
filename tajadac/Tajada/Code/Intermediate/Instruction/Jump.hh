#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_JUMP_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_JUMP_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Block.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                class Jump:
                                        public virtual Tajada::Code::Intermediate::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::Block * target;

                                                Jump(
                                                        Tajada::Code::Block * p_target
                                                );

                                                virtual std::string show();

                                                virtual std::vector<Tajada::Code::MIPS::Instruction::Instruction *> to_mips();
                                };
                        }
                }
        }
}

#endif
