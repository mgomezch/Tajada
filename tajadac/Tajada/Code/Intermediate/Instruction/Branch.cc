// Class:
#include "Tajada/Code/Intermediate/Instruction/Branch.hh"

// Superclasses:
#include "Tajada/Code/Instruction.hh"
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"

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
                                                + this->block_true->label
                                                + " else goto "
                                                + this->block_false->label
                                        ;
                                }
                        }
                }
        }
}
