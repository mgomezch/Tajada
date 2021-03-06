#ifndef TAJADA_CODE_MIPS_INSTRUCTION_LW_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_LW_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Address.hh"
#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class lw:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::MIPS::Address::Address  * src;
                                                Tajada::Code::MIPS::Address::Register * dst;

                                                lw(
                                                        Tajada::Code::MIPS::Address::Address  * p_src,
                                                        Tajada::Code::MIPS::Address::Register * p_dst
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
