#ifndef TAJADA_AST_EXPRESSIONSTATEMENT_HH
#define TAJADA_AST_EXPRESSIONSTATEMENT_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                class ExpressionStatement : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Expression * expression;

                                ExpressionStatement(
                                        Tajada::AST::Expression * expression
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
