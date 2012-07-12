#include <algorithm>
#include <list>
#include <numeric>
#include <string>

// Class:
#include "Tajada/AST/Block.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/For.hh"
#include "Tajada/AST/If.hh"
#include "Tajada/AST/TypeSelection.hh"
#include "Tajada/AST/While.hh"
#include "Tajada/Code/Block.hh"
#include "Tajada/Code/Intermediate/Instruction/Jump.hh"
#include "scope.hh"

namespace Tajada {
        namespace AST {
                Block::Block(
                        std::list<Tajada::AST::Statement *> * p_statements,
                        Tajada::Scope                       * p_scope
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),

                        statements(p_statements),
                        scope     (p_scope     )
                {}



                std::string Block::show(unsigned int depth) {
                        return
                                std::string(u8"{\n")
                                + std::accumulate(
                                        this->statements->begin(),
                                        this->statements->end(),
                                        std::string(),
                                        [depth](std::string acc, Tajada::AST::Statement * statement) {
                                                return
                                                        acc
                                                        + std::string((depth + 1) * 8, ' ')
                                                        + statement->show(depth + 1)
                                                        + (
                                                                   dynamic_cast<Tajada::AST::Block         *>(statement)
                                                                || dynamic_cast<Tajada::AST::If            *>(statement)
                                                                || dynamic_cast<Tajada::AST::While         *>(statement)
                                                                || dynamic_cast<Tajada::AST::For           *>(statement)
                                                                || dynamic_cast<Tajada::AST::TypeSelection *>(statement)
                                                                ? u8"\n"
                                                                : u8".\n"
                                                        )
                                                ;
                                        }
                                )
                                + std::string(depth * 8, ' ')
                                + u8"}"
                        ;
                }



                void Block::gen(
                        Tajada::Code::Block * b
                ) {
                        auto bs = new Tajada::Code::Block(
                                "scope_" + std::to_string(this->scope->id),
                                this->scope
                        );

                        auto be = new Tajada::Code::Block(
                                b->end->rawLabel(),
                                b->end->scope,
                                b->end->index + 1
                        );

                        b->end->instructions.push_back(
                                new Tajada::Code::Intermediate::Instruction::Jump(bs)
                        );
                        b->end->successors.push_back(bs); bs->predecessors.push_back(b);
                        b->end = bs;

                        std::for_each(
                                this->statements->begin(),
                                this->statements->end(),
                                [b](Tajada::AST::Statement * s) {
                                        s->gen(b);
                                }
                        );

                        b->end->instructions.push_back(
                                new Tajada::Code::Intermediate::Instruction::Jump(be)
                        );
                        b->end->successors.push_back(be); be->predecessors.push_back(b->end);

                        b->end = be;
                }
        }
}
