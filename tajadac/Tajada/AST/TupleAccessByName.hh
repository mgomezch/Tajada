#ifndef TAJADA_AST_TUPLEACCESSBYNAME_HH
#define TAJADA_AST_TUPLEACCESSBYNAME_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Expression.hh"

namespace Tajada {
        namespace AST {
                class TupleAccessByName : public virtual Tajada::AST::Expression {
                        public:
                                Tajada::AST::Expression * source;
                                std::string * field;

                                TupleAccessByName(
                                        Tajada::AST::Expression * source,
                                        std::string * field
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
