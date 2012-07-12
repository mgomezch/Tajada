// Class:
#include "Tajada/Code/MIPS/Instruction/mflo.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                mflo::mflo(
                                        Tajada::Code::MIPS::Address::Register * p_dst
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction(),

                                        dst(p_dst)
                                {}



                                std::string mflo::show() {
                                        return
                                                "mflo "
                                                + this->dst->show()
                                        ;
                                }
                        }
                }
        }
}
