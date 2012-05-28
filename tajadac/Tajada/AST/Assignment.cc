#include <string>

// Class:
#include "Tajada/AST/Assignment.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Expression.hh"
#include "Tajada/Code/Block.hh"
#include "Tajada/Code/Intermediate/Instruction/Copy.hh"

namespace Tajada {
        namespace AST {
                Assignment::Assignment(
                        Tajada::AST::Expression * lhs,
                        Tajada::AST::Expression * rhs
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),

                        lhs(lhs),
                        rhs(rhs)
                {}



                std::string Assignment::show(unsigned int depth) {
                        return
                                lhs->show(depth)
                                + std::string(u8" ≔ ")
                                + rhs->show(depth)
                        ;
                }



                void Assignment::gen(
                        Tajada::Code::Block * b
                ) {
                        auto lv = this->lhs->genl(b);
                        auto rv = this->rhs->genr(b);

                        b->end->instructions.push_back(
                                new Tajada::Code::Intermediate::Instruction::Copy(lv, rv)
                        );
                }
        }
}
