#ifndef TAJADA_CODE_INTERMEDIATE_ADDRESS_TEMPORARY_HH
#define TAJADA_CODE_INTERMEDIATE_ADDRESS_TEMPORARY_HH

#include <string>

// Superclasses:
#include "Tajada/Code/Intermediate/Address/Address.hh"

#include "scope.hh"

namespace Tajada {
        namespace Code {
                namespace Intermediate {
                        namespace Address {
                                class Temporary:
                                        public virtual Tajada::Code::Intermediate::Address::Address
                                {
                                        public:
                                                unsigned long int id;

                                                Temporary();

                                                virtual std::string show();

                                        private:
                                                static unsigned long int next_id;
                                };
                        }
                }
        }
}

#endif
