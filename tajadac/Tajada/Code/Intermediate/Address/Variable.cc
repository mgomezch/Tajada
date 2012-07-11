#include <string>

// Class:
#include "Tajada/Code/Intermediate/Address/Variable.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Location.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"
#include "scope.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                Variable::Variable(
                                        Tajada::Scope * p_scope ,
                                        std::string   * p_name  ,
                                        unsigned int    p_offset
                                ):
                                        Tajada::Code::Address(),
                                        Tajada::Code::Intermediate::Address::Address(),
                                        Tajada::Code::Intermediate::Address::Location(p_offset),

                                        scope(p_scope),
                                        name (p_name )
                                {}



                                std::string Variable::show() {
                                        return
                                                (
                                                        this->offset
                                                        ? std::to_string(this->offset)
                                                        + u8"("
                                                        : u8""
                                                )
                                                + *this->name
                                                + u8"[[scope: "
                                                + std::to_string(this->scope->id)
                                                + u8"]]"
                                                + (
                                                        this->offset
                                                        ? u8")"
                                                        : u8""
                                                )
                                        ;
                                }



                                Tajada::Code::MIPS::Address::Address * Variable::to_mips() {
                                        return
                                                new Tajada::Code::MIPS::Address::Register
                                                ( this->scope->type == Tajada::Scope::Type::global
                                                ? Tajada::Code::MIPS::Address::Register::R::gp
                                                : Tajada::Code::MIPS::Address::Register::R::fp
                                                , -this->scope->variable_offset(*this->name)
                                                )
                                        ;
                                }
                        }
                }
        }
}
