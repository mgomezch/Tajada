#include <string>

#include "Tajada/Type/Float.hh"

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                Float::Float():
                           Tajada::Type::Type(Tajada::Type::Type::Complete::complete)
                {}

                std::string Float::show(unsigned int depth) {
                        TAJADA_UNUSED_PARAMETER(depth);
                        return u8"papelón";
                }

                unsigned int Float::size_     () { return 32; }
                unsigned int Float::alignment_() { return 32; }
        }
}
