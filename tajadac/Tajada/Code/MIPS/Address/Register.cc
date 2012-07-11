#include <string>

// Class:
#include "Tajada/Code/MIPS/Address/Register.hh"

// Superclasses:
#include "Tajada/Code/Address.hh"
#include "Tajada/Code/MIPS/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Address {
                                Register::Register(
                                        Tajada::Code::MIPS::Address::Register::R p_r     ,
                                        int                                      p_offset
                                ):
                                        Tajada::Code::Address(),
                                        Tajada::Code::MIPS::Address::Address(),

                                        r     (p_r     ),
                                        offset(p_offset)
                                {}



                                // Painful reminder of C++’s idiocy: this is just «deriving Show»
                                std::string Register::show() {
                                        std::string r = "$";
                                        switch (this->r) {
                                                case Tajada::Code::MIPS::Address::Register::R::zero: r += "zero"; break;
                                                case Tajada::Code::MIPS::Address::Register::R::at  : r += "at"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::v0  : r += "v0"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::v1  : r += "v1"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::a0  : r += "a0"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::a1  : r += "a1"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::a2  : r += "a2"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::a3  : r += "a3"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::t0  : r += "t0"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::t1  : r += "t1"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::t2  : r += "t2"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::t3  : r += "t3"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::t4  : r += "t4"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::t5  : r += "t5"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::t6  : r += "t6"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::t7  : r += "t7"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::s0  : r += "s0"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::s1  : r += "s1"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::s2  : r += "s2"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::s3  : r += "s3"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::s4  : r += "s4"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::s5  : r += "s5"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::s6  : r += "s6"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::s7  : r += "s7"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::t8  : r += "t8"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::t9  : r += "t9"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::k0  : r += "k0"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::k1  : r += "k1"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::gp  : r += "gp"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::sp  : r += "sp"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::fp  : r += "fp"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::ra  : r += "ra"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f0  : r += "f0"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f1  : r += "f1"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f2  : r += "f2"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f3  : r += "f3"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f4  : r += "f4"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f5  : r += "f5"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f6  : r += "f6"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f7  : r += "f7"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f8  : r += "f8"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f9  : r += "f9"  ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f10 : r += "f10" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f11 : r += "f11" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f12 : r += "f12" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f13 : r += "f13" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f14 : r += "f14" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f15 : r += "f15" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f16 : r += "f16" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f17 : r += "f17" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f18 : r += "f18" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f19 : r += "f19" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f20 : r += "f20" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f21 : r += "f21" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f22 : r += "f22" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f23 : r += "f23" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f24 : r += "f24" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f25 : r += "f25" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f26 : r += "f26" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f27 : r += "f27" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f28 : r += "f28" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f29 : r += "f29" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f30 : r += "f30" ; break;
                                                case Tajada::Code::MIPS::Address::Register::R::f31 : r += "f31" ; break;
                                        }
                                        if (offset) return std::to_string(offset) + "(" + r + ")";
                                        return r;
                                }



                                // Painful reminder of C++’s idiocy: this is just «deriving Eq»
                                bool operator == (
                                        Tajada::Code::MIPS::Address::Register const & l,
                                        Tajada::Code::MIPS::Address::Register const & r
                                ) {
                                        return l.r == r.r && l.offset == r.offset;
                                }
                        }
                }
        }
}
