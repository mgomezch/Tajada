#ifndef TAJADA_AST_LITERAL_INTEGER_HH
#define TAJADA_AST_LITERAL_INTEGER_HH

#include <string>

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        class Integer : public virtual Tajada::AST::Expression {
                                public:
                                        int value;

                                        Integer(std::string * value);

                                        virtual std::string show(unsigned int depth = 0);
                        };
                }
        }
}

#endif
