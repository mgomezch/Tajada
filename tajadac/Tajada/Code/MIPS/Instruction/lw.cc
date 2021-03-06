// Class:
#include "Tajada/Code/MIPS/Instruction/lw.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                lw::lw(
                                        Tajada::Code::MIPS::Address::Address  * p_src,
                                        Tajada::Code::MIPS::Address::Register * p_dst
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction(),

                                        src(p_src),
                                        dst(p_dst)
                                {}



                                std::string lw::show() {
                                        auto rsrc = dynamic_cast<Tajada::Code::MIPS::Address::Register *>(this->src);
                                        return
                                                "lw "
                                                + this->dst->show()
                                                + ", "
                                                + (
                                                        (rsrc && rsrc->offset) || !rsrc
                                                        ? this->src->show()
                                                        : "(" + this->src->show() + ")"
                                                )
                                        ;
                                }
                        }
                }
        }
}
