#ifndef TAJADA_CODE_MIPS_INSTRUCTION_MOVE_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_MOVE_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class move:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::MIPS::Address::Register * src;
                                                Tajada::Code::MIPS::Address::Register * dst;

                                                move(
                                                        Tajada::Code::MIPS::Address::Register * p_src,
                                                        Tajada::Code::MIPS::Address::Register * p_dst
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
