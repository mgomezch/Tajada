#include <functional>
#include <string>

#include "Tajada/AST/BuiltinFunction.hh"
#include "Tajada/AST/Call.hh"
#include "Tajada/AST/FunctionDeclaration.hh"
#include "Tajada/AST/Function.hh"

namespace Tajada {
        namespace AST {
                BuiltinFunction::BuiltinFunction(
                        Tajada::AST::FunctionDeclaration * p_declaration,
                        std::function<bool (Tajada::AST::Call *)> p_evaluator
                ):
                        Tajada::AST::Function(p_declaration, p_evaluator)
                {}

                std::string BuiltinFunction::show(unsigned int depth) {
                        return
                                Function::show(depth)
                                + u8" (builtin"
                                + (evaluator != nullptr ? u8", constexpr" : "")
                                + u8")";
                }
        }
}
