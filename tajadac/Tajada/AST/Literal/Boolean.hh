#ifndef TAJADA_AST_LITERAL_BOOLEAN_HH
#define TAJADA_AST_LITERAL_BOOLEAN_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Expression.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        class Boolean:
                                public virtual Tajada::AST::Expression
                        {
                                public:
                                        bool value;

                                        Boolean(
                                                bool p_value
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
}

#endif
