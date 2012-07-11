#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_TEMPORARY_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_TEMPORARY_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Location.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                class Temporary:
                                        public virtual Tajada::Code::Intermediate::Address::Location
                                {
                                        public:
                                                unsigned long int id;

                                                Temporary(
                                                        unsigned int offset = 0
                                                );

                                                virtual std::string show();

                                                virtual Tajada::Code::MIPS::Address::Address * to_mips();

                                        private:
                                                static unsigned long int next_id;
                                };
                        }
                }
        }
}

#endif
