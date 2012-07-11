// TODO: remove this file once all Expression classes have their implementation of genl/genr and all Statement classes implement gen

// Class:
#include "Tajada/Code/Intermediate/Instruction/Unimplemented.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/AST/AST.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                Unimplemented::Unimplemented(
                                        Tajada::AST::AST * p_unimplemented
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::Intermediate::Instruction::Instruction(),

                                        unimplemented(p_unimplemented)
                                {}

                                std::string Unimplemented::show() {
                                        return
                                                u8"‹UNIMPLEMENTED INSTRUCTION: "
                                                + unimplemented->show()
                                                + u8"›"
                                        ;
                                }
                        }
                }
        }
}
