#include <string>

// Class:
#include "Tajada/Code/Intermediate/Address/Variable.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"

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

                                        scope (p_scope ),
                                        name  (p_name  ),
                                        offset(p_offset)
                                {}



                                std::string Variable::show() {
                                        return
                                                *this->name
                                                + u8"[[scope: "
                                                + std::to_string(this->scope->id)
                                                + (
                                                        offset == 0
                                                        ? u8""
                                                        : u8", offset: "
                                                        + std::to_string(this->offset)
                                                )
                                                + u8"]]"
                                        ;
                                }
                        }
                }
        }
}
