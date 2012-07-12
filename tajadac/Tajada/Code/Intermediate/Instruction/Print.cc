// Class:
#include "Tajada/Code/Intermediate/Instruction/Print.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                Print::Print(
                                        Tajada::Code::Intermediate::Address::Address * p_src
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::Intermediate::Instruction::Instruction(),

                                        src(p_src)
                                {}

                                std::string Print::show() {
                                        return
                                                u8"print "
                                                + this->src->show()
                                        ;
                                }
                        }
                }
        }
}
