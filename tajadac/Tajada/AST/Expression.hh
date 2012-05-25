#ifndef TAJADA_AST_EXPRESSION_HH
#define TAJADA_AST_EXPRESSION_HH

#include <string>

// Superclasses:
#include "Tajada/AST/AST.hh"

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                class Expression : public virtual Tajada::AST::AST {
                        public:
                                Tajada::Type::Type * type;
                                bool is_lvalue;

                                Expression(
                                        Tajada::Type::Type * type,
                                        bool is_lvalue
                                );
                };
        }
}

#endif
