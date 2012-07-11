// Class:
#include "Tajada/Code/MIPS/Instruction/Comment.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                Comment::Comment(
                                        std::string p_text
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction(),

                                        text(p_text)
                                {}



                                std::string Comment::show() {
                                        return
                                                "# "
                                                + this->text
                                        ;
                                }
                        }
                }
        }
}
