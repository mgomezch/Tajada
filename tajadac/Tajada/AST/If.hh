#ifndef TAJADA_AST_IF_HH
#define TAJADA_AST_IF_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                class If : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Expression * condition;
                                Tajada::AST::Statement * body_true;
                                Tajada::AST::Statement * body_false;

                                If(
                                        Tajada::AST::Expression * condition,
                                        Tajada::AST::Statement * body_true,
                                        Tajada::AST::Statement * body_false
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
