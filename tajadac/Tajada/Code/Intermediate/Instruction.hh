#ifndef TAJADA_CODE_INTERMEDIATE_INSTRUCTION_HH
#define TAJADA_CODE_INTERMEDIATE_INSTRUCTION_HH

#include <string>

#include "Tajada/Code/Instruction.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        class Instruction : public virtual Tajada::Code::Instruction {
                                public:
                                        virtual std::string show() = 0;

                                        virtual ~Instruction() = 0;
                        };
                }
        }
}
