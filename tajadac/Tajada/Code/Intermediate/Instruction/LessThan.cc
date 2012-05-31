// Class:
#include "Tajada/Code/Intermediate/Instruction/LessThan.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                LessThan::LessThan(
                                        Tajada::Code::Intermediate::Address::Address * p_dst ,
                                        Tajada::Code::Intermediate::Address::Address * p_lsrc,
                                        Tajada::Code::Intermediate::Address::Address * p_rsrc
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::Intermediate::Instruction::Instruction(),

                                        dst (p_dst ),
                                        lsrc(p_lsrc),
                                        rsrc(p_rsrc)
                                {}

                                std::string LessThan::show() {
                                        return
                                                this->dst->show()
                                                + u8" ≔ "
                                                + this->lsrc->show()
                                                + u8" < "
                                                + this->rsrc->show()
                                        ;
                                }
                        }
                }
        }
}
