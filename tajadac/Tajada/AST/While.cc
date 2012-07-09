#include <string>

// Class:
#include "Tajada/AST/While.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Expression.hh"
#include "Tajada/Code/Block.hh"
#include "Tajada/Code/Intermediate/Instruction/Branch.hh"
#include "Tajada/Code/Intermediate/Instruction/Jump.hh"

namespace Tajada {
        namespace AST {
                While::While(
                        Tajada::AST::Expression * condition,
                        Tajada::AST::Statement  * body
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),

                        condition(condition),
                        body     (body     )
                {}



                std::string While::show(unsigned int depth) {
                        return
                                std::string(u8"while (")
                                + condition->show(depth)
                                + std::string(u8") ")
                                + body->show(depth)
                                + std::string(u8"\n")
                        ;
                }



                void While::gen(
                        Tajada::Code::Block * b
                ) {
                        auto l = std::to_string(Tajada::Code::Block::make_label());

                        auto bc = new Tajada::Code::Block("c_" + l);
                        auto bb = new Tajada::Code::Block("b_" + l);
                        auto be = new Tajada::Code::Block("e_" + l);

                        b->end->instructions.push_back(
                                new Tajada::Code::Intermediate::Instruction::Jump(bc)
                        );
                        b->end->successors.push_back(bc);
                        bc->predecessors.push_back(b->end);

                        auto c = this->condition->genr(bc);
                        bc->end->instructions.push_back(
                                new Tajada::Code::Intermediate::Instruction::Branch(c, bb, be)
                        );
                        bc->end->successors.push_back(bb); bb->predecessors.push_back(bc->end);
                        bc->end->successors.push_back(be); be->predecessors.push_back(bc->end);

                        this->body->gen(bb);
                        bb->end->instructions.push_back(
                                new Tajada::Code::Intermediate::Instruction::Jump(bc)
                        );
                        bb->end->successors.push_back(bc); bc->predecessors.push_back(bb->end);

                        b->end = be;
                }
        }
}
