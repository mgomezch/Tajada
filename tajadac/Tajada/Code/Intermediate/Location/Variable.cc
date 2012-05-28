#include <string>

// Class:
#include "Tajada/Code/Intermediate/Location/Variable.hh"

// Superclasses:
#include "Tajada/Code/Location.hh"
#include "Tajada/Code/Intermediate/Location/Location.hh"

#include "scope.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Location {
                                Variable::Variable(
                                        Tajada::Scope * p_scope,
                                        std::string   * p_name
                                ):
                                        Tajada::Code::Location(),
                                        Tajada::Code::Intermediate::Location::Location(),

                                        scope(p_scope),
                                        name (p_name )
                                {}



                                std::string Variable::show() {
                                        return
                                                *this->name
                                                + u8"[[scope: "
                                                + std::to_string(this->scope->id)
                                                + u8"]]"
                                        ;
                                }
                        }
                }
        }
}
