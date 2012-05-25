#include <string>

#include "Tajada/AST/Break.hh"

namespace Tajada {
        namespace AST {
                Break::Break(
                        Tajada::AST::Statement * p_statement
                ):
                        statement(p_statement)
                {}

                std::string Break::show(unsigned int depth) {
                        TAJADA_UNUSED_PARAMETER(depth);
                        return
                                u8"break";
                }
        }
}
