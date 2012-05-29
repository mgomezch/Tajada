#ifndef TAJADA_CODE_ADDRESS_HH
#define TAJADA_CODE_ADDRESS_HH

#include <string>

namespace Tajada {
        namespace Code {
                class Address {
                        public:
                                virtual std::string show() = 0;

                                virtual ~Address() = 0;
                };
        }
}

#endif
