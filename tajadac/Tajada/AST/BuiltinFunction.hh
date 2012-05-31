#ifndef TAJADA_AST_BUILTINFUNCTION_HH
#define TAJADA_AST_BUILTINFUNCTION_HH

#include <functional>
#include <string>

// Superclasses:
#include "Tajada/AST/Function.hh"

#include "Tajada/AST/Call.hh"
#include "Tajada/AST/FunctionDeclaration.hh"
#include "Tajada/Builtins.hh"

namespace Tajada {
        namespace AST {
                class BuiltinFunction:
                        public virtual Tajada::AST::Function
                {
                        public:
                                std::string * name;

                                Tajada::Builtins::generator generator;

                                BuiltinFunction(
                                        std::string                               * p_name       ,
                                        Tajada::AST::FunctionDeclaration          * p_declaration,
                                        Tajada::Builtins::generator                 p_generator  ,
                                        std::function<bool (Tajada::AST::Call *)>   p_evaluator
                                );

                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
