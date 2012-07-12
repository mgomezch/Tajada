// Class:
#include "Tajada/Code/Intermediate/Instruction/ReadI.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Location.hh"
#include "Tajada/Code/MIPS/Address/Immediate/Integer.hh"
#include "Tajada/Code/MIPS/Address/Register.hh"
#include "Tajada/Code/MIPS/Instruction/Comment.hh"
#include "Tajada/Code/MIPS/Instruction/li.hh"
#include "Tajada/Code/MIPS/Instruction/sw.hh"
#include "Tajada/Code/MIPS/Instruction/syscall.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                ReadI::ReadI(
                                        Tajada::Code::Intermediate::Address::Location * p_dst
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::Intermediate::Instruction::Instruction(),

                                        dst(p_dst)
                                {}



                                std::string ReadI::show() {
                                        return
                                                u8"read[I] "
                                                + this->dst->show()
                                        ;
                                }



                                std::vector<Tajada::Code::MIPS::Instruction::Instruction *> ReadI::to_mips() {
                                        auto mdst = this->dst->to_mips();

                                        return
                                                { new Tajada::Code::MIPS::Instruction::Comment(this->show())

                                                , new Tajada::Code::MIPS::Instruction::li(
                                                        new Tajada::Code::MIPS::Address::Immediate::Integer(5), // read_int
                                                        new Tajada::Code::MIPS::Address::Register(Tajada::Code::MIPS::Address::Register::R::v0)
                                                )

                                                , new Tajada::Code::MIPS::Instruction::syscall()

                                                , new Tajada::Code::MIPS::Instruction::sw(
                                                        new Tajada::Code::MIPS::Address::Register(Tajada::Code::MIPS::Address::Register::R::v0),
                                                        dynamic_cast<Tajada::Code::MIPS::Address::Register *>(mdst)
                                                )

                                                }
                                        ;
                                }
                        }
                }
        }
}
