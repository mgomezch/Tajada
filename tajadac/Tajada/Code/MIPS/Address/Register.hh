#ifndef TAJADA_CODE_MIPS_REGISTER_HH
#define TAJADA_CODE_MIPS_REGISTER_HH

#include <string>

#include "Tajada/Code/MIPS/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Address {
                                class Register : public virtual Tajada::Code::MIPS::Address::Address {
                                        public:
                                                enum class R : unsigned char
                                                        { zero
                                                        , at
                                                        , v0, v1
                                                        , a0, a1, a2, a3
                                                        , t0, t1, t2, t3, t4, t5, t6, t7
                                                        , s0, s1, s2, s3, s4, s5, s6, s7
                                                        , t8, t9
                                                        , k0, k1
                                                        , gp, sp, fp, ra
                                                        ,  f0,  f1,  f2,  f3,  f4,  f5,  f6,  f7
                                                        ,  f8,  f9, f10, f11, f12, f13, f14, f15
                                                        , f16, f17, f18, f19, f20, f21, f22, f23
                                                        , f24, f25, f26, f27, f28, f29, f30, f31
                                                        }
                                                r;

                                                int offset;

                                                Register(
                                                        Tajada::Code::MIPS::Address::Register::R p_r         ,
                                                        int                                      p_offset = 0
                                                );

                                                virtual std::string show();
                                };

                                bool operator == (
                                        Tajada::Code::MIPS::Address::Register const & l,
                                        Tajada::Code::MIPS::Address::Register const & r
                                );
                        }
                }
        }
}

#endif
