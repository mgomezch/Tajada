#include <string>

#include "Tajada/Type/Array.hh"

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                Array::Array(
                        Type * p_contents
                ):
                        Type(Tajada::Type::Type::Complete::incomplete),
                        contents(p_contents),
                        length(0)
                {}

                Array::Array(
                        Type * p_contents,
                        unsigned int p_length
                ):
                        Type(p_contents->is_complete),
                        contents(p_contents),
                        length(p_length)
                {}

                unsigned int Array::size_() {
                        auto s = contents->size();
                        auto a = contents->alignment();
                        return length * (s + a - s % a);
                }

                unsigned int Array::alignment_() {
                        return contents->alignment();
                }

                std::string Array::show(unsigned int depth) {
                        return
                                u8"arroz con "
                                + contents->show(depth)
                        ;
                }
        }
}
