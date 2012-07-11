// Class:
#include "Tajada/Code/MIPS/Instruction/li.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Immediate/Integer.hh"
#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                li::li(
                                        Tajada::Code::MIPS::Address::Immediate::Integer * p_src,
                                        Tajada::Code::MIPS::Address::Register           * p_dst
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction(),

                                        src(p_src),
                                        dst(p_dst)
                                {}



                                std::string li::show() {
                                        return
                                                "li "
                                                + this->dst->show()
                                                + ", "
                                                + this->src->show()
                                        ;
                                }
                        }
                }
        }
}
