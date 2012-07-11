// TODO: remove this file once all subclasses have their implementation of genl/genr

// Class:
#include "Tajada/Code/Intermediate/Address/Unimplemented.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"

#include "Tajada/AST/AST.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                Unimplemented::Unimplemented(
                                        Tajada::AST::AST * p_unimplemented
                                ):
                                        Tajada::Code::Address(),
                                        Tajada::Code::Intermediate::Address::Address(),

                                        unimplemented(p_unimplemented)
                                {}

                                std::string Unimplemented::show() {
                                        return
                                                u8"‹UNIMPLEMENTED ADDRESS: "
                                                + unimplemented->show()
                                                + u8"›"
                                        ;
                                }
                        }
                }
        }
}
