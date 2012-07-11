#include <string>

#include "Tajada/AST/AST.hh"
#include "Tajada/AST/Statement.hh"
#include "Tajada/AST/VariableDefinition.hh"
#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace AST {
                VariableDefinition::VariableDefinition(
                        std::string        * p_name,
                        Tajada::Type::Type * p_type
                ):
                        Tajada::AST::AST(),
                        Tajada::AST::Statement(),

                        name(p_name),
                        type(p_type)
                {}



                std::string VariableDefinition::show(unsigned int depth) {
                        return
                                *name
                                + std::string(u8" es ")
                                + type->show(depth)
                        ;
                }



                void VariableDefinition::gen(
                        Tajada::Code::Block * b
                ) {
                        TAJADA_UNUSED_PARAMETER(b);
                }
        }
}
