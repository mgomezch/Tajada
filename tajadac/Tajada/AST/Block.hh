#ifndef TAJADA_AST_BLOCK_HH
#define TAJADA_AST_BLOCK_HH

#include <list>
#include <string>

// Superclasses:
#include "Tajada/AST/Statement.hh"

#include "Tajada/Code/Block.hh"
#include "scope.hh"

namespace Tajada {
        namespace AST {
                class Block:
                        public virtual Tajada::AST::Statement
                {
                        public:
                                std::list<Tajada::AST::Statement *> * statements;
                                Tajada::Scope                       * scope     ;

                                Block(
                                        std::list<Tajada::AST::Statement *> * p_statements,
                                        Tajada::Scope                       * p_scope
                                );

                                virtual std::string show(unsigned int depth = 0);

                                virtual void gen(
                                        Tajada::Code::Block * b
                                );
                };
        }
}

#endif
