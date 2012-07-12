#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_PRINTLINE_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_PRINTLINE_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                class PrintLine:
                                        public virtual Tajada::Code::Intermediate::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::Intermediate::Address::Address * src;

                                                PrintLine(
                                                        Tajada::Code::Intermediate::Address::Address * p_src
                                                );

                                                virtual std::string show();

                                                virtual std::vector<Tajada::Code::MIPS::Instruction::Instruction *> to_mips();
                                };
                        }
                }
        }
}

#endif
