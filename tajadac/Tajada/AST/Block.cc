#include <numeric>
#include <list>
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

namespace Tajada {
        namespace AST {
                Block::Block(
                        std::list<Tajada::AST::Statement *> * p_statements
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),

                        statements(p_statements)
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



                Tajada::Code::Block * Block::gen(
                        Tajada::Code::Block * b
                ) {
                        std::accumulate(
                                this->statements->begin(),
                                this->statements->end(),
                                b,
                                [](Tajada::Code::Block * acc, Tajada::AST::Statement * s) {
                                        return s->gen(acc);
                                }
                        );
                        return b;
                }
        }
}
