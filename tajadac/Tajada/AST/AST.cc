// Class:
#include "Tajada/AST/AST.hh"

#include "Tajada/Code/Block.hh"

namespace Tajada {
        namespace AST {
                AST::~AST() {}

                Tajada::Code::Block * AST::gen() {
                        return new Tajada::Code::Block;
                }
        }
}
