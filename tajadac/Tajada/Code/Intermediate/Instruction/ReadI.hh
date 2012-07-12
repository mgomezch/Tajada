#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_READI_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_READI_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Location.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                class ReadI:
                                        public virtual Tajada::Code::Intermediate::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::Intermediate::Address::Location * dst;

                                                ReadI(
                                                        Tajada::Code::Intermediate::Address::Location * p_dst
                                                );

                                                virtual std::string show();

                                                virtual std::vector<Tajada::Code::MIPS::Instruction::Instruction *> to_mips();
                                };
                        }
                }
        }
}

#endif
