#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_INSTRUCTION_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_INSTRUCTION_HH

#include <vector>

// Superclasses:
#include "Tajada/Code/Instruction.hh"

#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                class Instruction : public virtual Tajada::Code::Instruction {
                                        public:
                                                Instruction();

                                                // TODO: make this pure virtual once all instructions implement translation to MIPS
                                                virtual std::vector<Tajada::Code::MIPS::Instruction::Instruction *> to_mips();
                                };
                        }
                }
        }
}

#endif
