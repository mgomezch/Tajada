#ifndef TAJADA_TYPE_INTEGER_HH
#define TAJADA_TYPE_INTEGER_HH

#include <string>

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                class Integer : public virtual Tajada::Type::Type {
                        public:
                                Integer();

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
