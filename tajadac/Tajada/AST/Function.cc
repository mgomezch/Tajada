#include <functional>
#include <string>

#include "Tajada/AST/Call.hh"
#include "Tajada/AST/FunctionDeclaration.hh"
#include "Tajada/AST/Function.hh"

namespace Tajada {
        namespace AST {
                Function::Function(
                        Tajada::AST::FunctionDeclaration * p_declaration,
                        std::function<bool (Tajada::AST::Call *)> p_evaluator
                ):
                        declaration(p_declaration),
                        evaluator  (p_evaluator  )
                {}

                std::string Function::show(unsigned int depth) {
                        return declaration->show(depth);
                }
        }
}
