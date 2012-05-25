#include <numeric>
#include <list>
#include <string>

#include "Tajada/AST/Block.hh"
#include "Tajada/AST/FunctionDefinition.hh"
#include "Tajada/AST/Program.hh"
#include "Tajada/AST/Statement.hh"

namespace Tajada {
        namespace AST {
                Program::Program(
                                std::list<Tajada::AST::Statement *> * statements,
                                Tajada::AST::Block * main
                ):
                        statements(statements),
                        main(main)
                {}

                std::string Program::show(unsigned int depth) {
                        return
                                std::accumulate(
                                        statements->begin(),
                                        statements->end(),
                                        std::string(),
                                        [depth](std::string acc, Tajada::AST::Statement *statement) {
                                                return
                                                        acc
                                                        + statement->show(depth)
                                                        + (
                                                                (
                                                                        dynamic_cast<Tajada::AST::Block *>(statement)
                                                                        || dynamic_cast<Tajada::AST::FunctionDefinition *>(statement)
                                                                )
                                                                ? u8"\n"
                                                                : u8".\n"
                                                        );
                                        }
                                )
                                + main->show(depth);
                }
        }
}