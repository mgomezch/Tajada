#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_UNIMPLEMENTED_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_UNIMPLEMENTED_HH

// TODO: remove this file once all Expression classes have their implementation of genl/genr and all Statement classes implement gen

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

//#include "Tajada/AST/AST.hh"
namespace Tajada {
        namespace AST {
                class AST;
        }
}

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Instruction {
                                class Unimplemented:
                                        public virtual Tajada::Code::Intermediate::Instruction::Instruction
                                {
                                        public:
                                                Tajada::AST::AST * unimplemented;

                                                Unimplemented(
                                                        Tajada::AST::AST * p_unimplemented
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
