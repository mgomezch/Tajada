#ifndef TAJADA_AST_FUNCTIONDEFINITION_HH
#define TAJADA_AST_FUNCTIONDEFINITION_HH

#include <functional>
#include <string>

// Superclasses:
#include "Tajada/AST/Function.hh"

#include "Tajada/AST/Call.hh"
#include "Tajada/AST/FunctionDeclaration.hh"
#include "Tajada/AST/Statement.hh"

namespace Tajada {
        namespace AST {
                class FunctionDefinition : public virtual Tajada::AST::Function {
                        public:
                                Tajada::AST::Statement * body;

                                FunctionDefinition(
                                        Tajada::AST::FunctionDeclaration * p_declaration,
                                        Tajada::AST::Statement * p_body,
                                        std::function<bool (Tajada::AST::Call *)> p_evaluator = nullptr
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
