#ifndef TAJADA_AST_LITERAL_FLOAT_HH
#define TAJADA_AST_LITERAL_FLOAT_HH

#include <string>

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        class Float : public virtual Tajada::AST::Expression {
                                public:
                                        float value;

                                        Float(std::string * integer, std::string * fractional);

                                        virtual std::string show(unsigned int depth = 0);
                        };
                }
        }
}

#endif
