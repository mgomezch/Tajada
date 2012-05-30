#include <numeric>
#include <string>

// Class:
#include "Tajada/Code/Intermediate/Address/Complex.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"

#include "Tajada/Type/Tuple.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                Complex::Complex(
                                        Tajada::Type::Tuple * p_type
                                ):
                                        Tajada::Code::Address(),
                                        Tajada::Code::Intermediate::Address::Address(),

                                        elems{},
                                        type(p_type)
                                {}



                                std::string Complex::show() {
                                        return
                                                u8"["
                                                + (
                                                        this->elems.empty()
                                                        ? u8""
                                                        : std::accumulate(
                                                                this->elems.begin(),
                                                                --this->elems.end(),
                                                                std::string(),
                                                                [](std::string acc, Tajada::Code::Intermediate::Address::Address * a) {
                                                                        return
                                                                                acc
                                                                                + a->show()
                                                                                + ", "
                                                                        ;
                                                                }
                                                        )
                                                        + this->elems.back()->show()
                                                )
                                                + u8"]"
                                        ;
                                }
                        }
                }
        }
}
