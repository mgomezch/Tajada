#ifndef TAJADA_AST_LITERAL_CHARACTER_HH
#define TAJADA_AST_LITERAL_CHARACTER_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Expression.hh"

#include "Tajada/Code/Intermediate/Address/Address.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        class Character:
                                public virtual Tajada::AST::Expression
                        {
                                public:
                                        std::string * value;

                                        Character(
                                                std::string * value
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
