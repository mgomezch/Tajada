#ifndef TAJADA_CODE_MIPS_INSTRUCTION_UNIMPLEMENTED_HH
#define TAJADA_CODE_MIPS_INSTRUCTION_UNIMPLEMENTED_HH

#include <string>

// Superclasses:
#include "Tajada/Code/MIPS/Instruction/Instruction.hh"

#include "Tajada/Code/Intermediate/Instruction/Instruction.hh"

// TODO: remove this whole class once every intermediate instruction gets translated
namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Instruction {
                                class Unimplemented:
                                        public virtual Tajada::Code::MIPS::Instruction::Instruction
                                {
                                        public:
                                                Tajada::Code::Intermediate::Instruction::Instruction * untranslated;

                                                Unimplemented(
                                                        Tajada::Code::Intermediate::Instruction::Instruction * p_untranslated
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
