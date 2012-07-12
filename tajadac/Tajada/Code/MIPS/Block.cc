#include <numeric>
#include <string>

// Class:
#include "Tajada/Code/MIPS/Block.hh"

// Superclasses:
#include "Tajada/Code/Block.hh"

#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"
#include "Tajada/Code/MIPS/MIPS.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        Block::Block(
                                std::string     p_label,
                                Tajada::Scope * p_scope,
                                unsigned int    p_index
                        ):
                                Tajada::Code::Block(p_label, p_scope, p_index)
                        {}



                        std::string Block::show() {
                                return
                                        this->getLabel() + u8":\n"
                                        + std::accumulate(
                                                this->instructions.begin(),
                                                this->instructions.end(),
                                                std::string(),
                                                [](std::string acc, Tajada::Code::Instruction * i) {
                                                        return
                                                                acc
                                                                + u8"        "
                                                                + i->show()
                                                                + u8"\n"
                                                        ;
                                                }
                                        )
                                ;
                        }
                }
        }
}
