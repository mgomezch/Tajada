#ifndef TAJADA_CODE_BLOCK_HH
#define TAJADA_CODE_BLOCK_HH

#include <string>
#include <vector>

#include "Tajada/Code/Instruction.hh"

namespace Tajada {
        namespace Code {
                class Block {
                        public:
                                std::string label;

                                std::vector<Tajada::Code::Instruction *> instructions;
                                std::vector<Tajada::Code::Block       *> successors  ;

                                Block(
                                        std::string p_label
                                );

                                std::string show();
                };
        }
}

#endif
