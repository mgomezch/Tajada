// Class:
#include "Tajada/Code/MIPS/Instruction/syscall.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                syscall::syscall():
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::MIPS::Instruction::Instruction()
                                {}



                                std::string syscall::show() {
                                        return "syscall";
                                }
                        }
                }
        }
}
