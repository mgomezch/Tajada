#ifndef TAJADA_CODE_MIPS_INSTRUCTION_MFLO_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_MFLO_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class mflo:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::MIPS::Address::Register * dst;

                                                mflo(
                                                        Tajada::Code::MIPS::Address::Register * p_dst
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
