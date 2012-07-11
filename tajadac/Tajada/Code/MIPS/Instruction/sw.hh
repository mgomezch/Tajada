#ifndef TAJADA_CODE_MIPS_INSTRUCTION_SW_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_SW_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Address.hh"
#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class sw:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::MIPS::Address::Register * src;
                                                Tajada::Code::MIPS::Address::Address  * dst;

                                                sw(
                                                        Tajada::Code::MIPS::Address::Register * p_src,
                                                        Tajada::Code::MIPS::Address::Address  * p_dst
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
