#ifndef TAJADA_AST_LITERAL_BOOLEAN_HH
#define TAJADA_AST_LITERAL_BOOLEAN_HH

#include <string>

#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                namespace Literal {
                        class Boolean : public virtual Tajada::AST::Expression {
                                public:
                                        bool value;

                                        Boolean(
                                                bool p_value
                                        );

                                        virtual std::string show(unsigned int depth = 0);
                        };
                }
        }
}

#endif
