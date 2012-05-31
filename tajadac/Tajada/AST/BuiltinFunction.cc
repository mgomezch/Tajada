#include <functional>
#include <string>

// Class:
#include "Tajada/AST/BuiltinFunction.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Statement.hh"
#include "Tajada/AST/Function.hh"

#include "Tajada/AST/Call.hh"
#include "Tajada/AST/FunctionDeclaration.hh"
#include "Tajada/Builtins.hh"

namespace Tajada {
        namespace AST {
                BuiltinFunction::BuiltinFunction(
                        std::string                               * p_name       ,
                        Tajada::AST::FunctionDeclaration          * p_declaration,
                        Tajada::Builtins::generator                 p_generator  ,
                        std::function<bool (Tajada::AST::Call *)>   p_evaluator
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),
                        Tajada::AST::Function(
                                p_declaration,
                                p_evaluator
                        ),

                        name     (p_name     ),
                        generator(p_generator)
                {}

                std::string BuiltinFunction::show(unsigned int depth) {
                        return
                                Function::show(depth)
                                + u8" cableado "
                                + *this->name
                                + (
                                        this->evaluator != nullptr
                                        ? u8"(constexpr)"
                                        : ""
                                )
                        ;
                }
        }
}
