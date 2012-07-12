// Class:
#include "Tajada/Code/MIPS/Instruction/la.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Address.hh"
#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                la::la(
                                        Tajada::Code::MIPS::Address::Address  * p_src,
                                        Tajada::Code::MIPS::Address::Register * p_dst
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction(),

                                        src(p_src),
                                        dst(p_dst)
                                {}



                                std::string la::show() {
                                        return
                                                "la "
                                                + this->dst->show()
                                                + ", "
                                                + this->src->show()
                                        ;
                                }
                        }
                }
        }
}
