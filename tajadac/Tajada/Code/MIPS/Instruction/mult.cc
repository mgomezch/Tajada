// Class:
#include "Tajada/Code/MIPS/Instruction/mult.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                mult::mult(
                                        Tajada::Code::MIPS::Address::Register * p_lsrc,
                                        Tajada::Code::MIPS::Address::Register * p_rsrc
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction(),

                                        lsrc(p_lsrc),
                                        rsrc(p_rsrc)
                                {}



                                std::string mult::show() {
                                        return
                                                "mult "
                                                + this->lsrc->show()
                                                + ", "
                                                + this->rsrc->show()
                                        ;
                                }
                        }
                }
        }
}
