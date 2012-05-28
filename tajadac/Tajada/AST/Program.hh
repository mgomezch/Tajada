#ifndef TAJADA_AST_PROGRAM_HH
#define TAJADA_AST_PROGRAM_HH

#include <list>
#include <string>

// Superclasses:
#include "Tajada/AST/AST.hh"

#include "Tajada/AST/Block.hh"
#include "Tajada/AST/Statement.hh"
#include "Tajada/Code/Block.hh"

namespace Tajada {
        namespace AST {
                class Program : public virtual Tajada::AST::AST {
                        public:
                                std::list<Tajada::AST::Statement *> * statements;
                                Tajada::AST::Block * main;

                                Program(
                                        std::list<Tajada::AST::Statement *> * statements,
                                        Tajada::AST::Block * main
                                );

                                virtual std::string show(unsigned int depth = 0);

                                virtual Tajada::Code::Block * gen();
                };
        }
}

#endif
