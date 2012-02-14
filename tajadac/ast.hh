#ifndef TAJADA_AST_HH
#define TAJADA_AST_HH

#include <string>

#include "types.hh"

namespace Tajada {
        namespace AST {
                class Expression {
                        public:
                                Tajada::types::Type * type;

                                Expression(Tajada::types::Type * type = NULL);
                                virtual ~Expression() = 0;
                };

                class BooleanLiteral : public virtual Expression {
                        public:
                                BooleanLiteral();

                                virtual ~BooleanLiteral();
                };

                class TrueLiteral : public virtual BooleanLiteral {
                        public:
                                TrueLiteral();
                };

                class FalseLiteral : public virtual BooleanLiteral {
                        public:
                                FalseLiteral();
                };
        }
}

#endif
