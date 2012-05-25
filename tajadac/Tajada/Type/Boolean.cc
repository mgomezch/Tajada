#include <string>

#include "Tajada/Type/Boolean.hh"

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                Boolean::Boolean():
                           Tajada::Type::Type(Tajada::Type::Type::Complete::complete)
                {}

                std::string Boolean::show(unsigned int depth) {
                        TAJADA_UNUSED_PARAMETER(depth);
                        return u8"café";
                }

                unsigned int Boolean::size_     () { return 1; }
                unsigned int Boolean::alignment_() { return 8; }
        }
}
