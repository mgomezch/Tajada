#ifndef TAJADA_AST_WHILE_HH
#define TAJADA_AST_WHILE_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                class While : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Expression * condition;
                                Tajada::AST::Statement * body;

                                While(
                                        Tajada::AST::Expression * condition,
                                        Tajada::AST::Statement * body
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
