#include <string>

#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/Statement.hh"
#include "Tajada/AST/While.hh"

namespace Tajada {
        namespace AST {
                While::While(
                        Tajada::AST::Expression * condition,
                        Tajada::AST::Statement * body
                ):
                        condition(condition),
                        body(body)
                {}

                std::string While::show(unsigned int depth) {
                        return
                                std::string(u8"while (")
                                + condition->show(depth)
                                + std::string(u8") ")
                                + body->show(depth)
                                + std::string(u8"\n");
                }
        }
}
