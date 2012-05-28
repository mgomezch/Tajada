// Class:
#include "Tajada/AST/Statement.hh"

#include "Tajada/Code/Block.hh"

namespace Tajada {
        namespace AST {
                // TODO: delete this implementation once all subclasses have their own
                void Statement::gen(
                        Tajada::Code::Block * b
                ) {
                        TAJADA_UNUSED_PARAMETER(b);
                }
        }
}
