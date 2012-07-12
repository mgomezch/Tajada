// Class:
#include "Tajada/Code/Intermediate/Instruction/Copy.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/MIPS/Address/Register.hh"
#include "Tajada/Code/MIPS/Instruction/Comment.hh"
#include "Tajada/Code/MIPS/Instruction/sw.hh"

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
                                                this->dst->show()
                                                + " ≔ "
                                                + this->src->show()
                                        ;
                                }



                                std::vector<Tajada::Code::MIPS::Instruction::Instruction *> Copy::to_mips() {
                                        auto msrc = this->src->to_mips();
                                        auto mdst = this->dst->to_mips();

                                        return
                                                { new Tajada::Code::MIPS::Instruction::Comment(this->show())

                                                , TAJADA_LOAD_TO_REGISTER_MIPS(msrc, t0, Integer)

                                                , new Tajada::Code::MIPS::Instruction::sw(
                                                        new Tajada::Code::MIPS::Address::Register(Tajada::Code::MIPS::Address::Register::R::t0),
                                                        dynamic_cast<Tajada::Code::MIPS::Address::Register *>(mdst)
                                                )

                                                }
                                        ;
                                }
                        }
                }
        }
}
