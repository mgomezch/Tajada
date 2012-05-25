#ifndef TAJADA_TYPE_BOOLEAN_HH
#define TAJADA_TYPE_BOOLEAN_HH

#include <string>

#include "Tajada/Type/Type.hh"

namespace Tajada {
        namespace Type {
                class Boolean : public virtual Tajada::Type::Type {
                        public:
                                Boolean();

                                virtual unsigned int size_();
                                virtual unsigned int alignment_();
                                virtual std::string show(unsigned int depth = 0);
                };
        }
}

#endif
