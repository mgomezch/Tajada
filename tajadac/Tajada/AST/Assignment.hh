#ifndef TAJADA_AST_ASSIGNMENT_HH
#define TAJADA_AST_ASSIGNMENT_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                class Assignment:
                        public virtual Tajada::AST::Statement
                {
                        public:
                                Tajada::AST::Expression * lhs;
                                Tajada::AST::Expression * rhs;

                                Assignment(
                                        Tajada::AST::Expression * lhs,
                                        Tajada::AST::Expression * rhs
                                );

                                virtual std::string show(unsigned int depth = 0);

                                virtual void gen(
                                        Tajada::Code::Block * b
                                );
                };
        }
}

#endif
