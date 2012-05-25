#ifndef TAJADA_CODE_INSTRUCTION_HH
#define TAJADA_CODE_INSTRUCTION_HH

#include <string>

namespace Tajada {
        namespace Code {
                class Instruction {
                        public:
                                virtual std::string show() = 0;

                                virtual ~Instruction() = 0;
                };
        }
}

#endif
