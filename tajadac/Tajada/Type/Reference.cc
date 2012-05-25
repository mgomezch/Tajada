#include <string>

#include "Tajada/Type/Reference.hh"

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                Reference::Reference(
                        Type * p_target
                ):
                        Type(Tajada::Type::Type::Complete::complete),
                        target(p_target)
                {}

                unsigned int Reference::size_     () { return 32; }
                unsigned int Reference::alignment_() { return 32; }

                std::string Reference::show(unsigned int depth) {
                        return
                                u8"⋘"
                                + target->show(depth)
                                + u8"⋙"
                        ;
                }
        }
}
