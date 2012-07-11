// Class:
#include "Tajada/Code/MIPS/Instruction/j.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                j::j(
                                        std::string p_label
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction(),

                                        label(p_label)
                                {}



                                std::string j::show() {
                                        return
                                                "j "
                                                + this->label
                                        ;
                                }
                        }
                }
        }
}
