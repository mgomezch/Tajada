// Class:
#include "Tajada/AST/Statement.hh"

#include "Tajada/Code/Block.hh"
#include "Tajada/Code/Intermediate/Instruction/Unimplemented.hh" // TODO: remove this once all subclasses have their implementation of genl/genr

namespace Tajada {
        namespace AST {
                // TODO: delete this implementation once all subclasses have their own
                void Statement::gen(
                        Tajada::Code::Block * b
                ) {
                        b->end->instructions.push_back(
                                new Tajada::Code::Intermediate::Instruction::Unimplemented(this)
                        );
                }
        }
}
