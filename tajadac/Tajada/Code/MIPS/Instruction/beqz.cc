// Class:
#include "Tajada/Code/MIPS/Instruction/beqz.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                beqz::beqz(
                                        Tajada::Code::MIPS::Address::Register * p_condition,
                                        std::string                             p_label
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction(),

                                        condition(p_condition),
                                        label    (p_label    )
                                {}



                                std::string beqz::show() {
                                        return
                                                "beqz "
                                                + this->condition->show()
                                                + ", "
                                                + this->label
                                        ;
                                }
                        }
                }
        }
}
