#ifndef TAJADA_AST_UNIONACCESSBYINTEGER_HH
#define TAJADA_AST_UNIONACCESSBYINTEGER_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Expression.hh"

#include "Tajada/AST/Literal/Integer.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace AST {
                class UnionAccessByInteger:
                        public virtual Tajada::AST::Expression
                {
                        public:
                                Tajada::AST::Expression       * source;
                                Tajada::AST::Literal::Integer * field ;

                                UnionAccessByInteger(
                                        Tajada::AST::Expression       * p_source,
                                        Tajada::AST::Literal::Integer * p_field
                                );

                                virtual std::string show(unsigned int depth = 0);

                                virtual Tajada::Code::Intermediate::Address::Address * genl(
                                        Tajada::Code::Block * b
                                );

                                virtual Tajada::Code::Intermediate::Address::Address * genr(
                                        Tajada::Code::Block * b
                                );
                };
        }
}

#endif
