#ifndef TAJADA_CODE_MIPS_INSTRUCTION_SLT_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_SLT_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class slt:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::MIPS::Address::Register * lsrc;
                                                Tajada::Code::MIPS::Address::Register * rsrc;
                                                Tajada::Code::MIPS::Address::Register * dst ;

                                                slt(
                                                        Tajada::Code::MIPS::Address::Register * p_lsrc,
                                                        Tajada::Code::MIPS::Address::Register * p_rsrc,
                                                        Tajada::Code::MIPS::Address::Register * p_dst
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
