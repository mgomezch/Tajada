#ifndef TAJADA_AST_SEQUENCE_HH
#define TAJADA_AST_SEQUENCE_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                class Sequence : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * first;
                                Tajada::AST::Expression * second;

                                Sequence(
                                        Tajada::AST::Expression * first,
                                        Tajada::AST::Expression * second
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
