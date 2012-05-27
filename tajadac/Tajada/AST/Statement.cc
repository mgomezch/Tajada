// Class:
#include "Tajada/AST/Statement.hh"

#include "Tajada/Code/Block.hh"

namespace Tajada {
        namespace AST {
                Tajada::Code::Block * Statement::gen(
                        Tajada::Code::Block * b
                ) {
                        // TODO: delete this implementation once all subclasses have their own
                        return b;
                }
        }
}
