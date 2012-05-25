#ifndef TAJADA_AST_CALL_HH
#define TAJADA_AST_CALL_HH

#include <string>

// Superclasses:
#include "Tajada/AST/Expression.hh"

#include "Tajada/AST/Function.hh"
#include "Tajada/Type/Type.hh"


namespace Tajada {
        namespace AST {
                class Function;

                class Call : public virtual Tajada::AST::Expression {
                        public:
                                std::string * name;
                                Tajada::AST::Function ** definition_ptr;
                                Tajada::AST::Expression * argument;

                                Call(
                                        std::string * p_name,
                                        Tajada::AST::Function ** p_definition_ptr,
                                        Tajada::AST::Expression * p_argument,
                                        Tajada::Type::Type * p_return_type
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
