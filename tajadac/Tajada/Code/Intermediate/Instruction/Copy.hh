#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_COPY_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_COPY_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Location.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                class Copy:
                                        public virtual Tajada::Code::Intermediate::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::Intermediate::Location::Location * src;
                                                Tajada::Code::Intermediate::Location::Location * dst;

                                                Copy(
                                                        Tajada::Code::Intermediate::Location::Location * p_src,
                                                        Tajada::Code::Intermediate::Location::Location * p_dst
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
