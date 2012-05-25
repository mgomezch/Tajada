#ifndef TAJADA_AST_LITERAL_STRING_HH
#define TAJADA_AST_LITERAL_STRING_HH

#include <string>

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        class String : public virtual Tajada::AST::Expression {
                                public:
                                        std::string * value;

                                        String(std::string * value);

                                        virtual std::string show(unsigned int depth = 0);
                        };
                }
        }
}

#endif
