#ifndef TAJADA_CODE_MIPS_BLOCK_HH
#define TAJADA_CODE_MIPS_BLOCK_HH

#include <string>
#include <vector>

#include "Tajada/Code/Instruction.hh"

// Superclasses:
#include "Tajada/Code/Block.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        class Block : public virtual Tajada::Code::Block {
                                public:
                                        Block(
                                                std::string     p_label    ,
                                                Tajada::Scope * p_scope    ,
                                                unsigned int    p_index = 0
                                        );

                                        virtual std::string show();
                        };

                        Tajada::Code::MIPS::Block * make_block(
                                std::string     p_label    ,
                                Tajada::Scope * p_scope    ,
                                unsigned int    p_index = 0
                        );
                }
        }
}

#endif
