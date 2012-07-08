// Class:
#include "Tajada/Code/Intermediate/Instruction/Jump.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Block.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                Jump::Jump(
                                        Tajada::Code::Block * p_target
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::Intermediate::Instruction::Instruction(),

                                        target(p_target)
                                {}

                                std::string Jump::show() {
                                        return
                                                "goto "
                                                + this->target->label
                                        ;
                                }
                        }
                }
        }
}
