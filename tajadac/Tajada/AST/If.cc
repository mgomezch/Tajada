#include <string>

// Class:
#include "Tajada/AST/If.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Block.hh"
#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/For.hh"
#include "Tajada/AST/TypeSelection.hh"
#include "Tajada/AST/While.hh"
#include "Tajada/Code/Block.hh"
#include "Tajada/Code/Intermediate/Instruction/Branch.hh"
#include "Tajada/Code/Intermediate/Instruction/Jump.hh"

namespace Tajada {
        namespace AST {
                If::If(
                        Tajada::AST::Expression * condition ,
                        Tajada::AST::Statement  * body_true ,
                        Tajada::AST::Statement  * body_false
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),

                        condition (condition ),
                        body_true (body_true ),
                        body_false(body_false)
                {}

                std::string If::show(unsigned int depth) {
                        return
                                std::string(u8"if (")
                                + condition->show(depth)
                                + std::string(u8") ")
                                + body_true->show(depth)
                                + (
                                        (
                                                   dynamic_cast<Tajada::AST::Block         *>(body_true)
                                                || dynamic_cast<Tajada::AST::For           *>(body_true)
                                                || dynamic_cast<Tajada::AST::If            *>(body_true)
                                                || dynamic_cast<Tajada::AST::TypeSelection *>(body_true)
                                                || dynamic_cast<Tajada::AST::While         *>(body_true)
                                        )
                                        ? (
                                                body_false
                                                ? u8" "
                                                : u8""
                                        )
                                        : (u8".\n" + (body_false ? std::string(depth * 8, ' ') : u8""))
                                )
                                + (
                                        body_false
                                        ? std::string(u8"else ")
                                        + body_false->show(depth)
                                        + (
                                                (
                                                           dynamic_cast<Tajada::AST::Block         *>(body_false)
                                                        || dynamic_cast<Tajada::AST::For           *>(body_false)
                                                        || dynamic_cast<Tajada::AST::If            *>(body_false)
                                                        || dynamic_cast<Tajada::AST::TypeSelection *>(body_false)
                                                        || dynamic_cast<Tajada::AST::While         *>(body_false)
                                                )
                                                ? u8""
                                                : u8"."
                                        )
                                        : u8""
                                )
                        ;
                }

                void If::gen(
                        Tajada::Code::Block * b
                ) {
                        auto l = std::to_string(Tajada::Code::Block::make_label());

                        auto bt = new Tajada::Code::Block("t_" + l, b->end->scope);
                        auto bf = new Tajada::Code::Block("f_" + l, b->end->scope);
                        auto be = new Tajada::Code::Block("e_" + l, b->end->scope);

                        auto c = this->condition->genr(b);

                        b->end->instructions.push_back(
                                new Tajada::Code::Intermediate::Instruction::Branch(c, bt, bf)
                        );

                        auto x = [b, be](Tajada::Code::Block * bb, Tajada::AST::Statement * s) {
                                b->end->successors.push_back(bb);
                                bb->predecessors.push_back(b->end);
                                if (s) s->gen(bb);
                                bb->end->instructions.push_back(
                                        new Tajada::Code::Intermediate::Instruction::Jump(be)
                                );
                                bb->end->successors.push_back(be);
                                be->predecessors.push_back(bb);
                        };
                        x(bt, this->body_true );
                        x(bf, this->body_false);

                        b->end = be;
                }
        }
}
