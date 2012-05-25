#ifndef TAJADA_AST_VARIABLEUSE_HH
#define TAJADA_AST_VARIABLEUSE_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Expression.hh"

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                class VariableUse : public virtual Tajada::AST::Expression {
                        public:
                                unsigned int scope_id;
                                std::string * name;

                                VariableUse(
                                        unsigned int scope_id,
                                        std::string * name,
                                        Tajada::Type::Type * type
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
