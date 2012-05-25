#ifndef TAJADA_AST_UNIONACCESSBYINTEGER_HH
#define TAJADA_AST_UNIONACCESSBYINTEGER_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Expression.hh"

#include "Tajada/AST/Literal/Integer.hh"

namespace Tajada {
        namespace AST {
                class UnionAccessByInteger : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * source;
                                Tajada::AST::Literal::Integer * field;

                                UnionAccessByInteger(
                                        Tajada::AST::Expression * source,
                                        Tajada::AST::Literal::Integer * field
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
