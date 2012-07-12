// Class:
#include "Tajada/Code/Intermediate/Instruction/Add.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/MIPS/Instruction/Comment.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"
#include "Tajada/Code/MIPS/Instruction/add.hh"
#include "Tajada/Code/MIPS/Instruction/sw.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                Add::Add(
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



                                std::string Add::show() {
                                        return
                                                this->dst->show()
                                                + u8" ≔ "
                                                + this->lsrc->show()
                                                + u8" + "
                                                + this->rsrc->show()
                                        ;
                                }



                                std::vector<Tajada::Code::MIPS::Instruction::Instruction *> Add::to_mips() {
                                        auto mlsrc = this->lsrc->to_mips();
                                        auto mrsrc = this->rsrc->to_mips();
                                        auto mdst  = this->dst ->to_mips();

                                        return
                                                { new Tajada::Code::MIPS::Instruction::Comment(this->show())

                                                , TAJADA_LOAD_TO_REGISTER_MIPS(mlsrc, t1, Integer)
                                                , TAJADA_LOAD_TO_REGISTER_MIPS(mrsrc, t2, Integer)

                                                , new Tajada::Code::MIPS::Instruction::add(
                                                        new Tajada::Code::MIPS::Address::Register(Tajada::Code::MIPS::Address::Register::R::t1),
                                                        new Tajada::Code::MIPS::Address::Register(Tajada::Code::MIPS::Address::Register::R::t2),
                                                        new Tajada::Code::MIPS::Address::Register(Tajada::Code::MIPS::Address::Register::R::t0)
                                                )

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
