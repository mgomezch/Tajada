#ifndef TAJADA_AST_BUILTINFUNCTION_HH
#define TAJADA_AST_BUILTINFUNCTION_HH

#include <functional>
#include <string>

// Superclasses:
#include "Tajada/AST/Function.hh"

#include "Tajada/AST/Call.hh"
#include "Tajada/AST/FunctionDeclaration.hh"

namespace Tajada {
        namespace AST {
                class BuiltinFunction : public virtual Tajada::AST::Function {
                        public:
                                BuiltinFunction(
                                        Tajada::AST::FunctionDeclaration * p_declaration,
                                        std::function<bool (Tajada::AST::Call *)> p_evaluator = nullptr
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
