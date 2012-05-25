#include <string>

#include "Tajada/Type/Integer.hh"

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                Integer::Integer():
                           Tajada::Type::Type(Tajada::Type::Type::Complete::complete)
                {}

                std::string Integer::show(unsigned int depth) {
                        TAJADA_UNUSED_PARAMETER(depth);
                        return u8"queso";
                }

                unsigned int Integer::size_     () { return 32; }
                unsigned int Integer::alignment_() { return 32; }
        }
}
