#ifndef TAJADA_AST_FUNCTION_HH
#define TAJADA_AST_FUNCTION_HH

#include <functional>
#include <string>

// Superclasses:
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Call.hh"
#include "Tajada/AST/FunctionDeclaration.hh"

namespace Tajada {
        namespace AST {
                class Call;

                class Function : public virtual Tajada::AST::Statement {
                        public:
                                Tajada::AST::FunctionDeclaration * declaration;
                                std::function<bool (Tajada::AST::Call *)> evaluator;

                                Function(
                                        Tajada::AST::FunctionDeclaration * p_declaration,
                                        std::function<bool (Tajada::AST::Call *)> p_evaluator = nullptr
                                );

                                virtual std::string show(unsigned int depth = 0) = 0;
                };
        }
}

#endif
