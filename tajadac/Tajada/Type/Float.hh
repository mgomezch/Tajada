#ifndef TAJADA_TYPE_FLOAT_HH
#define TAJADA_TYPE_FLOAT_HH

#include <string>

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                class Float : public virtual Tajada::Type::Type {
                        public:
                                Float();

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
