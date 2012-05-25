#ifndef TAJADA_AST_VARIABLEDEFINITION_HH
#define TAJADA_AST_VARIABLEDEFINITION_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Statement.hh"

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                class VariableDefinition : public virtual Tajada::AST::Statement {
                        public:
                                std::string * name;
                                Tajada::Type::Type * type;

                                VariableDefinition(
                                        std::string * name,
                                        Tajada::Type::Type * type
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
