// Class:
#include "Tajada/Code/MIPS/Instruction/bnez.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                bnez::bnez(
                                        Tajada::Code::MIPS::Address::Register * p_condition,
                                        std::string                             p_label
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction(),

                                        condition(p_condition),
                                        label    (p_label    )
                                {}



                                std::string bnez::show() {
                                        return
                                                "bnez "
                                                + this->condition->show()
                                                + ", "
                                                + this->label
                                        ;
                                }
                        }
                }
        }
}
