#include <string>

#include "Tajada/AST/For.hh"

#include "Tajada/AST/Block.hh"
#include "Tajada/AST/Expression.hh"
#include "Tajada/AST/If.hh"
#include "Tajada/AST/Statement.hh"
#include "Tajada/AST/TypeSelection.hh"
#include "Tajada/AST/While.hh"

namespace Tajada {
        namespace AST {
                For::For(
                        std::string * p_counter,
                        Tajada::AST::Expression * p_inicio,
                        Tajada::AST::Expression * p_fin,
                        Tajada::AST::Statement * p_body
                ):
                        counter(p_counter),
                        inicio(p_inicio),
                        fin(p_fin),
                        body(p_body)
                {}

                std::string For::show(unsigned int depth) {
                        return
                                u8"for "
                                + *counter
                                + u8" in ("
                                + inicio->show(depth)
                                + u8" … "
                                + fin->show(depth)
                                + u8") "
                                + body->show(depth)
                                + (
                                        (
                                                   dynamic_cast<Tajada::AST::Block         *>(body)
                                                || dynamic_cast<Tajada::AST::If            *>(body)
                                                || dynamic_cast<Tajada::AST::While         *>(body)
                                                || dynamic_cast<Tajada::AST::For           *>(body)
                                                || dynamic_cast<Tajada::AST::TypeSelection *>(body)
                                        )
                                        ? u8""
                                        : u8"."
                                );
                }
        }
}
