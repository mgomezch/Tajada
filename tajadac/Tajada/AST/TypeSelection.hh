#ifndef TAJADA_AST_TYPESELECTION_HH
#define TAJADA_AST_TYPESELECTION_HH

#include <string>
#include <vector>

// Superclasses:
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/TypeCase/TypeCase.hh"

namespace Tajada {
        namespace AST {
                class TypeSelection : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::Expression * fuente;
                                std::string * variable;
                                std::vector<Tajada::AST::TypeCase::TypeCase *> * casos;

                                TypeSelection(
                                        Tajada::AST::Expression * p_fuente,
                                        std::string * p_variable,
                                        std::vector<Tajada::AST::TypeCase::TypeCase *> * p_casos
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
