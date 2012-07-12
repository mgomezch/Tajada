#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_SUBSTRACT_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_SUBSTRACT_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                class Substract:
                                        public virtual Tajada::Code::Intermediate::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::Intermediate::Address::Address * dst ;
                                                Tajada::Code::Intermediate::Address::Address * lsrc;
                                                Tajada::Code::Intermediate::Address::Address * rsrc;

                                                Substract(
                                                        Tajada::Code::Intermediate::Address::Address * p_dst ,
                                                        Tajada::Code::Intermediate::Address::Address * p_lsrc,
                                                        Tajada::Code::Intermediate::Address::Address * p_rsrc
                                                );

                                                virtual std::string show();

                                                virtual std::vector<Tajada::Code::MIPS::Instruction::Instruction *> to_mips();
                                };
                        }
                }
        }
}

#endif
