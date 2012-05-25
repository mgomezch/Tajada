#ifndef TAJADA_AST_BLOCK_HH
#define TAJADA_AST_BLOCK_HH

#include <list>
#include <string>

// Superclasses:
#include "Tajada/AST/Statement.hh"

namespace Tajada {
        namespace AST {
                class Block : public virtual Tajada::AST::Statement {
                        public:
                                std::list<Tajada::AST::Statement *> * statements;

                                Block(
                                        std::list<Tajada::AST::Statement *> * statements
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
