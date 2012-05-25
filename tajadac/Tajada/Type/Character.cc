#include <string>

#include "Tajada/Type/Character.hh"

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                Character::Character():
                           Tajada::Type::Type(Tajada::Type::Type::Complete::complete)
                {}

                std::string Character::show(unsigned int depth) {
                        TAJADA_UNUSED_PARAMETER(depth);
                        return u8"caraota";
                }

                unsigned int Character::size_     () { return 32; }
                unsigned int Character::alignment_() { return 32; }
        }
}
