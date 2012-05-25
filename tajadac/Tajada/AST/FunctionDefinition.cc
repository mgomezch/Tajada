#include <functional>
#include <string>

#include "Tajada/AST/FunctionDefinition.hh"

#include "Tajada/AST/Call.hh"
#include "Tajada/AST/FunctionDeclaration.hh"
#include "Tajada/AST/Function.hh"
#include "Tajada/AST/Statement.hh"

namespace Tajada {
        namespace AST {
                FunctionDefinition::FunctionDefinition(
                        Tajada::AST::FunctionDeclaration * p_declaration,
                        Tajada::AST::Statement * p_body,
                        std::function<bool (Tajada::AST::Call *)> p_evaluator
                ):
                        Tajada::AST::Function(p_declaration, p_evaluator),
                        body(p_body)
                {}

                std::string FunctionDefinition::show(unsigned int depth) {
                        return
                                Function::show(depth)
                                + u8" "
                                + body->show(depth)
                                + u8"\n";
                }
        }
}
