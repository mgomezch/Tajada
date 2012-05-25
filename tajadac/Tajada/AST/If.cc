#include <string>

#include "Tajada/AST/Block.hh"
#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/For.hh"
#include "Tajada/AST/If.hh"
#include "Tajada/AST/Statement.hh"
#include "Tajada/AST/TypeSelection.hh"
#include "Tajada/AST/While.hh"

namespace Tajada {
        namespace AST {
                If::If(
                        Tajada::AST::Expression * condition,
                        Tajada::AST::Statement * body_true,
                        Tajada::AST::Statement * body_false
                ):
                        condition(condition),
                        body_true(body_true),
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
                                                dynamic_cast<Tajada::AST::Block *>(body_true)
                                                || dynamic_cast<Tajada::AST::For *>(body_true)
                                                || dynamic_cast<Tajada::AST::If *>(body_true)
                                                || dynamic_cast<Tajada::AST::TypeSelection *>(body_true)
                                                || dynamic_cast<Tajada::AST::While *>(body_true)
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
                                                        dynamic_cast<Tajada::AST::Block *>(body_false)
                                                        || dynamic_cast<Tajada::AST::For *>(body_false)
                                                        || dynamic_cast<Tajada::AST::If *>(body_false)
                                                        || dynamic_cast<Tajada::AST::TypeSelection *>(body_false)
                                                        || dynamic_cast<Tajada::AST::While *>(body_false)
                                                )
                                                ? u8""
                                                : u8"."
                                        )
                                        : u8""
                                );
                }
        }
}
