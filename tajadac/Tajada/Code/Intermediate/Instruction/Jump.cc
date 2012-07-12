#include <vector>

// Class:
#include "Tajada/Code/Intermediate/Instruction/Jump.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Block.hh"
#include "Tajada/Code/MIPS/Instruction/Comment.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/j.hh"

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
                                                + this->target->getLabel()
                                        ;
                                }



                                std::vector<Tajada::Code::MIPS::Instruction::Instruction *> Jump::to_mips() {
                                        return
                                                { new Tajada::Code::MIPS::Instruction::Comment(this->show())

                                                , new Tajada::Code::MIPS::Instruction::j(
                                                        this->target->getLabel()
                                                )

                                                }
                                        ;
                                }
                        }
                }
        }
}
