#ifndef TAJADA_CODE_MIPS_LABEL_HH
#define TAJADA_CODE_MIPS_LABEL_HH

#include <string>

#include "Tajada/Code/MIPS/Address/Address.hh"

namespace Tajada {
        namespace Code {
                namespace MIPS {
                        namespace Address {
                                class Label : public virtual Tajada::Code::MIPS::Address::Address {
                                        public:
                                                std::string label;

                                                Label(
                                                        std::string p_label
                                                );

                                                virtual std::string show();
                                };
                        }
                }
        }
}

#endif
