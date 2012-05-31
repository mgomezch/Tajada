#include <functional>
#include <string>

// Class:
#include "Tajada/AST/Function.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Call.hh"
#include "Tajada/AST/FunctionDeclaration.hh"

namespace Tajada {
        namespace AST {
                Function::Function(
                        Tajada::AST::FunctionDeclaration * p_declaration,
                        std::function<bool (Tajada::AST::Call *)> p_evaluator
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),

                        declaration(p_declaration),
                        evaluator  (p_evaluator  )
                {}

                std::string Function::show(unsigned int depth) {
                        return declaration->show(depth);
                }
        }
}
