#include <numeric>
#include <string>

// Class:
#include "Tajada/AST/TypeSelection.hh"

// Superclasses:
#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Statement.hh"

#include "Tajada/AST/Block.hh"
#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/For.hh"
#include "Tajada/AST/If.hh"
#include "Tajada/AST/TypeCase/TypeCase.hh"
#include "Tajada/AST/While.hh"


namespace Tajada {
        namespace AST {
                TypeSelection::TypeSelection(
                        Tajada::AST::Expression * p_fuente,
                        std::string * p_variable,
                        std::vector<Tajada::AST::TypeCase::TypeCase *> * p_casos
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),

                        fuente(p_fuente),
                        variable(p_variable),
                        casos(p_casos)
                {}

                std::string TypeSelection::show(unsigned int depth) {
                        return
                                fuente->show(depth)
                                + u8" ∷ "
                                + *variable
                                + u8" {\n"
                                + std::accumulate(
                                        casos->begin(),
                                        casos->end(),
                                        std::string(),
                                        [depth](std::string acc, Tajada::AST::TypeCase::TypeCase * c) {
                                                return
                                                        acc
                                                        + std::string((depth + 1) * 8, ' ')
                                                        + c->show(depth + 1)
                                                        + (
                                                                (
                                                                           dynamic_cast<Tajada::AST::Block         *>(c->body)
                                                                        || dynamic_cast<Tajada::AST::For           *>(c->body)
                                                                        || dynamic_cast<Tajada::AST::If            *>(c->body)
                                                                        || dynamic_cast<Tajada::AST::TypeSelection *>(c->body)
                                                                        || dynamic_cast<Tajada::AST::While         *>(c->body)
                                                                )
                                                                ? u8"\n"
                                                                : u8".\n"
                                                        );
                                        }
                                )
                                + std::string(depth * 8, ' ')
                                + u8"}";
                }
        }
}
