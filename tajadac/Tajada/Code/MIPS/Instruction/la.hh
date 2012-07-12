#ifndef TAJADA_CODE_MIPS_INSTRUCTION_LA_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_LA_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Immediate/Integer.hh"
#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class la:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::MIPS::Address::Address  * src;
                                                Tajada::Code::MIPS::Address::Register * dst;

                                                la(
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
