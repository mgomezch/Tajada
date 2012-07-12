// Class:
#include "Tajada/Code/Intermediate/Instruction/PrintLine.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/MIPS/Address/Immediate/Integer.hh"
#include "Tajada/Code/MIPS/Address/Label.hh"
#include "Tajada/Code/MIPS/Address/Register.hh"
#include "Tajada/Code/MIPS/Instruction/Comment.hh"
#include "Tajada/Code/MIPS/Instruction/li.hh"
#include "Tajada/Code/MIPS/Instruction/la.hh"
#include "Tajada/Code/MIPS/Instruction/syscall.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                PrintLine::PrintLine(
                                        Tajada::Code::Intermediate::Address::Address * p_src
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::Intermediate::Instruction::Instruction(),

                                        src(p_src)
                                {}



                                std::string PrintLine::show() {
                                        return
                                                u8"printLine "
                                                + this->src->show()
                                        ;
                                }



                                std::vector<Tajada::Code::MIPS::Instruction::Instruction *> PrintLine::to_mips() {
                                        auto msrc = this->src->to_mips();

                                        return
                                                { new Tajada::Code::MIPS::Instruction::Comment(this->show())

                                                , TAJADA_LOAD_TO_REGISTER_MIPS(msrc, a0, Integer)

                                                , new Tajada::Code::MIPS::Instruction::li(
                                                        new Tajada::Code::MIPS::Address::Immediate::Integer(1), // print_int
                                                        new Tajada::Code::MIPS::Address::Register(Tajada::Code::MIPS::Address::Register::R::v0)
                                                )

                                                , new Tajada::Code::MIPS::Instruction::syscall()

                                                , new Tajada::Code::MIPS::Instruction::la(
                                                        new Tajada::Code::MIPS::Address::Label("endl"),
                                                        new Tajada::Code::MIPS::Address::Register(Tajada::Code::MIPS::Address::Register::R::a0)
                                                )

                                                , new Tajada::Code::MIPS::Instruction::li(
                                                        new Tajada::Code::MIPS::Address::Immediate::Integer(4), // print_string
                                                        new Tajada::Code::MIPS::Address::Register(Tajada::Code::MIPS::Address::Register::R::v0)
                                                )

                                                , new Tajada::Code::MIPS::Instruction::syscall()

                                                }
                                        ;
                                }
                        }
                }
        }
}
