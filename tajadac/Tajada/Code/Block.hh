#ifndef TAJADA_CODE_BLOCK_HH
#define TAJADA_CODE_BLOCK_HH

#include <deque>
#include <string>
#include <vector>

#include "Tajada/Code/Instruction.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        class Block;
                }
        }
        class Scope;
}

namespace Tajada {
        namespace Code {
                class Block {
                        protected:
                                std::string     label;
                        public:
                                Tajada::Scope * scope;
                                unsigned int    index;

                                std::deque<Tajada::Code::Instruction *> instructions;

                                std::vector<Tajada::Code::Block *> successors  ;
                                std::vector<Tajada::Code::Block *> predecessors;

                                Tajada::Code::Block * end;


                                Block(
                                        std::string     p_label    ,
                                        Tajada::Scope * p_scope    ,
                                        unsigned int    p_index = 0
                                );

                                virtual ~Block();

                                virtual std::string getLabel();

                                virtual std::string rawLabel();

                                virtual std::string show();

                                virtual std::string show_all();

                                virtual Tajada::Code::MIPS::Block * to_mips(
                                        Tajada::Code::Block * root
                                );

                                virtual std::string to_mips_all();

                                static unsigned long int make_label();

                        private:
                                static unsigned long int next_label;
                };
        }
}

#endif
