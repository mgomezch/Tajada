#include <vector>

// Class:
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Instruction/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Unimplemented.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                Instruction::Instruction():
                                        Tajada::Code::Instruction()
                                {}

                                // TODO: delete this once all instructions implement translation to MIPS
                                std::vector<Tajada::Code::MIPS::Instruction::Instruction *> Instruction::to_mips() {
                                        return { new Tajada::Code::MIPS::Instruction::Unimplemented(this) };
                                }
                        }
                }
        }
}
