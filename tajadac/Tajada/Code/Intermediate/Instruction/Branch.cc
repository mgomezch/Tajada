// Class:
#include "Tajada/Code/Intermediate/Instruction/Branch.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Block.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/MIPS/Address/Immediate/Integer.hh"
#include "Tajada/Code/MIPS/Address/Register.hh"
#include "Tajada/Code/MIPS/Instruction/Comment.hh"
#include "Tajada/Code/MIPS/Instruction/bnez.hh"
#include "Tajada/Code/MIPS/Instruction/j.hh"
#include "Tajada/Code/MIPS/Instruction/li.hh"
#include "Tajada/Code/MIPS/Instruction/lw.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                Branch::Branch(
                                        Tajada::Code::Intermediate::Address::Address * p_condition  ,
                                        Tajada::Code::Block                          * p_block_true ,
                                        Tajada::Code::Block                          * p_block_false
                                ):
                                        Tajada::Code::Instruction(),
                                        Tajada::Code::Intermediate::Instruction::Instruction(),

                                        condition  (p_condition  ),
                                        block_true (p_block_true ),
                                        block_false(p_block_false)
                                {}



                                std::string Branch::show() {
                                        return
                                                "if ("
                                                + this->condition->show()
                                                + ") goto "
                                                + this->block_true->getLabel()
                                                + " else goto "
                                                + this->block_false->getLabel()
                                        ;
                                }




                                std::vector<Tajada::Code::MIPS::Instruction::Instruction *> Branch::to_mips() {
                                        auto c = this->condition->to_mips();
                                        auto i = dynamic_cast<Tajada::Code::MIPS::Address::Immediate::Integer  *>(c);
                                        auto r = dynamic_cast<Tajada::Code::MIPS::Address::Register            *>(c);
                                        return
                                                { new Tajada::Code::MIPS::Instruction::Comment(this->show())

                                                , i
                                                ? static_cast<Tajada::Code::MIPS::Instruction::Instruction *>(
                                                        new Tajada::Code::MIPS::Instruction::li(
                                                                i,
                                                                new Tajada::Code::MIPS::Address::Register(
                                                                        Tajada::Code::MIPS::Address::Register::R::t1
                                                                )
                                                        )
                                                )
                                                : static_cast<Tajada::Code::MIPS::Instruction::Instruction *>(
                                                        new Tajada::Code::MIPS::Instruction::lw(
                                                                r,
                                                                new Tajada::Code::MIPS::Address::Register(
                                                                        Tajada::Code::MIPS::Address::Register::R::t1
                                                                )
                                                        )
                                                )

                                                , new Tajada::Code::MIPS::Instruction::bnez(
                                                        new Tajada::Code::MIPS::Address::Register(
                                                                Tajada::Code::MIPS::Address::Register::R::t1
                                                        ),
                                                        this->block_true->getLabel() + "_mips"
                                                )

                                                , new Tajada::Code::MIPS::Instruction::j(this->block_false->getLabel() + "_mips")
                                                }
                                        ;
                                }
                        }
                }
        }
}
