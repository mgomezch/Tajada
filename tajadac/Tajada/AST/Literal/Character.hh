#ifndef TAJADA_AST_LITERAL_CHARACTER_HH
#define TAJADA_AST_LITERAL_CHARACTER_HH

#include <string>

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        class Character : public virtual Tajada::AST::Expression {
                                public:
                                        std::string * value;

                                        Character(std::string * value);

                                        virtual std::string show(unsigned int depth = 0);
                        };
                }
        }
}

#endif
