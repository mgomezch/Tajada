#ifndef TAJADA_AST_FUNCTIONDECLARATION_HH
#define TAJADA_AST_FUNCTIONDECLARATION_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/FunctionID.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                class FunctionDeclaration:
                        public virtual Tajada::AST::Statement
                {
                        public:
                                Tajada::AST::FunctionID * id         ;
                                std::string             * domain_name;
                                Tajada::Type::Type      * domain     ;
                                Tajada::Type::Type      * codomain   ;

                                FunctionDeclaration(
                                        Tajada::AST::FunctionID * p_id         ,
                                        std::string             * p_domain_name,
                                        Tajada::Type::Type      * p_domain     ,
                                        Tajada::Type::Type      * p_codomain
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
