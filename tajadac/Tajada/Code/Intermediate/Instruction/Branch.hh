#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_BRANCH_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_BRANCH_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Address.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                class Branch:
                                        public virtual Tajada::Code::Intermediate::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::Intermediate::Address::Address * condition  ;
                                                Tajada::Code::Block                          * block_true ;
                                                Tajada::Code::Block                          * block_false;

                                                Branch(
                                                        Tajada::Code::Intermediate::Address::Address * p_condition  ,
                                                        Tajada::Code::Block                          * p_block_true ,
                                                        Tajada::Code::Block                          * p_block_false
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
