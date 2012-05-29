// Class:
#include "Tajada/Code/Intermediate/Instruction/Copy.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                Copy::Copy(
                                        Tajada::Code::Intermediate::Address::Address * p_dst,
                                        Tajada::Code::Intermediate::Address::Address * p_src
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::Intermediate::Instruction::Instruction(),

                                        dst(p_dst),
                                        src(p_src)
                                {}

                                std::string Copy::show() {
                                        return
                                                "copy "
                                                + this->dst->show()
                                                + " ← "
                                                + this->src->show()
                                        ;
                                }
                        }
                }
        }
}
