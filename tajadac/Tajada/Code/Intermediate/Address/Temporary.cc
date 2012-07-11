#include <string>

// Class:
#include "Tajada/Code/Intermediate/Address/Temporary.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/Intermediate/Address/Address.hh"
#include "Tajada/Code/Intermediate/Address/Location.hh"

#include "Tajada/Code/MIPS/Address/Register.hh"
#include "Tajada/Code/MIPS/MIPS.hh"
#include "scope.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                unsigned long int Temporary::next_id = 0;

                                Temporary::Temporary(
                                        unsigned int p_offset
                                ):
                                        Tajada::Code::Address(),
                                        Tajada::Code::Intermediate::Address::Address(),
                                        Tajada::Code::Intermediate::Address::Location(p_offset),

                                        id(++Tajada::Code::Intermediate::Address::Temporary::next_id)
                                {}



                                std::string Temporary::show() {
                                        return
                                                this->offset

                                                ? std::to_string(this->offset)
                                                + u8"($t"
                                                + std::to_string(this->id)
                                                + u8")"

                                                : u8"$t"
                                                + std::to_string(this->id)
                                        ;
                                }



                                Tajada::Code::MIPS::Address::Address * Temporary::to_mips() {
                                        unsigned int offset;

                                        auto it = Tajada::Code::MIPS::temp_offsets.find(this->id);
                                        if (it != Tajada::Code::MIPS::temp_offsets.end()) {
                                                offset = it->second;
                                        } else {
                                                Tajada::Code::MIPS::temp_offsets[this->id] = offset = Tajada::Code::MIPS::next_offset;
                                                Tajada::Code::MIPS::next_offset += 4; // TODO: shouldn’t this depend on the type somehow?
                                        }

                                        return
                                                new Tajada::Code::MIPS::Address::Register(
                                                        Tajada::Code::MIPS::Address::Register::R::fp,
                                                        -(offset + this->offset)
                                                )
                                        ;
                                }
                        }
                }
        }
}
