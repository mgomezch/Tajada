#ifndef TAJADA_AST_UNIONACCESSBYNAME_HH
#define TAJADA_AST_UNIONACCESSBYNAME_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Expression.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace AST {
                class UnionAccessByName:
                        public virtual Tajada::AST::Expression
                {
                        public:
                                Tajada::AST::Expression * source;
                                std::string             * field ;

                                UnionAccessByName(
                                        Tajada::AST::Expression * p_source,
                                        std::string             * p_field
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
