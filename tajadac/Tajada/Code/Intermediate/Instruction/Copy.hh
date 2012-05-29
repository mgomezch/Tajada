#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_COPY_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_COPY_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                class Copy:
                                        public virtual Tajada::Code::Intermediate::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::Intermediate::Address::Address * dst;
                                                Tajada::Code::Intermediate::Address::Address * src;

                                                Copy(
                                                        Tajada::Code::Intermediate::Address::Address * p_dst,
                                                        Tajada::Code::Intermediate::Address::Address * p_src
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
