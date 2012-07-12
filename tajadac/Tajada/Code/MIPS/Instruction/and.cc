// Class:
#include "Tajada/Code/MIPS/Instruction/and.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                and_::and_(
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



                                std::string and_::show() {
                                        return
                                                "and "
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
