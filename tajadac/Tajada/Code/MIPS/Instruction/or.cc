// Class:
#include "Tajada/Code/MIPS/Instruction/or.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                or_::or_(
                                        Tajada::Code::MIPS::Address::Register * p_lsrc,
                                        Tajada::Code::MIPS::Address::Register * p_rsrc,
                                        Tajada::Code::MIPS::Address::Register * p_dst
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction(),

                                        lsrc(p_lsrc),
                                        rsrc(p_rsrc),
                                        dst (p_dst )
                                {}



                                std::string or_::show() {
                                        return
                                                "or "
                                                + this->dst->show()
                                                + ", "
                                                + this->lsrc->show()
                                                + ", "
                                                + this->rsrc->show()
                                        ;
                                }
                        }
                }
        }
}
