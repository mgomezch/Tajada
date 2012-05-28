// Class:
#include "Tajada/Code/Intermediate/Instruction/Copy.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Location/Location.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                Copy::Copy(
                                        Tajada::Code::Intermediate::Location::Location * p_src,
                                        Tajada::Code::Intermediate::Location::Location * p_dst
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::Intermediate::Instruction::Instruction(),

                                        src(p_src),
                                        dst(p_dst)
                                {}

                                std::string Copy::show() {
                                        return
                                                "copy "
                                                + this->src->show()
                                                + " → "
                                                + this->dst->show()
                                        ;
                                }
                        }
                }
        }
}
