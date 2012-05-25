#ifndef TAJADA_AST_ARRAYACCESS_HH
#define TAJADA_AST_ARRAYACCESS_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                class ArrayAccess : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * source;
                                Tajada::AST::Expression * position;

                                ArrayAccess(
                                        Tajada::AST::Expression * source,
                                        Tajada::AST::Expression * position
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
