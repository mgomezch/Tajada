#ifndef TAJADA_CODE_LOCATION_HH
#define TAJADA_CODE_LOCATION_HH

#include <string>

namespace Tajada {
        namespace Code {
                class Location {
                        public:
                                virtual std::string show() = 0;

                                virtual ~Location() = 0;
                };
        }
}

#endif
