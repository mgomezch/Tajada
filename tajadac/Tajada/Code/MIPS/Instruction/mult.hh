#ifndef TAJADA_CODE_MIPS_INSTRUCTION_MULT_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_MULT_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class mult:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::MIPS::Address::Register * lsrc;
                                                Tajada::Code::MIPS::Address::Register * rsrc;

                                                mult(
                                                        Tajada::Code::MIPS::Address::Register * p_lsrc,
                                                        Tajada::Code::MIPS::Address::Register * p_rsrc
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
