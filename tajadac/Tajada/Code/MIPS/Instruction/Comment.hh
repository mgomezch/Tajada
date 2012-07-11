#ifndef TAJADA_CODE_MIPS_INSTRUCTION_COMMENT_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_COMMENT_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class Comment:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                std::string text;

                                                Comment(
                                                        std::string p_text
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
